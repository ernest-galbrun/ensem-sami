#include<string>

#ifndef POINT_H
#define POINT_H

using namespace std;

class Point {

	private:

		float x, y, z;
		string name;

	public:

		Point(int x, int y, int z);
		Point(int x, int y, int z, string name);
		float getX();
		float getY();
		float getZ();
		string getName();
		void setName(string name);

};

#endif

