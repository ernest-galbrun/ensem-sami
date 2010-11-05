/* This file contains the wrapper c functions exposed in the dll, 
for use with matlab or other third party software*/

//#include "windows.h"

#include "KheperaIII.h"
#include "LocalizationSystem.h"
#include "Object.h"
#include "../Matlab/@khepera3/khepera3clib.h"

#include <iostream>
#include <string>

#include "boost/array.hpp"

using namespace std;
using namespace boost;

// global variable k3 stores pointer to every robot created.
// It is instanciated when the dll is loaded, and destructed when unloaded.
KheperaIII* k3[10];


extern "C" __declspec(dllexport) int LaunchKhepera(int robotID, int isVirtual){
	k3[robotID] = new KheperaIII(robotID, (bool) isVirtual);
	return 0;
}

extern "C" __declspec(dllexport) int DeleteKhepera(int robotID){
	delete(k3[robotID]);
	//k3[robotID]->CloseConnection();
	//k3[robotID]->closeSession();
	//k3[robotID] = NULL;
	return 0;
}

extern "C" __declspec(dllexport) int SendPosition(int robotID) {
	k3[robotID]->SendPosition();
	return 0;
}

extern "C" __declspec(dllexport) int SetSpeed(int robotID, double linear, double angular){
	k3[robotID]->setVelocity(linear,angular);
	return 0;
}

extern "C" __declspec(dllexport) int InitLocalizationSystem(int robotID, int mode, const char* localIP, const char* cortexIP){
	string bodyName("khe");
	char buf[10];
	int i=k3[robotID]->getId();
	itoa(k3[robotID]->getId(),buf,10);
	bodyName += buf;
	k3[robotID]->SetUpdatePositionMode(mode);
	if (mode)
		k3[robotID]->InitLocalizationSystem(string(localIP), string(cortexIP), bodyName);	
	k3[robotID]->LaunchContinuousThread();
	return 0;
}

extern "C" __declspec(dllexport) int GetPosition(int robotID, double *posX, double *posY) {
	array<double,2> pos = k3[robotID]->getPosition();
	*posX = pos[0];
	*posY = pos[1];
	return 0;
}

extern "C" __declspec(dllexport) int GetOrientation(int robotID, double* orientation){
	*orientation = k3[robotID]->getOrientation();
	return 0;
}

extern "C" __declspec(dllexport) int GetMode(int robotID, int* modeLeft, int* modeRight){
	return k3[robotID]->GetMode(modeLeft, modeRight);
}

extern "C" __declspec(dllexport) int GetPID(int robotID, int* pLeft, int* iLeft, int* dLeft, int* pRight, int* iRight, int* dRight){
	int PIDLeft[3];
	int PIDRight[3];
	int ret;
	ret = k3[robotID]->GetPID(&PIDLeft, &PIDRight);
	*pLeft = PIDLeft[0];
	*iLeft = PIDLeft[1];
	*dLeft=  PIDLeft[2];
	*pRight = PIDRight[0];
	*iRight = PIDRight[1];
	*dRight = PIDRight[2];
	return ret;
}

extern "C" __declspec(dllexport) int GetEncoderPosition(int robotID, int* left, int* right){
	k3[robotID]->getEncodersValue(left, right);
	return 0;
}

extern "C" __declspec(dllexport) int GetSpeed(int robotID, int* left, int* right){
	return k3[robotID]->GetSpeed(left,right);
}

extern "C" __declspec(dllexport) int SetMode(int robotID, int left, int right){
	return k3[robotID]->SetMode(left, right);
}

extern "C" __declspec(dllexport) int SetPID(int robotID, int pLeft, int iLeft, int dLeft, int pRight, int iRight, int dRight){
	return k3[robotID]->SetPID(pLeft, iLeft, dLeft, pRight, iRight, dRight);
}

extern "C" __declspec(dllexport) int SetTargetPoint(int robotID, int targetLeft, int targetRight){
	return k3[robotID]->SetTargetPoint(targetLeft, targetRight);
}

extern "C" __declspec(dllexport) int ResetPosition(int robotID, int posLeft, int posRight){
	return k3[robotID]->ResetPosition(posLeft, posRight);
}

extern "C" __declspec(dllexport) int StartMotors(int robotID){
	return k3[robotID]->StartMotors();
}

extern "C" __declspec(dllexport) int StopMotors(int robotID){
	return k3[robotID]->StopMotors();
}

extern "C" __declspec(dllexport) int RecordPulse(int robotID, int modeLeft, int modeRight, int nStep, int* targetLeft, int* targetRight, int* NAcquisition,
										  int** timeStamp, int** valuesLeft, int** valuesRight){
	return k3[robotID]->RecordPulse(modeLeft, modeRight, nStep, targetLeft, targetRight, NAcquisition, timeStamp, valuesLeft, valuesRight);
}

extern "C" __declspec(dllexport) int StartInternalTracking(int robotID){
	return k3[robotID]->StartInternalTracking();
}
extern "C" __declspec(dllexport) int StopInternalTracking(int robotID){
	return k3[robotID]->StopInternalTracking();
}

extern "C" __declspec(dllexport) int GetNeighbors(int robotID, int* numberOfNeighbors, int** id, double** x, double** y) {
	k3[robotID]->getNeighbors(numberOfNeighbors,id,x,y);
	return 0;
}