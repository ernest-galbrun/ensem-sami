#pragma once
#define WIN32_LEAN_AND_MEAN 
#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"


class Sender
{
	boost::asio::ip::udp::endpoint endpoint_;
	boost::asio::ip::udp::socket socket_;
	boost::asio::deadline_timer timer_;
	int message_count_;
	std::string message_;

public:
	Sender(boost::asio::io_service&, const boost::asio::ip::address&,int);

	~Sender(void);
	void sendPosition(int,double,double);
	void handler_sender(const boost::system::error_code&);
};
