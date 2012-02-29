#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <tchar.h>
//#include <windows.h>
#include <sstream>
#include <math.h>
#include <array>

#include "boost/thread.hpp"

#include "Cortex.h"
#include "KheperaIII.h"
#include "LocalizationSystem.h"

//int LocalizationSystem::instanceCount = 0;
bool LocalizationSystem::cortexIsConnected = false;
string LocalizationSystem::me = "0.0.0.0";
string LocalizationSystem::host ="0.0.0.0";

//extern int instanceCount;

LocalizationSystem::LocalizationSystem():
	enable(false)
	//robot(robotArg)
{
	//instanceCount++;
	//robot = robotArg;
	//previousPosition = (float*)malloc(3*(sizeof(float)));
	//enable = 0;
}

LocalizationSystem::~LocalizationSystem(void)
{
	//instanceCount--;
	//if(instanceCount==0) {
	//	LocalizationSystem::Close();
	//}
}

void LocalizationSystem::FindBodyIndex()
{
	countT = 0;
	countO = 0;
	bool bodyNameFound = false;
	std::array<double,5> auxCor;
	
	sBodyDefs* pBodyDefs=NULL;
	int iBody;
	if (cortexIsConnected) {
	pBodyDefs = Cortex_GetBodyDefs();
		for (iBody=0; iBody<pBodyDefs->nBodyDefs; iBody++) {
			sBodyDef *pBody = &pBodyDefs->BodyDefs[iBody];
			char* aux = pBody->szName;
			if(strncmp (aux,name.c_str(),strlen(aux))==0) {
				bodyIndex = iBody;
				bodyNameFound = true;
			}					
		}
		if(!bodyNameFound) {
			enable =0;
			throw (ios_base::failure("Unable to find body with provided name."));
		}
	}
}


void LocalizationSystem::UpdatePosition(std::array<double,2>* position, double* orientation)
{
	countT++;
	std::array<double,5> auxCor;
	auxCor = GetOwnPosition_Cortex();
	countO++;
	(*position)[0] = auxCor[1];
	(*position)[1] = auxCor[2];
	*orientation = auxCor[4];
}
	
std::array<double,5> LocalizationSystem::GetOwnPosition_Cortex()
{
	std::array<double,5> ret = { { 0,0,0,0,0 } };
	double aux;
	sFrameOfData* pFrameOfData=NULL;
	float* coordFront;
	float* coordMiddle;
	float* off1;
	float* off2;
	int ack;
	ack = 1;	
	FindBodyIndex();
	pFrameOfData = Cortex_GetCurrentFrame();
	if (!pFrameOfData) 
		throw(ios_base::failure("Bad data from Cortex"));
	coordMiddle = (&pFrameOfData->BodyData[bodyIndex])->Markers[7];
	coordFront = (&pFrameOfData->BodyData[bodyIndex])->Markers[6];
	if(coordMiddle[0] == 9999999 || coordFront[0] == 9999999) {// || off1[0] == 9999999 || off2[0] == 9999999)
		throw(ios_base::failure("Bad data from Cortex"));
	}
	ret[0] = 1;
	ret[1] = (double)coordMiddle[0];//*.1;
	ret[2] = (double)coordMiddle[1];//*.1;
	ret[3] = (double)coordMiddle[2];//*.1;
	aux = atan2((double)(coordFront[1]- coordMiddle[1]),(double)(coordFront[0]- coordMiddle[0]));
	/*if(aux<0)
	{
		aux = aux+ 2*PI; 
	}*/
	ret[4] = aux;	
	//printf("Ack: %f x: %f y: %f z: %f t: %f\n",ret[0],ret[1],ret[2],ret[3],ret[4]);
	return ret;
}

void LocalizationSystem::Close()
{
	Cortex_Exit();
}

void LocalizationSystem::Open(string myAddress, string hostAddress) {	
	host = hostAddress;
	me = myAddress;
	sHostInfo Cortex_HostInfo;
	Cortex_SetVerbosityLevel(VL_None);		
	printf("Connecting to Cortex Host...\n");
	int retval;
	retval = Cortex_Initialize((char*)me.c_str(), (char*)host.c_str());		
	if (retval != RC_Okay)	{
		cortexIsConnected = false;
		throw (ios_base::failure("Unable to initialize ethernet communication."));
	}
	else	{
		retval = Cortex_GetHostInfo(&Cortex_HostInfo);    
		if (retval != RC_Okay || !Cortex_HostInfo.bFoundHost)		{
			cortexIsConnected =  false;
			throw (ios_base::failure("Unable to find Cortex dll runing."));
		}
		else {
			cortexIsConnected = true;
		}
	}
}

int LocalizationSystem::GetBodyIndex() {
	return bodyIndex;
}