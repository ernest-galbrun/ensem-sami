#pragma once

#define WIN32_LEAN_AND_MEAN
#include <string>
#include <stdio.h>
#include <iostream>
#include <array>
#include "Sender.h"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

class CommunicationSystem:boost::noncopyable
{
	Sender sender;
	std::string multicastAddress;
	std::string localAddress;
	int multicastPort;
	bool enable;
public:
	CommunicationSystem(int id, std::string adMult, int porMult);
	~CommunicationSystem(void);

	//void run();
	void reorganizeNeighbors(int,double,double);
	void sendPosition(int id,const std::tr1::array<double,2>& position);
	bool Enabled();	
};
