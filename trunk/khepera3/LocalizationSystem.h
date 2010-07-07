#pragma once

#include "EVaRT2.h"
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
	KheperaIII *robot;
	int mode;
	int enable;
	float* previousPosition;
	double previousL;
	double previousR;

	//EVaRT Parameters
	string host;
	string me;
	string name;
	sFrameOfData  MyCopyOfFrame;
	int bodyIndex;
	
public:
	LocalizationSystem(KheperaIII*);
	~LocalizationSystem(void);

	void init(int,int);
	void init(int,int,string,string,string);
	void atualizePosition();
	void Close();
	double* getOwnPosition_EVaRT(); //{Ack,X,Y,Z,theta}

	int countT;
	int countO;
};
