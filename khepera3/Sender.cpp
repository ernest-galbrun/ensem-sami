#include "Sender.h"

#define WIN32_LEAN_AND_MEAN 
#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

using namespace boost;
using namespace std;

Sender::Sender(const boost::asio::ip::address& multicast_address,int multicast_port): 
	io_service_sender(),
	endpoint_(boost::asio::ip::address::from_string("239.255.0.1"), 30001), 
	socket_(io_service_sender, endpoint_.protocol())
{    
	//socket_.open(endpoint_.protocol());
}

Sender::~Sender(void)
{
}

void Sender::sendPosition(int id,const std::array<double,2>& position, const double & orientation)
{
	std::ostringstream os;
    os << id <<","<<position[0]<<","<<position[1]<<","<<orientation;
	std::string message_ = os.str();
	socket_./*async_*/send_to(boost::asio::buffer(message_), endpoint_/*, boost::bind(&Sender::handler_sender, this, boost::asio::placeholders::error)*/);
}

void Sender::handler_sender(const boost::system::error_code& error)
{}