#include "Agent.h"


//CONSTRUCTOR AND DESTRUCTOR----------------------------------
Agent::Agent(void)
{
	trackGenerator = new TrackGenerator();
	localAddress = "1.1.1.1";
	nNeighbors = 0;
	neighbors = NULL;
	obstacles = NULL;
}

Agent::~Agent(void)
{
	delete trackGenerator;
}

//GETS--------------------------------------------------------
Agent* Agent::getNeighbors()
{
	return neighbors;
}

Object* Agent::getObstacles()
{
	return obstacles;
}

string Agent::getLocalAddress()
{
	return localAddress;
}

int Agent::getnNeighbors()
{
	return nNeighbors;
}

//SETS--------------------------------------------------------
void Agent::setNeighbors(Agent *neighborsArg)
{
	neighbors = neighborsArg;
}

void Agent::setObstacles(Object *obstaclesArg)
{
	obstacles = obstaclesArg;
}

void Agent::setLocalAddres(string localAddressArg)
{
	localAddress = localAddressArg;
}

void Agent::setnNeighbors(int nArg)
{
	nNeighbors = nArg;
}

//FUNCTIONAL METHODS------------------------------------------