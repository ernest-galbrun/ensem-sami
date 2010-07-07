#include "Sender.h"

#define WIN32_LEAN_AND_MEAN 
#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

Sender::Sender(boost::asio::io_service& io_service, const boost::asio::ip::address& multicast_address,int multicast_port) : endpoint_(multicast_address, multicast_port), socket_(io_service, endpoint_.protocol()), timer_(io_service)
{
}

Sender::~Sender(void)
{
}

void Sender::sendPosition(int id,double x,double y)
{
	std::ostringstream os;
    os << id <<","<<x<<","<<y;
	std::string message_ = os.str();

	socket_.async_send_to(boost::asio::buffer(message_), endpoint_, boost::bind(&Sender::handler_sender, this, boost::asio::placeholders::error));

}

void Sender::handler_sender(const boost::system::error_code& error)
{}