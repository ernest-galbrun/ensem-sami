#pragma once

#include "Cortex.h"
#include "boost/array.hpp"
#include "boost/shared_ptr.hpp"
class KheperaIII;

/*
Modes:
1- Purely encoder estimation
2- Purely positioning system
3- Mixed

autoAtualize:
1- enabled
2- disabled
*/

using namespace std;

class LocalizationSystem
{
	//boost::shared_ptr<KheperaIII> robot;
protected:	
	bool enable;

	//Cortex Parameters
	string host;
	string me;
	string name;
	sFrameOfData  MyCopyOfFrame;
	int bodyIndex;
	static int instanceCount;

public:
	LocalizationSystem();
	~LocalizationSystem(void);

	void init(int,int);
	virtual void init(string myAddress, string hostAddress, string bodyName,boost::array<double,2>* position, double* orientation);
	//updates the position given in the input pointers, return false on failure
	virtual bool UpdatePosition(boost::array<double,2>* position, double* orientation);
	void Close();
	boost::array<double,5> getOwnPosition_Cortex(); //{Ack,X,Y,Z,theta}

	int countT;
	int countO;
};
