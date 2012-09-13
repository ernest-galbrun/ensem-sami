#include "../Matlab/@khepera3/khepera3clib.h"
#include "boost/date_time.hpp"
#include "boost/thread.hpp"
#include <iostream>
#include <ostream>
#include <fstream>
#include <time.h>

using namespace std;
using namespace boost;

int main(int argc, char* argv[])

{
	double X;
	double Y;
	OpenCortex();
	GetWandPosition(&X, &Y);
	GetWandPosition(&X, &Y);
	GetWandPosition(&X, &Y);
	GetWandPosition(&X, &Y);
	CloseCortex();
	ofstream log("log.txt");
	cout.rdbuf(log.rdbuf());
	LaunchKhepera(6,false,0,0,0);
	//LaunchKhepera(22,true);
	//posix_time::time_duration timeStamp;
	//posix_time::ptime begin(posix_time::microsec_clock::local_time());

	InitLocalizationSystem(6,1);
	//InitLocalizationSystem(22,1,"193.49.136.186","193.49.136.176");
	int n;
	int* id;
	double* x;
	double* y;
	//int* ir;
	//GetAmbientIR(6,&ir);
	GetNeighbors(6, &n, &id, &x, &y);
	//DeleteKhepera(1);
	//double x,y,t,lastx, lasty;
	//x=0;
	//y=0;
	//t=0;
	//lastx = 0;
	//lasty = 0;
	//clock_t begin=clock();
	//clock_t timeStamp, duration;
	//SetSpeed(1,30,1);
	//for(int i=0;i<100;i++) {
	//	this_thread::sleep(boost::posix_time::milliseconds(0));
	//	//timeStamp = posix_time::microsec_clock::local_time() - begin;
	//	timeStamp= clock();
	//	duration = timeStamp - begin;


	//	GetPosition(1,&x, &y);
	//	GetOrientation(1,&t);
	//	if (x != lastx)
	//		cout <<"t : " << duration * 1000 / CLOCKS_PER_SEC << "\tX : "<<x<<"\tY : "<<y<<"\tTheta : "<<t<<"\n";
	//	lastx = x;
	//}
	//log.close();
	return 0;
}