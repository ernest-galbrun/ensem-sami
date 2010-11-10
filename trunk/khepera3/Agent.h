#pragma once

#include <string>
#include <vector>
#include "boost/thread.hpp"
#include "boost/shared_ptr.hpp"
#include "Object.h"
#include "TrackGenerator.h"
#include "CommunicationSystem.h"

class Agent : public Object,boost::noncopyable
{
private:
	std::vector<Object> neighbors;
	std::vector<Object> obstacles;
	std::string localAddress;
	// posX_, posY_ and id_ are c array holding values for every neighbors
	double * posX_;
	double * posY_;
	int* id_;
	CommunicationSystem communicationSystem;	

	int testNeighbor(int idArg);
	void ReceiveContinuously();
	bool stopListening;
	boost::thread listeningThread;
protected:
	void LaunchComm();
public:
	Agent(int id);
	~Agent(void);

	TrackGenerator trackGenerator;

	void ReorganizeNeighbors(int idArg, double xArg, double yArg);
	std::vector<Object> getNeighbors();
	// c friendly getNeighbors function
	void	getNeighbors(int* numberOfNeighbors, int** id, double** x, double** y);
	std::vector<Object> getObstacles();
	std::string getLocalAddress();
	void SendPosition();

	void setNeighbors(vector<Object>);
	void setObstacles(vector<Object>);
	void setLocalAddres(std::string);
};
