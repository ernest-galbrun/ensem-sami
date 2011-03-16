#include "Wand.h"
#include "boost/array.hpp"


bool Wand::UpdatePosition(boost::array<double,2>* position, double* orientation) {
	*orientation = 0; //unimplemented
	countT++;
	sFrameOfData* pFrameOfData=NULL;
	float* A;
	float* B;
	pFrameOfData = Cortex_GetCurrentFrame();
	if ((&pFrameOfData->BodyData[bodyIndex])->nMarkers == 3) {
		A = (&pFrameOfData->BodyData[bodyIndex])->Markers[0];
		B = (&pFrameOfData->BodyData[bodyIndex])->Markers[2];
		(*position)[0] = A[0] +  A[2]* (B[0]-A[0]) / (A[2]-B[2]);
		(*position)[1] = A[1] +  A[2]* (B[1]-A[1]) / (A[2]-B[2]);
	}				
	else {
		throw (ios_base::failure("One or more marker missing."));
	}
}

void Wand::init(string myAddress, string hostAddress, string bodyName,boost::array<double,2>* position, double* orientation){
	*orientation = 0; //unimplemented
	sFrameOfData* pFrameOfData=NULL;
	float* A;
	float* B;
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
					if ((&pFrameOfData->BodyData[bodyIndex])->nMarkers == 3) {
					A = (&pFrameOfData->BodyData[bodyIndex])->Markers[0];
					B = (&pFrameOfData->BodyData[bodyIndex])->Markers[2];
					(*position)[0] = A[0] +  A[2]* (B[0]-A[0]) / (A[2]-B[2]);
					(*position)[1] = A[1] +  A[2]* (B[1]-A[1]) / (A[2]-B[2]);
					}				
					else {
						throw (ios_base::failure("One or more marker missing."));
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