#include "Agent.h"


//CONSTRUCTOR AND DESTRUCTOR----------------------------------
Agent::Agent(void)
{
	trackGenerator = new TrackGenerator();
	nNeighbors = 0;
}

Agent::~Agent(void)
{
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