#pragma once


#include <iostream>
#include <string>
#define WIN32_LEAN_AND_MEAN 
#include <boost/asio.hpp>
#include "boost/bind.hpp"

class CommunicationSystem;

class Receiver
{
	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint sender_endpoint_;
	enum { max_length = 1024 };
	char data_[max_length];
	CommunicationSystem *comm;

public:
	Receiver(boost::asio::io_service& , const boost::asio::ip::address&, const boost::asio::ip::address&,int,CommunicationSystem*);
	~Receiver(void);

	void run();
	void handler_receiver(const boost::system::error_code&,size_t);

};
