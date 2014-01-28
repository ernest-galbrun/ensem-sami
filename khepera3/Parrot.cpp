#include "Parrot.h"
#include <array>
//#include "boost/array.hpp"

extern int instanceCount;

Parrot::Parrot() {
	SetName("markerset_parrot21");
}

std::array<double,5> Parrot::GetOwnPosition_Cortex() {//{Ack,X,Y,Z,theta}
	//*orientation = 0; //unimplemented
	//countT++;
	int i = GetBodyIndex();
	std::array<double,5> ret = { { 0,0,0,0,0 } };
	sFrameOfData* pFrameOfData=NULL;
	float* A;
	float* B;
	pFrameOfData = Cortex_GetCurrentFrame();
	if ((&pFrameOfData->BodyData[i])->nMarkers == 3) {
		A = (&pFrameOfData->BodyData[bodyIndex])->Markers[0];
		B = (&pFrameOfData->BodyData[bodyIndex])->Markers[1];
		ret[0] = 1;
		ret[1] = A[0] +  A[2]* (B[0]-A[0]) / (A[2]-B[2]);
		ret[2] = A[1] +  A[2]* (B[1]-A[1]) / (A[2]-B[2]);
	}				
	else {
		ret[0] = 0;
	}
	return ret;
}

bool Parrot::UpdatePosition(double * x, double* y, double* z, double* yaw, double * pitch, double* roll)
{
	
	std::array<double,5> ret = { { 0,0,0,0,0 } };
	sFrameOfData* pFrameOfData= nullptr;
	int ack;
	ack = 1;	 
	FindBodyIndex();
	pFrameOfData = Cortex_GetCurrentFrame();
	float* m = (&pFrameOfData->BodyData[bodyIndex])->Markers[1]; //middle
	float* f = (&pFrameOfData->BodyData[bodyIndex])->Markers[0]; //front
	float* bl = (&pFrameOfData->BodyData[bodyIndex])->Markers[4]; //back left
	float* br = (&pFrameOfData->BodyData[bodyIndex])->Markers[5]; //back right
	if(m[0] == 9999999 || f[0] == 9999999 || br[0] == 9999999 || bl[0] == 9999999) {
		return false;
	}
	*x = (m[0]+f[0])/2;
	*y = (m[1]+f[1])/2;	
	*z = (m[2]+f[2])/2;
	*pitch = atan2(f[2]-m[2],sqrt((f[0]-m[0]) * (f[0] - m[0]) + (f[1]-m[1]) * (f[1] - m[1])));
	*yaw = atan2(f[1] - m[1], f[0] - m[0]);
	*roll = atan2(br[2]-bl[2],sqrt((br[0]-bl[0]) * (br[0] - bl[0]) + (br[1]-bl[1]) * (br[1] - bl[1])));

	return true;
}
	