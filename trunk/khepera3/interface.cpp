/* This file contains the wrapper c functions exposed in the dll, 
for use with matlab or other third party software*/

//#include "windows.h"

#include "KheperaIII.h"
#include "LocalizationSystem.h"

#include <iostream>
#include <string>

#include "boost/array.hpp"

using namespace std;
using namespace boost;

extern "C" __declspec(dllexport) int LaunchKhepera(int robotID, int mode, void** k3ptr){
	*k3ptr = new KheperaIII(robotID);
	KheperaIII* k3 = (KheperaIII*) *k3ptr;
	//cout<<"Initialising local system...\n";
	//k3->localizationSystem->init(mode,1,string(localIP), string(cortexIP), "objectNameCortex");
	return 0;
}

extern "C" __declspec(dllexport) int SetSpeed(void* k3ptr, int linear, int angular){
	KheperaIII* k3 = (KheperaIII*) k3ptr;
	k3->setVelocity(linear,angular);
	return 0;
}

extern "C" __declspec(dllexport) int InitLocalizationSystem(void* k3ptr, const char* localIP, const char* cortexIP){
	KheperaIII* k3 = (KheperaIII*) k3ptr;
	string bodyName("khe");
	char buf[10];
	int i=k3->getId();
	itoa(k3->getId(),buf,10);

	bodyName += buf;
	k3->localizationSystem->init(2,1,string(localIP), string(cortexIP), bodyName);	
	thread(&KheperaIII::ContinuousChecks, k3);
	return 0;
}

extern "C" __declspec(dllexport) int GetPosition(void* agent_ptr, double *posX, double *posY) {
	Agent* a = (Agent*) agent_ptr;
	double* pos = new double[2];
	pos = a->getPosition();
	*posX = pos[0];
	*posY = pos[1];
	return 0;
}

extern "C" __declspec(dllexport) int GetOrientation(void* agent_ptr, double* orientation){
	Agent* a = (Agent*) agent_ptr;
	*orientation = a->getOrientation();
	return 0;
}

