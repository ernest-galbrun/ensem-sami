#ifndef POINT_H
#define POINT_H

class Point {

	private:

		float x, y, z;
		char ** name;

	public:

		Point(int x, int y, int z);
		Point(int x, int y, int z, char ** name);
		float getX();
		float getY();
		float getZ();
		char * getName();
		void setName(char ** name);

};

#endif

