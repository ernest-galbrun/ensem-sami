#include "Agent.h"
#include "Object.h"

#include <vector>

#include "boost/thread.hpp"

using namespace boost;

//CONSTRUCTOR AND DESTRUCTOR----------------------------------
Agent::Agent(int id):
	trackGenerator(),
	localAddress("1.1.1.1"),
	neighbors(vector<Object>()),
	obstacles(vector<Object>()),
	communicationSystem(id, "239.255.0.1", 5090),
	stopListening(false)
{
}

Agent::~Agent(void)
{
	stopListening = true;
  	listeningThread.join();
}

//GETS--------------------------------------------------------
vector<Object> Agent::getNeighbors()
{
	return neighbors;
}

vector<Object> Agent::getObstacles()
{
	return obstacles;
}

string Agent::getLocalAddress()
{
	return localAddress;
}

//SETS--------------------------------------------------------
void Agent::setNeighbors(vector<Object> neighborsArg)
{
	neighbors = neighborsArg;
}

void Agent::setObstacles(vector<Object> obstaclesArg)
{
	obstacles = obstaclesArg;
}

void Agent::setLocalAddres(string localAddressArg)
{
	localAddress = localAddressArg;
}


void Agent::ReorganizeNeighbors(int idArg, double xArg, double yArg)
{	
	if(getId() != idArg && communicationSystem.Enabled())
	{		
		int index = testNeighbor(idArg);			
		if(index != -1) // neighbor already exist
		{				
			neighbors[index].setPosition(xArg,yArg);
		}
		else //new neighbor
		{
			Object newcomer;
			newcomer.setId(idArg);
			newcomer.setPosition(xArg,yArg);
			neighbors.push_back(newcomer);
		}
	}
}

int Agent::testNeighbor(int idArg)
{
	int ret = -1;
	for(unsigned int i=0;i < neighbors.size();++i)
	{
		if((neighbors[i]).getId() == idArg)
		{ret = i;}
	}
	return ret;
}

void Agent::SendPosition() {
	communicationSystem.sendPosition(getId(),getPosition());
}


void Agent::LaunchComm()
{
	//boost::thread thr(boost::bind(&CommunicationSystem::run,&communicationSystem));
	listeningThread = thread(&Agent::ReceiveContinuously, this);
}

void Agent::ReceiveContinuously() {
	while(!stopListening) {
		int id;
		boost::array<double,2> position;
		if	(communicationSystem.ReceivePosition(id,position)) {
			ReorganizeNeighbors(id,position[0],position[1]);
		} 		
	}
}