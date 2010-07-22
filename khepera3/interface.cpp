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

KheperaIII* k3;

extern "C" __declspec(dllexport) int LaunchKhepera(int robotID){
	k3 = new KheperaIII(robotID);
	//KheperaIII* k3 = (KheperaIII*) *k3ptr;
	//cout<<"Initialising local system...\n";
	//k3->localizationSystem->init(mode,1,string(localIP), string(cortexIP), "objectNameCortex");
	return 0;
}

extern "C" __declspec(dllexport) int SetSpeed(double linear, double angular){
	//KheperaIII* k3 = (KheperaIII*) k3ptr;
	k3->setVelocity(linear,angular);
	return 0;
}

extern "C" __declspec(dllexport) int InitLocalizationSystem(int mode, const char* localIP, const char* cortexIP){
	//KheperaIII* k3 = (KheperaIII*) k3ptr;
	string bodyName("khe");
	char buf[10];
	int i=k3->getId();
	itoa(k3->getId(),buf,10);

	bodyName += buf;
	k3->localizationSystem->init(mode,1,string(localIP), string(cortexIP), bodyName);	
	//thread(&KheperaIII::ContinuousChecks, k3);
	return 0;
}

extern "C" __declspec(dllexport) int GetPosition(double *posX, double *posY) {
	//Agent* a = (KheperaIII*) agent_ptr;
	double* pos = new double[2];
	pos = k3->getPosition();
	*posX = pos[0];
	*posY = pos[1];
	return 0;
}

extern "C" __declspec(dllexport) int GetOrientation(double* orientation){
	//Agent* a = (KheperaIII*) agent_ptr;
	*orientation = k3->getOrientation();
	return 0;
}

