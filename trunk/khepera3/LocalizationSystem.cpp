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
#include "boost/asio.hpp"

#include "Cortex.h"
#include "KheperaIII.h"
#include "LocalizationSystem.h"

using namespace boost;

//int LocalizationSystem::instanceCount = 0;
bool LocalizationSystem::cortexIsConnected = false;
string LocalizationSystem::me = "0.0.0.0";
string LocalizationSystem::me_wifi = "0.0.0.0";
string LocalizationSystem::host ="193.49.136.176";

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
	//std::array<double,5> auxCor;
	
	
	int iBody;
	if (cortexIsConnected) {
		//Cortex_FreeBodyDefs(pBodyDefs);
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
		//Cortex_FreeBodyDefs(pBodyDefs);
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
	//sFrameOfData* pFrameOfData=NULL;
	float* coordFront;
	float* coordMiddle;
	int ack;
	ack = 1;	
	//FindBodyIndex();
	pFrameOfData = Cortex_GetCurrentFrame();
	if (!pFrameOfData) 
		throw(ios_base::failure("Bad data from Cortex"));
	coordMiddle = (&pFrameOfData->BodyData[bodyIndex])->Markers[7];
	coordFront = (&pFrameOfData->BodyData[bodyIndex])->Markers[6];
	if(coordMiddle[0] == 9999999 || coordFront[0] == 9999999) {
		throw(ios_base::failure("Bad data from Cortex"));
	}
	ret[0] = 1;
	ret[1] = (double)coordMiddle[0];//*.1;
	ret[2] = (double)coordMiddle[1];//*.1;
	ret[3] = (double)coordMiddle[2];//*.1;
	aux = atan2((double)(coordFront[1]- coordMiddle[1]),(double)(coordFront[0]- coordMiddle[0]));
	ret[4] = aux;	
	//Cortex_FreeFrame(pFrameOfData); (seems useless ? cortex.h says it is)
	return ret;
}

void LocalizationSystem::Close()
{
	Cortex_Exit();
}

void LocalizationSystem::Open() {	
	asio::io_service ios;
	asio::ip::tcp::resolver resolver(ios);
    asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(),"");
    asio::ip::tcp::resolver::iterator it=resolver.resolve(query);
	asio::ip::address wifi_addr, ethernet_addr,addr;
    while(it!=asio::ip::tcp::resolver::iterator())
    {
        addr=(it++)->endpoint().address();       
		if (addr.to_string().substr(0,3)=="10.")
			me_wifi = addr.to_string();
		else if(addr.to_string().substr(0,4)=="193.")
			me = addr.to_string();
    }
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