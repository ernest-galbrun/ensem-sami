#include "interface.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])

{
	void* p;
	LaunchKhepera(2,2,&p);
	SetSpeed(p,0,2);
	InitLocalizationSystem(p,"127.0.0.1","127.0.0.1");
	double left, right;
	while (true) {
		SetSpeed(p,0,0);
		GetPosition(p,&left, &right);
		cout<< "left : "<<left<<" ; right : "<<right<<".\n";
	}
	return 0;
}