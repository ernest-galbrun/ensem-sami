#pragma once

#define WIN32_LEAN_AND_MEAN
#include <string>
#include <stdio.h>
//#include <windows.h>
#include <iostream>

#include "Receiver.h"
#include "Sender.h"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/utility.hpp>

class CommunicationSystem:boost::noncopyable
{
	Receiver receiver;
	Sender sender;
	std::string multicastAddress;
	std::string localAddress;
	int multicastPort;
	bool enable;
	//boost::shared_ptr<KheperaIII> robot;
public:
	CommunicationSystem(int id, std::string adMult, int porMult);
	~CommunicationSystem(void);

	//void run();
	void reorganizeNeighbors(int,double,double);
	void sendPosition(int id,const boost::array<double,2>& position);
	bool ReceivePosition(int& id, boost::array<double,2>& position);
	bool Enabled();	
};
