#include "Cortex.h"
#include <iostream>

using namespace std;

int main(void){
	Cortex_Initialize("193.49.136.189", "193.49.136.176");
	sBodyDefs* pBodyDefs;
	sFrameOfData* pFrameOfData;	
	pFrameOfData = Cortex_GetCurrentFrame();
	if (!pFrameOfData) 
		throw(ios_base::failure("Bad data from Cortex"));
}