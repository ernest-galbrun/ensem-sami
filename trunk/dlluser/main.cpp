#include "interface.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])

{
	void* p;
	LaunchKhepera(2,2,&p);
	//SetSpeed(p,0,2);
	InitLocalizationSystem(p,2,"193.49.136.176","193.49.136.176");
	double x,y,t;
	while (true) {		
		SetSpeed(p,0,1);
		GetPosition(p,&x, &y);
		GetOrientation(p,&t);
		cout<< "X : "<<x<<" ; Y : "<<y<<"Theta : "<<t<<".\n";
	}
	return 0;
}