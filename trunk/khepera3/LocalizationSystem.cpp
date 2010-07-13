#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <tchar.h>
//#include <windows.h>
#include <sstream>
#include <math.h>

#include "boost/thread.hpp"

#include "EVaRT2.h"
#include "KheperaIII.h"
#include "LocalizationSystem.h"

LocalizationSystem::LocalizationSystem(KheperaIII* robotArg)
{
	robot = robotArg;
	previousPosition = (float*)malloc(3*(sizeof(float)));
	enable = 0;
}

LocalizationSystem::~LocalizationSystem(void)
{
}

void LocalizationSystem::init(int modeArg, int autoAtualize)
{
	mode = modeArg;
	
	enable = autoAtualize;

	previousL= X0;
	previousR= Y0;
	if(mode == 1)
	{
		robot->setPosition(X0,Y0);
		robot->setOrientation(THETA0);

		robot->setEncodersValue(0,0);
	}
	if(mode == 2)
	{
		printf("ERROR: For this mode, please use LocalizationSystem::init(int,int,string,string,string\n");
		exit(0);
	}
	if(mode == 3)
	{
		//TODO
	}	
}




void LocalizationSystem::init(int modeArg, int autoAtualize, string myAddress, string hostAddress, string bodyName)
{

	previousL= X0;
	previousR= Y0;
	countT = 0;
	countO = 0;
	int test = 0;
	mode = modeArg;
	enable = autoAtualize;
	double *auxCor;
	sHostInfo EVaRT_HostInfo;
	
	sBodyDefs* pBodyDefs=NULL;
	int iBody;

	
	if(mode == 1)
	{
		robot->setPosition(X0,Y0);
		robot->setOrientation(THETA0);

		robot->setEncodersValue(0,0);
	}
	if(mode == 2 || mode == 3)
	{		
		robot->setEncodersValue(0,0);

		me = myAddress;
		host = hostAddress;
		name = bodyName;

		//INITIALIZING EVaRT
		memset(&MyCopyOfFrame, 0, sizeof(sFrameOfData));
		EVaRT2_SetVerbosityLevel(VL_None);
		
		printf("Connecting to Evart Host...\n");
		int retval = EVaRT2_Initialize((char*)me.c_str(), (char*)host.c_str());
		
		
		if (retval != RC_Okay)
		{
			enable =0;printf("Error: Unable to initialize ethernet communication.\n");
			exit(0);
		}
		else
		{
			retval = EVaRT2_GetHostInfo(&EVaRT_HostInfo);
    
			if (retval != RC_Okay || !EVaRT_HostInfo.bFoundHost)
			{
				enable =0;printf("Error: Unable to find EVaRT.\n");
				exit(0);
				
			}
			else
			{
			pBodyDefs = EVaRT2_GetBodyDefs();
				for (iBody=0; iBody<pBodyDefs->nBodyDefs; iBody++)
				{
					sBodyDef *pBody = &pBodyDefs->BodyDefs[iBody];
					char* aux = pBody->szName;
					if(strncmp (aux,name.c_str(),strlen(aux))==0)
					{
						bodyIndex = iBody;
						test  = 1;
						auxCor = getOwnPosition_EVaRT();
						if(auxCor[0]==1)
						{
							robot->setPosition(auxCor[1],auxCor[2]);
							robot->setOrientation(auxCor[4]);
							printf("Done!!!\n");
							
						}
						else
						{
							enable =0;printf("Error: In the first iteration ALL markers of the must be valid.\n");
							exit(0);
							
						}
					}
					
				}
				if(test==0)
				{enable =0;printf("Error: Unable to find body with provided name.\n");exit(0);}
			}
		}
	}	
}


