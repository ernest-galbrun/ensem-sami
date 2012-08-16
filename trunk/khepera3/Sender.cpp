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
	endpoint_(boost::asio::ip::address::from_string("239.255.0.1")/*multicast_address*/, multicast_port), 
	endpoint_bis(multicast_address, multicast_port), 
	socket_(io_service_sender), 
	timer_(io_service_sender)
{    

	boost::asio::io_service io_service;

    asio::ip::tcp::resolver resolver(io_service);
    asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(),"");
    asio::ip::tcp::resolver::iterator it=resolver.resolve(query);

	stringstream sout;
	boost::asio::ip::address thisone;
    while(it!=asio::ip::tcp::resolver::iterator())
    {
        boost::asio::ip::address addr=(it++)->endpoint().address();
        if(addr.is_v6())
        {
            sout<<"ipv6 address: ";
        }
        else
            sout<<"ipv4 address: ";

        sout<<addr.to_string()<<std::endl;
		if (addr.to_string()=="10.10.10.105")
			thisone = addr;

    }
	string test(sout.str());
	
    boost::asio::ip::address_v4 local_interface=boost::asio::ip::address_v4::from_string("10.10.10.105");
	boost::asio::ip::multicast::outbound_interface option(thisone.to_v4());
	//const ip::address ifAddr( asio::ip::udp::endpoint( *interfaceIP ).address( )); 
	socket_.open(endpoint_.protocol());
	socket_.set_option(option);
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