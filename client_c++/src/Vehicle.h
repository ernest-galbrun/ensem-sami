#ifndef VEHICLE_H
#define VEHICLE_H

#include "Point.h"
#include <stdio.h>
#include<vector>
#include<string>

using namespace std;

class Vehicle {

	private:
		string name;
		vector<Point> points;

	public:
		Vehicle();
		Vehicle(string name, vector<float> float_32_data);
		void print_data();
		void setPointsNames(vector<string> pointsNames);
		vector<Point> getPoints();
		string getName();

};

#endif
