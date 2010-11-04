#pragma once

#include <string>
#include <vector>
#include "Object.h"
#include "TrackGenerator.h"
#include "CommunicationSystem.h"

class Agent : public Object,boost::noncopyable
{
private:
	std::vector<Object> neighbors;
	std::vector<Object> obstacles;
	std::string localAddress;
	CommunicationSystem communicationSystem;	

	int testNeighbor(int idArg);
	void ReceiveContinuously();
protected:
	void LaunchComm();
public:
	Agent(int id);
	~Agent(void);

	TrackGenerator trackGenerator;

	void ReorganizeNeighbors(int idArg, double xArg, double yArg);
	std::vector<Object> getNeighbors();
	std::vector<Object> getObstacles();
	std::string getLocalAddress();
	void SendPosition();

	void setNeighbors(vector<Object>);
	void setObstacles(vector<Object>);
	void setLocalAddres(std::string);
};
