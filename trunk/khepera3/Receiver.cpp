#include <string>
#include <sstream>

#include "Receiver.h"
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/thread.hpp"

using namespace boost;
using namespace std;

Receiver::Receiver(const boost::asio::ip::address& listen_address, const boost::asio::ip::address& multicast_address,int multicast_port) : 
	io_service_receiver(),
	socket_(io_service_receiver)
{	
	// Create the socket so that multiple may be bound to the same address.
    boost::asio::ip::udp::endpoint listen_endpoint(listen_address, multicast_port);
    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);

    // Join the multicast group.
    socket_.set_option(boost::asio::ip::multicast::join_group(multicast_address));
	data_.resize(100);

}

Receiver::~Receiver(void)
{
}

//void Receiver::run()
//{
//	io_service_receiver.run();
//	socket_.async_receive_from(boost::asio::buffer(data_, max_length), sender_endpoint_,boost::bind(&Receiver::handler_receiver, this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
//	while(true)
//		io_service_receiver.run();
//}

void Receiver::handler_receiver(const boost::system::error_code& error, std::size_t bytes_recvd)
{
	if (!error)
    {	
		char comma;
		stringstream msg(data_);
		msg>>receivedId>>comma>>receivedPosition[0]>>comma>>receivedPosition[1];
	}
}


bool Receiver::ReceivePosition(int& id, boost::array<double,2>& position) {
	
	socket_.async_receive_from(asio::buffer(data_), sender_endpoint_,boost::bind(boost::mem_fn(&Receiver::handler_receiver), this, boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));	
    asio::deadline_timer timer(io_service_timer); 
    timer.expires_from_now(posix_time::milliseconds(100)); 
	timer.async_wait(boost::bind(&Receiver::Handler_AsyncTimer,this,asio::placeholders::error)); 
	bool newDataArrived;
	size_t n = io_service_receiver.poll_one();
    while (n==0)
    { 
		this_thread::sleep(boost::posix_time::milliseconds(1));
		io_service_timer.poll();
		if (io_error_) 
		timer.cancel(); 
		else if (timer_error_) 
		socket_.cancel(); 
		else
		n=io_service_receiver.poll_one();
    }
	newDataArrived = n==0?false:true;
	if (newDataArrived) {
		id = receivedId;
		position = receivedPosition;
	}
	return newDataArrived;
}

void Receiver::Handler_AsyncTimer( const boost::system::error_code& error){
	timer_error_ = error;
} 