void LocalizationSystem::atualizePosition()
{
	countT++;

	double* auxCor;

	if(enable == 1)
	{
		
		if(mode==1)
		{
			double dl, dr, dc, thetaAux, xAux, yAux;
			int* encoders = robot->getEncodersValue();
			dl = (encoders[0]-previousL)*K_ENCODER;
			dr = (encoders[1]-previousR)*K_ENCODER;
			dc = (dl+dr)/2;
			thetaAux = robot->getOrientation();

			robot->setOrientation(robot->getOrientation() + (dr-dl)/AXIS);

			
			xAux = robot->getPosition()[0] + dc*cos( (robot->getOrientation() + thetaAux)/2);
			yAux = robot->getPosition()[1] + dc*sin( (robot->getOrientation() + thetaAux)/2);
			robot->setPosition(xAux,yAux);

			if(robot->getOrientation() < 0)
			{
				robot->setOrientation(2*PI + robot->getOrientation());
			}
			if(robot->getOrientation() > 2*PI)
			{
				robot->setOrientation(robot->getOrientation() - 2*PI);
			}
			
						
			
			previousL= encoders[0];
			previousR= encoders[1];
			//robot->setEncodersValue(0,0);

		}
		if(mode==2)
		{
			auxCor = getOwnPosition_EVaRT();
			if(auxCor[0]==1)
			{
				countO++;
				//printf("Ct: %d Co: %d\n",countT, countO);
				robot->setPosition(auxCor[1],auxCor[2]);
				robot->setOrientation(auxCor[4]);

				int* encoders = robot->getEncodersValue();
				previousL= encoders[0];
				previousR= encoders[1];
			}
			else
			{
				//printf("MARKER LOSS\n");
				double dl, dr, dc, thetaAux, xAux, yAux;
				int* encoders = robot->getEncodersValue();
				dl = (encoders[0]-previousL)*K_ENCODER;
				dr = (encoders[1]-previousR)*K_ENCODER;
				dc = (dl+dr)/2;
				thetaAux = robot->getOrientation();

				robot->setOrientation(robot->getOrientation() + (dr-dl)/AXIS);

				if(robot->getOrientation() < 0)
				{
					robot->setOrientation(2*PI + robot->getOrientation());
				}
				if(robot->getOrientation() > 2*PI)
				{
					robot->setOrientation(robot->getOrientation() - 2*PI);
				}
				
				xAux = robot->getPosition()[0] + dc*cos( (robot->getOrientation() + thetaAux)/2);
				yAux = robot->getPosition()[1] + dc*sin( (robot->getOrientation() + thetaAux)/2);
							
				robot->setPosition(xAux,yAux);
				
				previousL= encoders[0];
				previousR= encoders[1];
			}
		}
		if(mode==3)
		{
		}
	}
}



double* LocalizationSystem::getOwnPosition_EVaRT()
{
	double* ret = new double[5];
	double aux;
	sFrameOfData* pFrameOfData=NULL;
	float* coordFront;
	float* coordMiddle;
	float* off1;
	float* off2;
	int ack;

	ack = 1;
	
	pFrameOfData = EVaRT2_GetCurrentFrame();
	coordMiddle = (&pFrameOfData->BodyData[bodyIndex])->Markers[0];
	coordFront = (&pFrameOfData->BodyData[bodyIndex])->Markers[2];

	off1 = (&pFrameOfData->BodyData[bodyIndex])->Markers[1];
	off2 = (&pFrameOfData->BodyData[bodyIndex])->Markers[3];

	//printf("Xm: %f Xf: %f\n",coordMiddle[0],coordFront[0]);
	//Verify th integrity of the markers
	if(coordMiddle[0] == 9999999 || coordFront[0] == 9999999 || off1[0] == 9999999 || off2[0] == 9999999)
	{
		ack =0;
	}

	else
	{
		ack = 1;
	}
	 
	
	ret[0] = ack;
	ret[1] = (double)coordMiddle[0]*.1;
	ret[2] = (double)coordMiddle[1]*.1;
	ret[3] = (double)coordMiddle[2]*.1;
	aux = atan2((double)(coordFront[1]- coordMiddle[1]),(double)(coordFront[0]- coordMiddle[0]));
	if(aux<0)
	{
		aux = aux+ 2*PI; 
	}
	ret[4] = aux;
	
	//printf("Ack: %f x: %f y: %f z: %f t: %f\n",ret[0],ret[1],ret[2],ret[3],ret[4]);
	return ret;
}

void LocalizationSystem::Close()
{
	EVaRT2_Exit();
}