#include "interface.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])

{
	void* p;
	LaunchKhepera(2);
	//SetSpeed(p,0,2);
	InitLocalizationSystem(1,"193.49.136.176","193.49.136.176");
	double x,y,t;
	while (true) {		
		SetSpeed(0,1);
		GetPosition(&x, &y);
		GetOrientation(&t);
		cout<< "X : "<<x<<" ; Y : "<<y<<"Theta : "<<t<<".\n";
	}
	return 0;
}