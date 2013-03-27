#include "Agent.h"
#include "Object.h"

#include <vector>
#include <array>

#include "boost/thread.hpp"
#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"

using namespace boost;
using namespace std::tr1;

//CONSTRUCTOR AND DESTRUCTOR----------------------------------
Agent::Agent(int id, vector<double> initialPosition, double initialOrientation):
	Object(initialPosition, initialOrientation),
	trackGenerator(),
	localAddress("1.1.1.1"),
	neighbors(vector<Object>()),
	obstacles(vector<Object>()),
	communicationSystem(id, "239.255.0.1", 5090),
	stopListening(false),
	posX_(NULL),
	posY_(NULL),
	id_(NULL),	
	orientation_(NULL),
	io_service_receiver(),
	work_receiver(io_service_receiver),
	socket_receiver(io_service_receiver)//,
	//socket_udp_sender(io_service_receiver)
{
	
	// Create the socket so that multiple may be bound to the same address.
    boost::asio::ip::udp::endpoint listen_endpoint(boost::asio::ip::address::from_string("0.0.0.0"), 5090);
    socket_receiver.open(listen_endpoint.protocol());
    socket_receiver.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_receiver.bind(listen_endpoint);
    // Join the multicast group.
	socket_receiver.set_option(boost::asio::ip::multicast::join_group(boost::asio::ip::address::from_string("239.255.0.1").to_v4(),listen_endpoint.address().to_v4()));
}

Agent::~Agent(void)
{
	stopListening = true;
	io_service_receiver.stop();
	if (listeningThread.joinable()){
  		listeningThread.join();
	}
	free (posX_);
	free (posY_);
	free (orientation_);
	free (id_);
}

//GETS--------------------------------------------------------
vector<Object> Agent::getNeighbors()
{
	return neighbors;
}

void	Agent::getNeighbors(int* numberOfNeighbors, int** id, double** x, double** y){
	*numberOfNeighbors=(int)neighbors.size();

	posX_ = (double*) malloc(*numberOfNeighbors * sizeof(double));
	posY_ = (double*) malloc(*numberOfNeighbors * sizeof(double));
	//orientation_ = (double*) malloc(*numberOfNeighbors * sizeof(double));
	id_ = (int*) malloc(*numberOfNeighbors * sizeof(int));
	std::tr1::array<double,2> position;
	//double orientation;
	for (unsigned int i=0;i<neighbors.size();i++) {
		position = neighbors[i].getPosition();
		//orientation = neighbors[i].getOrientation();
		id_[i] = neighbors[i].getId();
		posX_[i] = position[0];
		posY_[i] = position[1];
		//orientation_[i] = orientation;
	}
	*id= id_;
	*x = posX_;
	*y = posY_;
}

vector<Object> Agent::getObstacles()
{
	return obstacles;
}

string Agent::getLocalAddress()
{
	return localAddress;
}

//SETS--------------------------------------------------------
void Agent::setNeighbors(vector<Object> neighborsArg)
{
	neighbors = neighborsArg;
}

void Agent::setObstacles(vector<Object> obstaclesArg)
{
	obstacles = obstaclesArg;
}

void Agent::setLocalAddres(string localAddressArg)
{
	localAddress = localAddressArg;
}


void Agent::ReorganizeNeighbors(int idArg, double xArg, double yArg, double orientationArg)
{	
	if(getId() != idArg && communicationSystem.Enabled())
	{		
		int index = testNeighbor(idArg);			
		if(index != -1) // neighbor already exist
		{				
			neighbors[index].setPosition(xArg,yArg);
			neighbors[index].setOrientation(orientationArg);
		}
		else //new neighbor
		{
			Object newcomer;
			newcomer.setId(idArg);
			newcomer.setPosition(xArg,yArg);
			newcomer.setOrientation(orientationArg);
			neighbors.push_back(newcomer);
		}
	}
}

int Agent::testNeighbor(int idArg)
{
	int ret = -1;
	for(unsigned int i=0;i < neighbors.size();++i)
	{
		if((neighbors[i]).getId() == idArg)
		{ret = i;}
	}
	return ret;
}

void Agent::SendPosition() {
	communicationSystem.sendPosition(getId(),getPosition(),getOrientation());
}


void Agent::LaunchComm()
{
	//boost::thread thr(boost::bind(&CommunicationSystem::run,&communicationSystem));
	listeningThread = thread(&Agent::ReceiveContinuously, this);
	socket_receiver.async_receive_from(asio::buffer(data_, strlen(data_)), receiver_endpoint,boost::bind(boost::mem_fn(&Agent::ReadIncomingData), 
								this, asio::placeholders::error,boost::asio::placeholders::bytes_transferred));

}

void Agent::ReadIncomingData(const system::error_code& error, size_t bytes_recvd){
	if (!error) {
		char comma;
		stringstream msg(data_);
		msg>>receivedId>>comma>>receivedPosition[0]>>comma>>receivedPosition[1]>>comma>>receivedOrientation;
		ReorganizeNeighbors(receivedId,receivedPosition[0],receivedPosition[1],receivedOrientation);
		socket_receiver.async_receive_from(asio::buffer(data_, strlen(data_)), receiver_endpoint,boost::bind(boost::mem_fn(&Agent::ReadIncomingData), 
								this, asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
	}
}

void Agent::ReceiveContinuously() {
	//while(!stopListening) {
	io_service_receiver.run();
	//	this_thread::sleep(boost::posix_time::milliseconds(10));
	//}
}


void Agent::LaunchUDPServer(int port){
	using namespace boost::asio::ip;
	using boost::shared_ptr;
	socket_udp_sender = shared_ptr<udp::socket> (new udp::socket(io_service_receiver, udp::endpoint(udp::v4(), port)));	
	udp::endpoint remote_endpoint_;
	std::array<char, 1> recv_buffer_;
	socket_udp_sender->async_receive_from(
		boost::asio::buffer(recv_buffer_), udp_destination_temp,
        boost::bind(&Agent::handle_receive, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
}

void Agent::handle_receive(const system::error_code& error, size_t /*bytes_transferred*/){
	using namespace boost::asio::ip;	  
	if (!error || error == asio::error::message_size)
    {
		udp_destination.first = true;
		udp_destination.second = udp_destination_temp;
	}
	std::array<char, 1> recv_buffer_;
	socket_udp_sender->async_receive_from(
		boost::asio::buffer(recv_buffer_), udp_destination_temp,
        boost::bind(&Agent::handle_receive, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
}


void Agent::SendPositionUDP(){
	if (udp_destination.first) {
		//udp_destination.first = false;
		auto pos = getPosition();
		stringstream message;
		message<<this->getId()<<','<<pos[0]<<','<<pos[1]<<','<<getOrientation();
		string mes(message.str());
		socket_udp_sender->send_to(boost::asio::buffer(mes), udp_destination.second);
	}
}