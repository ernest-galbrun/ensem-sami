/* This file contains the wrapper c functions exposed in the dll, 
for use with matlab or other third party software*/

//#include "windows.h"

#include "KheperaIII.h"
#include "LocalizationSystem.h"
#include "Object.h"
#include "Wand.h" 
#include "../Matlab/@khepera3/khepera3clib.h"
#include <errno.h>

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "boost/array.hpp"

using namespace std;
using namespace boost;

const int maxRobotNumber = 1000;

// global variable k3 stores pointer to every robot created.
// It is instanciated when the dll is loaded, and destructed when unloaded.
KheperaIII* k3[maxRobotNumber];
vector<bool>	exists(maxRobotNumber,false);


extern "C" __declspec(dllexport) int GetWandPosition(double* X, double* Y, const char* ownIP){
	static bool firstCall=true;
	static Wand wand;
	array<double,2> position;
	double orientation;
	if (firstCall){
		wand.init(ownIP,"193.49.136.176","Wand500",&position, &orientation);
		firstCall=false;
	}
	else {
		wand.UpdatePosition(&position, &orientation);
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

extern "C" __declspec(dllexport) int InitLocalizationSystem(int robotID, int mode, const char* localIP, const char* cortexIP){
	K3ErrorCode ret = K3_NOERROR;
	if (robotID>=maxRobotNumber || !exists[robotID])
		return K3_BADROBOTID;
	stringstream bodyName;
	bodyName << "markerset_robot"<< robotID;
	k3[robotID]->SetUpdatePositionMode(mode);
	if (mode) {
		try {
			k3[robotID]->InitLocalizationSystem(string(localIP), string(cortexIP), bodyName.str());	
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
	array<double,2> pos = k3[robotID]->getPosition();
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
