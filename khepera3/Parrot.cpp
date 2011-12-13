#include "Parrot.h"
#include "boost/array.hpp"

extern int instanceCount;

boost::array<double,5> Parrot::GetOwnPosition_Cortex() {//{Ack,X,Y,Z,theta}
	//*orientation = 0; //unimplemented
	//countT++;
	int i = GetBodyIndex();
	boost::array<double,5> ret = { { 0,0,0,0,0 } };
	sFrameOfData* pFrameOfData=NULL;
	float* A;
	float* B;
	pFrameOfData = Cortex_GetCurrentFrame();
	if ((&pFrameOfData->BodyData[i])->nMarkers == 3) {
		A = (&pFrameOfData->BodyData[bodyIndex])->Markers[0];
		B = (&pFrameOfData->BodyData[bodyIndex])->Markers[2];
		ret[0] = 1;
		ret[1] = A[0] +  A[2]* (B[0]-A[0]) / (A[2]-B[2]);
		ret[2] = A[1] +  A[2]* (B[1]-A[1]) / (A[2]-B[2]);
	}				
	else {
		ret[0] = 0;
	}
	return ret;
}

bool Parrot::UpdatePosition(double * frontX, double* frontY, double* frontZ, double* backX, double * backY, double* backZ)
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
	FindBodyIndex("parrot1");
	pFrameOfData = Cortex_GetCurrentFrame();
	coordMiddle = (&pFrameOfData->BodyData[bodyIndex])->Markers[5];
	coordFront = (&pFrameOfData->BodyData[bodyIndex])->Markers[6];
	if(coordMiddle[0] == 9999999 || coordFront[0] == 9999999) {// || off1[0] == 9999999 || off2[0] == 9999999)
		return false;
	}
	*frontX = coordFront[0];	
	*frontY = coordFront[1];	
	*frontZ = coordFront[2];
	*backX = coordMiddle[0];
	*backY = coordMiddle[1];
	*backZ = coordMiddle[2];

	return true;
}
	