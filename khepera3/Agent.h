#include <string>
#include "Object.h"
#include "TrackGenerator.h"

#pragma once

using namespace std;

class Agent : public Object
{
private:
	Agent* neighbors;
	int nNeighbors;
	Object* obstacles;
	string localAddress;
public:
	Agent(void);
	~Agent(void);

	TrackGenerator* trackGenerator;

	Agent* getNeighbors();
	Object* getObstacles();
	string getLocalAddress();
	int getnNeighbors();

	void setnNeighbors(int);
	void setNeighbors(Agent*);
	void setObstacles(Object*);
	void setLocalAddres(string);
};
