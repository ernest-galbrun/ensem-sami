#pragma once


#include <iostream>
#include <string>
#define WIN32_LEAN_AND_MEAN 
#include "boost/asio.hpp"
#include "boost/bind.hpp"

class Receiver
{
	boost::asio::io_service io_service_receiver;
	boost::asio::io_service io_service_timer;

	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint sender_endpoint_;
	char data_[512];
	boost::system::error_code io_error_;
	boost::system::error_code timer_error_;
	bool timedOut;

	int receivedId;
	boost::array<double,2> receivedPosition;

public:
	Receiver(const boost::asio::ip::address&, const boost::asio::ip::address&,int);
	~Receiver(void);

	//void run();
	void handler_receiver(const boost::system::error_code&, std::size_t);
	void Handler_AsyncTimer( const boost::system::error_code& error);
	// ReceivePosition returns true if a new value was received
	bool ReceivePosition(int& id, boost::array<double,2>& position);
};
