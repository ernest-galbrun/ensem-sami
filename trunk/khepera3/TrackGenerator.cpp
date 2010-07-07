#include <time.h>
#include <iostream>

#include "DEFINITIONS.h"
#include "TrackGenerator.h"

//CONSTRUCTOR AND DESTRUCTOR----------------------------------
TrackGenerator::TrackGenerator(void)
{
}

TrackGenerator::~TrackGenerator(void)
{
}

//GETS--------------------------------------------------------
double* TrackGenerator::getDesiredPosition()
{
	return desiredPosition;
}

int TrackGenerator::getMode()
{
	return mode;
}

//SETS--------------------------------------------------------
void TrackGenerator::setDesiredPosition(double *desiredPositionArg)
{
	desiredPosition = desiredPositionArg;
}

void TrackGenerator::setMode(int modeArg)
{
	mode = modeArg;
}

//FUNCTIONAL METHODS------------------------------------------
void TrackGenerator::init(int modeArg)
{
	

	if(modeArg==2)
	{
	desiredPosition = (double *)malloc(2*sizeof(double));
	desiredPosition[0] = OSX;
	desiredPosition[1] = OSY;
	mode = modeArg;
	tickCount = clock();
	}
	
}

void TrackGenerator::nextStep()
{
	if(mode==2)
	{
		desiredPosition[0] = KX*(clock()-tickCount)/((double)CLOCKS_PER_SEC) +OSX;
		desiredPosition[1] = KY*(clock()-tickCount)/((double)CLOCKS_PER_SEC) +OSY;
	}
}