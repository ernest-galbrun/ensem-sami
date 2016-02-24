#include "Point.h"

#ifndef VEHICLE_OBJECT_H
#define VEHICLE_OBJECT_H

class Vehicle_Object{

	private:
		char ** name;
		int * points_number;
		Point ** points;

	public:
		Vehicle_Object(char ** name, float ** float_32_data, int points_number);
		~Vehicle_Object();
		void print_data();
		int getPointsNumber();
		Point ** getPoints();
		char * getName();

};	

#endif
