#pragma once

#define WIN32_LEAN_AND_MEAN
#include <string>
#include <stdio.h>
//#include <windows.h>
#include <iostream>

#include <boost/asio.hpp>

class Receiver;
class Sender;
class KheperaIII;
class Agent;
class CommunicationSystem
{
	Receiver *receiver;
	Sender *sender;
	std::string multicastAddress;
	std::string localAddress;
	int multicastPort;
	int enable;
	boost::asio::io_service io_service;
	boost::asio::io_service io_service2;
	KheperaIII *robot;
	int testNeighbor(int);
	void copyNeighbors(Agent*);

public:
	CommunicationSystem(KheperaIII *);
	~CommunicationSystem(void);

	void init(std::string,std::string,int);
	void reorganizeNeighbors(int,double,double);
	void sendPosition();
	
};
