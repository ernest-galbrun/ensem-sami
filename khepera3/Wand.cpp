#include "Wand.h"
#include "boost/array.hpp"


bool Wand::UpdatePosition(boost::array<double,2>* position, double* orientation) {
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

void Wand::init(string myAddress, string hostAddress, string bodyName,boost::array<double,2>* position, double* orientation){
	sFrameOfData* pFrameOfData=NULL;
	float* coordFront;
	float* coordBack;
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
	int retval;
	if (instanceCount==1) {
		retval = Cortex_Initialize((char*)me.c_str(), (char*)host.c_str());		
	}
	else {
		retval = enable?RC_Okay:RC_GeneralError;
	}
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
					pFrameOfData = Cortex_GetCurrentFrame();
					coordBack = (&pFrameOfData->BodyData[bodyIndex])->Markers[0];
					coordFront = (&pFrameOfData->BodyData[bodyIndex])->Markers[2];
					//auxCor = getOwnPosition_Cortex();
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