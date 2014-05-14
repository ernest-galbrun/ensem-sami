#include "Wand.h"
#include <array>
//#include "boost/array.hpp"

extern int instanceCount;

Wand::Wand(){
	SetName("wand500");
}

std::array<double,5> Wand::GetOwnPosition_Cortex() {//{Ack,X,Y,Z,theta}
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

void Wand::UpdateOrientation(double* X,double *Y,double *Z,double *x1,double *y1, double *z1){
	int i = GetBodyIndex();
	std::array<double,5> ret = { { 0,0,0,0,0 } };
	sFrameOfData* pFrameOfData=NULL;
	float* A;
	float* B;
	pFrameOfData = Cortex_GetCurrentFrame();
	if ((&pFrameOfData->BodyData[i])->nMarkers == 3) {
		A = (&pFrameOfData->BodyData[bodyIndex])->Markers[0];
		B = (&pFrameOfData->BodyData[bodyIndex])->Markers[2];
		double dx = B[0] - A[0];
		double dy = B[1] - A[1];
		double dz = B[2] - A[2];
		double norm = sqrt(dx*dx + dy*dy + dz*dz);
		*X = dx/norm;
		*Y = dy/norm;
		*Z = dz/norm;
		*x1 = A[0];
		*y1 = A[1];
		*z1 = A[2];
	}					
}

