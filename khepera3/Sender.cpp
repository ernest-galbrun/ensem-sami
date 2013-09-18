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

Sender::Sender(int id): 
	io_service_sender(),
	//endpoint_(Sender::GenerateMulticastAddress(id), 30001), 
	socket_(io_service_sender/*, endpoint_.protocol()*/)
{    
	//socket_.open(endpoint_.protocol());
	system::error_code error;
	socket_.open(asio::ip::udp::v4(), error);
	socket_.set_option(asio::ip::udp::socket::reuse_address(true));
    socket_.set_option(asio::socket_base::broadcast(true));
    endpoint_ = asio::ip::udp::endpoint(asio::ip::address::from_string("192.168.1.255"), 30159);            
	//socket.send_to(data, senderEndpoint);
    //socket.close(error);
}

Sender::~Sender(void)
{
	io_service_sender.stop();
	socket_.close();
	//~io_service_sender();
}

boost::asio::ip::address Sender::GenerateMulticastAddress(int id){
	stringstream ss;
	ss<<"239.255.0."<<id;
	return asio::ip::address::from_string(ss.str());
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