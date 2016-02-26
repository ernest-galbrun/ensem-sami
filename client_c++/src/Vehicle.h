#include "Point.h"

#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle {

	private:
		char ** name;
		int * points_number;
		Point ** points;

	public:
		Vehicle(char ** name, float ** float_32_data, int points_number);
		~Vehicle();
		void print_data();
		int getPointsNumber();
		Point ** getPoints();
		char * getName();

};

#endif
