#include <string>

#include "Receiver.h"
#include "CommunicationSystem.h"

Receiver::Receiver(boost::asio::io_service& io_service, const boost::asio::ip::address& listen_address, const boost::asio::ip::address& multicast_address,int multicast_port,CommunicationSystem* commArg) : socket_(io_service)
{
	comm = commArg;
	
	// Create the socket so that multiple may be bound to the same address.
    boost::asio::ip::udp::endpoint listen_endpoint(listen_address, multicast_port);
    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);

    // Join the multicast group.
    socket_.set_option(boost::asio::ip::multicast::join_group(multicast_address));

}

Receiver::~Receiver(void)
{
}

void Receiver::run()
{
	socket_.async_receive_from(boost::asio::buffer(data_, max_length), sender_endpoint_,boost::bind(&Receiver::handler_receiver, this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
}

void Receiver::handler_receiver(const boost::system::error_code& error, size_t bytes_recvd)
{
	int id;
	double x,y;
	if (!error)
    {
		std::string msg(data_);
		std::string aux;
		
		aux = msg.substr(0,msg.find(","));
		msg = msg.substr(msg.find(",")+1);
		id = atoi(aux.c_str());
		
		aux = msg.substr(0,msg.find(","));
		msg = msg.substr(msg.find(",")+1);
		x = atof(aux.c_str());
		y = atof(msg.c_str());

		comm->reorganizeNeighbors(id,x,y);
		
		
		socket_.async_receive_from(boost::asio::buffer(data_, max_length), sender_endpoint_, boost::bind(&Receiver::handler_receiver, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
}
