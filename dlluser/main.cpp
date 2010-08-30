#include "interface.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])

{
	void* p;

	LaunchKhepera(2);
	DeleteKhepera(2);
	//SetSpeed(p,0,2);
	InitLocalizationSystem(2,1,"193.49.136.176","193.49.136.176");
	double x,y,t;
	while (true) {		
		SetSpeed(2,0,1);
		GetPosition(2,&x, &y);
		GetOrientation(2,&t);
		cout<< "X : "<<x<<" ; Y : "<<y<<"Theta : "<<t<<".\n";
	}
	return 0;
}