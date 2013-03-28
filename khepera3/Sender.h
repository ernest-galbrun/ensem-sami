#pragma once
#define WIN32_LEAN_AND_MEAN 
#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
//#include "boost/array.hpp"


class Sender
{
	boost::asio::ip::address multicast_address;
	boost::asio::io_service io_service_sender;
	boost::asio::ip::udp::endpoint endpoint_;
	boost::asio::ip::udp::socket socket_;
	int message_count_;
	std::string message_;
	static boost::asio::ip::address GenerateMulticastAddress(int id);

public:
	Sender(int id);

	~Sender(void);
	void sendPosition(int id,const std::array<double,2>& position, const double & orientation);
	void handler_sender(const boost::system::error_code&);
};
