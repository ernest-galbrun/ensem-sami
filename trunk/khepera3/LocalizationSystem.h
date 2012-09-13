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
	static string host; //address of medimex computer
	static string me; //address of the computer
	static string me_wifi; // wifi address of the computer
	static bool cortexIsConnected;
	string name;
	//sFrameOfData  MyCopyOfFrame;
	int bodyIndex;
//	static int instanceCount;

public:
	LocalizationSystem();
	~LocalizationSystem(void);

	int GetBodyIndex();
	string GetOwnIP(){return me;};
	string GetOwnIP_wifi(){return me_wifi;};
	void init(int,int);
	void FindBodyIndex();
	void SetName(string bodyName) {name=bodyName;};
	//updates the position given in the input pointers, return false on failure
	void UpdatePosition(std::array<double,2>* position, double* orientation);
	static void Close();
	static void Open(/*string myAddress, string hostAddress*/);
	virtual std::array<double,5> GetOwnPosition_Cortex(); //{Ack,X,Y,Z,theta}

	int countT;
	int countO;
};
