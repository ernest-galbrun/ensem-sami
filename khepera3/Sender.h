#pragma once
#define WIN32_LEAN_AND_MEAN 
#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "boost/array.hpp"


class Sender
{
	boost::asio::io_service io_service_sender;
	boost::asio::ip::udp::endpoint endpoint_;
	boost::asio::ip::udp::socket socket_;
	boost::asio::deadline_timer timer_;
	int message_count_;
	std::string message_;

public:
	Sender(const boost::asio::ip::address&,int);

	~Sender(void);
	void sendPosition(int id,const boost::array<double,2>& position);
	void handler_sender(const boost::system::error_code&);
};
