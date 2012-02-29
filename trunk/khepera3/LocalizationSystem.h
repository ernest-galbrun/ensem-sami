#pragma once

#include "Cortex.h"
//#include "boost/array.hpp"
#include "boost/shared_ptr.hpp"

#include <array>
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
	static string host;
	static string me;
	static bool cortexIsConnected;
	string name;
	//sFrameOfData  MyCopyOfFrame;
	int bodyIndex;
//	static int instanceCount;

public:
	LocalizationSystem();
	~LocalizationSystem(void);

	int GetBodyIndex();
	void init(int,int);
	void FindBodyIndex();
	void SetName(string bodyName) {name=bodyName;};
	//updates the position given in the input pointers, return false on failure
	void UpdatePosition(std::array<double,2>* position, double* orientation);
	static void Close();
	static void Open(string myAddress, string hostAddress);
	virtual std::array<double,5> GetOwnPosition_Cortex(); //{Ack,X,Y,Z,theta}

	int countT;
	int countO;
};
