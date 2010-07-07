/* This file contains the wrapper c functions exposed in the dll, 
for use with matlab or other third party software*/

//#include "windows.h"

#include "KheperaIII.h"
#include "LocalizationSystem.h"

#include <iostream>
#include <string>

using namespace std;

 extern "C" __declspec(dllexport) int LaunchKhepera(int robotID, int mode, const char* localIP, const char* cortexIP){
	KheperaIII robot(robotID);
	cout<<"Initialising local system...\n";
	robot.localizationSystem->init(mode,1,string(localIP), string(cortexIP), "objectNameCortex");
	return 0;
}