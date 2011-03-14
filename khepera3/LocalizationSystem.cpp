#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <tchar.h>
//#include <windows.h>
#include <sstream>
#include <math.h>

#include "boost/thread.hpp"

#include "Cortex.h"
#include "KheperaIII.h"
#include "LocalizationSystem.h"

LocalizationSystem::LocalizationSystem():
	enable(false)
	//robot(robotArg)
{
	//robot = robotArg;
	//previousPosition = (float*)malloc(3*(sizeof(float)));
	//enable = 0;
}

LocalizationSystem::~LocalizationSystem(void)
{
	Cortex_Exit();
}

void LocalizationSystem::init(string myAddress, string hostAddress, string bodyName, boost::array<double,2>* position, double* orientation)
{
	countT = 0;
	countO = 0;
	bool bodyNameFound = false;
	boost::array<double,5> auxCor;
	sHostInfo Cortex_HostInfo;
	
	sBodyDefs* pBodyDefs=NULL;
	int iBody;
	me = myAddress;
	host = hostAddress;
	name = bodyName;

	//INITIALIZING EVaRT
	memset(&MyCopyOfFrame, 0, sizeof(sFrameOfData));
	Cortex_SetVerbosityLevel(VL_None);		
	printf("Connecting to Cortex Host...\n");
	int retval = Cortex_Initialize((char*)me.c_str(), (char*)host.c_str());		
	if (retval != RC_Okay)
	{
		enable =false;
		throw (ios_base::failure("Unable to initialize ethernet communication."));
	}
	else
	{
		retval = Cortex_GetHostInfo(&Cortex_HostInfo);    
		if (retval != RC_Okay || !Cortex_HostInfo.bFoundHost)
		{
			enable =0;
			throw (ios_base::failure("Unable to find Cortex dll runing."));
		}
		else
		{
		pBodyDefs = Cortex_GetBodyDefs();
			for (iBody=0; iBody<pBodyDefs->nBodyDefs; iBody++)
			{
				sBodyDef *pBody = &pBodyDefs->BodyDefs[iBody];
				char* aux = pBody->szName;
				if(strncmp (aux,name.c_str(),strlen(aux))==0)
				{
					bodyIndex = iBody;
					bodyNameFound = true;
					auxCor = getOwnPosition_Cortex();
					if(auxCor[0]==1)
					{
						(*position)[0] = auxCor[1];
						(*position)[1] = auxCor[2];
						*orientation = auxCor[4];
						printf("Done!!!\n");
							
					}
					else
					{
						enable =0;
						throw (ios_base::failure("In the first iteration ALL markers of the template must be valid."));
					}
				}
					
			}
			if(!bodyNameFound)
			{
				enable =0;
				throw (ios_base::failure("Unable to find body with provided name."));
			}
		}
	}
}


bool LocalizationSystem::UpdatePosition(boost::array<double,2>* position, double* orientation)
{
	countT++;
	boost::array<double,5> auxCor;
	auxCor = getOwnPosition_Cortex();
	if(auxCor[0]==1)
	{
		countO++;
		//printf("Ct: %d Co: %d\n",countT, countO);
		(*position)[0] = auxCor[1];
		(*position)[1] = auxCor[2];
		*orientation = auxCor[4];
		return true;
	}
	else
	{
		return false;
	}
}
	
boost::array<double,5> LocalizationSystem::getOwnPosition_Cortex()
{
	boost::array<double,5> ret = { { 0,0,0,0,0 } };
	double aux;
	sFrameOfData* pFrameOfData=NULL;
	float* coordFront;
	float* coordMiddle;
	float* off1;
	float* off2;
	int ack;

	ack = 1;
	
	pFrameOfData = Cortex_GetCurrentFrame();
	coordMiddle = (&pFrameOfData->BodyData[bodyIndex])->Markers[7];
	coordFront = (&pFrameOfData->BodyData[bodyIndex])->Markers[6];

	//off1 = (&pFrameOfData->BodyData[bodyIndex])->Markers[1];
	//off2 = (&pFrameOfData->BodyData[bodyIndex])->Markers[3];

	//printf("Xm: %f Xf: %f\n",coordMiddle[0],coordFront[0]);
	//Verify th integrity of the markers
	if(coordMiddle[0] == 9999999 || coordFront[0] == 9999999)// || off1[0] == 9999999 || off2[0] == 9999999)
	{
		ack =0;
	}

	else
	{
		ack = 1;
	}
	 
	
	ret[0] = ack;
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