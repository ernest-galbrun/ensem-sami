#include <stdlib.h>


#pragma once

class Object
{
private:
	int id;
	double *position;
	double orientation;
public:
	Object(void);
	~Object(void);
	void setId(int);
	int getId();
	void setPosition(double,double);
	double* getPosition();
	void setOrientation(double);
	double getOrientation();
};
