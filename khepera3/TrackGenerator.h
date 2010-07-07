#include <stdlib.h>

#include "DEFINITIONS.h"

#pragma once

/*
Mode: Type of Track
1- Simple Point
2- Straight
*/
class TrackGenerator
{
private:
	double* desiredPosition;
	int tickCount;
	int mode;

public:
	TrackGenerator(void);
	~TrackGenerator(void);

	double* getDesiredPosition();
	int getMode();

	void setDesiredPosition(double*);
	void setMode(int);

	void init(int);
	void nextStep();
};
