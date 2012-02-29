/* This file contains the wrapper c functions exposed in the dll, 
for use with matlab or other third party software*/

//#include "windows.h"

#include "KheperaIII.h"
#include "LocalizationSystem.h"
#include "Object.h"
#include "Wand.h" 
#include "Parrot.h"
//#include "../Matlab/@khepera3/khepera3clib.h"
#include <errno.h>

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>

//#include "boost/array.hpp"

enum K3ErrorCode{
	K3_NOERROR = 0,
	K3_CONNECTIONFAILURE,
	K3_OFFLINELOCALIZATION,
	K3_BADROBOTID,
	K3_CORTEXFAILURE
};


using namespace std;
using namespace std::tr1;
using namespace boost;

const int maxRobotNumber = 1000;

// global variable k3 stores pointer to every robot created.
// It is instanciated when the dll is loaded, and destructed when unloaded.
// instanceCount is the count of LocalizationSystem instances
KheperaIII* k3[maxRobotNumber];
vector<bool>	exists(maxRobotNumber,false);
int instanceCount = 0;
//Wand wand;
//bool firstCall=true;

extern "C" const __declspec(dllexport) char*  PrintHello(){
	return "Hellooo\0";
}


extern "C" __declspec(dllexport) int GetDronePosition(double * frontX, double* frontY, double* frontZ, double* backX, double * backY, double* backZ){
	static bool firstCall=true;
	static Parrot parrot;
	try {
		if (firstCall) {
			firstCall=false;
			parrot.FindBodyIndex();
		}
		parrot.UpdatePosition(frontX, frontY, frontZ, backX, backY, backZ);
	}
	catch (ios_base::failure e) {
		cout<<e.what();
		return K3_CORTEXFAILURE;
	}	
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int OpenCortex(const char* ownIP){
	try {
		LocalizationSystem::Open(ownIP, "193.49.136.176");
	}
	catch (ios_base::failure) {
		return K3_OFFLINELOCALIZATION;
	}
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int CloseCortex(){
	LocalizationSystem::Close();
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int GetWandPosition(double* X, double* Y){
	static bool firstCall=true;
	static Wand wand;
	std::array<double,2> position;
	double orientation;
	try {
		if (firstCall) {
			firstCall=false;
			wand.FindBodyIndex();
		}
		wand.UpdatePosition(&position, &orientation);
	}
	catch (ios_base::failure e) {
		cout<<e.what();
		return K3_CORTEXFAILURE;
	}
	*X = position[0];
	*Y = position[1];
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int LaunchKhepera(int robotID, int isVirtual,double x0,double y0,double theta0){
	if (robotID>=maxRobotNumber)
		return K3_BADROBOTID;
	if (exists[robotID])
		delete(k3[robotID]);
	vector<double> initialPosition(2,0);
	initialPosition[0] = x0;
	initialPosition[1] = y0;
	k3[robotID] = new KheperaIII(robotID, (bool) isVirtual, initialPosition, theta0);
	try {
		k3[robotID]->Init();
	}
	catch (ios_base::failure e) {
		delete(k3[robotID]);	
		cout<<e.what();
		return K3_CONNECTIONFAILURE;
	}
	exists[robotID] = true;
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int DeleteKhepera(int robotID){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	delete(k3[robotID]);
	exists[robotID] = false;
	//k3[robotID]->CloseConnection();
	//k3[robotID]->closeSession();
	//k3[robotID] = NULL;
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int SendPosition(int robotID) {
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->SendPosition();
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int SetSpeed(int robotID, double linear, double angular){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->setVelocity(linear,angular);
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int InitLocalizationSystem(int robotID, int mode) {
	K3ErrorCode ret = K3_NOERROR;
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	stringstream bodyName;
	bodyName << "markerset_robot"<< robotID;
	k3[robotID]->SetUpdatePositionMode(mode);
	if (mode) {
		try {
			k3[robotID]->InitLocalizationSystem(bodyName.str());	
		}
		catch (ios_base::failure e) {
			k3[robotID]->SetUpdatePositionMode(0);
			cout<<e.what();
			ret = K3_OFFLINELOCALIZATION;
		}
	}
	k3[robotID]->LaunchContinuousThread();
	return ret;
}

extern "C" __declspec(dllexport) int GetPosition(int robotID, double *posX, double *posY) {
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	std::array<double,2> pos = k3[robotID]->getPosition();
	*posX = pos[0];
	*posY = pos[1];
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int GetOrientation(int robotID, double* orientation){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	*orientation = k3[robotID]->getOrientation();
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int GetMode(int robotID, int* modeLeft, int* modeRight){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	return k3[robotID]->GetMode(modeLeft, modeRight);
}

extern "C" __declspec(dllexport) int GetPID(int robotID, int* pLeft, int* iLeft, int* dLeft, int* pRight, int* iRight, int* dRight){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	int PIDLeft[3];
	int PIDRight[3];
	k3[robotID]->GetPID(&PIDLeft, &PIDRight);
	*pLeft = PIDLeft[0];
	*iLeft = PIDLeft[1];
	*dLeft=  PIDLeft[2];
	*pRight = PIDRight[0];
	*iRight = PIDRight[1];
	*dRight = PIDRight[2];
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int GetEncoderPosition(int robotID, int* left, int* right){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->getEncodersValue(left, right);
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int GetSpeed(int robotID, int* left, int* right){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->GetSpeed(left,right);
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int SetMode(int robotID, int left, int right){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->SetMode(left, right);
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int SetPID(int robotID, int pLeft, int iLeft, int dLeft, int pRight, int iRight, int dRight){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->SetPID(pLeft, iLeft, dLeft, pRight, iRight, dRight);
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int SetTargetPoint(int robotID, int targetLeft, int targetRight){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->SetTargetPoint(targetLeft, targetRight);
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int ResetPosition(int robotID, int posLeft, int posRight){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->ResetPosition(posLeft, posRight);
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int StartMotors(int robotID){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->StartMotors();
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int StopMotors(int robotID){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->StopMotors();
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int RecordPulse(int robotID, int modeLeft, int modeRight, int nStep, int* targetLeft, int* targetRight, int* NAcquisition,
										  int** timeStamp, int** valuesLeft, int** valuesRight){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->RecordPulse(modeLeft, modeRight, nStep, targetLeft, targetRight, NAcquisition, timeStamp, valuesLeft, valuesRight);
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int StartInternalTracking(int robotID){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->StartInternalTracking();
	return K3_NOERROR;
}
extern "C" __declspec(dllexport) int StopInternalTracking(int robotID){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->StopInternalTracking();
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int GetNeighbors(int robotID, int* numberOfNeighbors, int** id, double** x, double** y) {
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->getNeighbors(numberOfNeighbors,id,x,y);
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int GetAmbientIR(int robotID, int* timestamp, int** values){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->GetAmbientIR(timestamp, values);
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int GetProximityIR(int robotID, int* timestamp, int** values){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->GetProximityIR(timestamp, values);
	return K3_NOERROR;
}

extern "C" __declspec(dllexport) int GetUltrasound(int robotID, int** values){
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	k3[robotID]->GetUltrasound(values);
	return K3_NOERROR;
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
		int a;
        case DLL_PROCESS_ATTACH:
			a=0;
         // Initialize once for each new process.
         // Return FALSE to fail DLL load.
            break;

        case DLL_THREAD_ATTACH:
         // Do thread-specific initialization.
            break;

        case DLL_THREAD_DETACH:
         // Do thread-specific cleanup.
            break;

        case DLL_PROCESS_DETACH:
			CloseCortex();
         // Perform any necessary cleanup.
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}