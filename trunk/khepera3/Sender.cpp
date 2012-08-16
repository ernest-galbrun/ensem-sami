#include "Sender.h"

#define WIN32_LEAN_AND_MEAN 
#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

Sender::Sender(const boost::asio::ip::address& multicast_address,int multicast_port): 
	io_service_sender(),
	endpoint_(boost::asio::ip::address::from_string("10.10.10.105")/*multicast_address*/, multicast_port), 
	endpoint_bis(multicast_address, multicast_port), 
	socket_(io_service_sender), 
	timer_(io_service_sender)
{
	socket_.open(endpoint_.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(endpoint_);
    // Join the multicast group.
    socket_.set_option(boost::asio::ip::multicast::join_group(boost::asio::ip::address::from_string("239.255.0.1")));
}

Sender::~Sender(void)
{
}

void Sender::sendPosition(int id,const std::array<double,2>& position, const double & orientation)
{
	std::ostringstream os;
    os << id <<","<<position[0]<<","<<position[1]<<","<<orientation;
	std::string message_ = os.str();
	socket_./*async_*/send_to(boost::asio::buffer(message_), endpoint_bis/*, boost::bind(&Sender::handler_sender, this, boost::asio::placeholders::error)*/);
}

void Sender::handler_sender(const boost::system::error_code& error)
{}