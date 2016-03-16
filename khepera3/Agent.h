#pragma once

#include <string>
#include <vector>
#include "boost/thread.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/asio.hpp"
#include "Object.h"
#include "TrackGenerator.h"
#include "CommunicationSystem.h"
#include <utility>

class Agent : public Object, boost::noncopyable
{
private:
	std::vector<Object> neighbors;
	std::vector<Object> obstacles;
	std::string localAddress;
	// posX_, posY_ and id_ are c array holding values for every neighbors
	double * posX_;
	double * posY_;
	double * orientation_;
	int* id_;
	CommunicationSystem communicationSystem;	

	int testNeighbor(int idArg);
	void ReceiveContinuously();
	void UDPServerThread();
	void handle_receive(const boost::system::error_code& error, std::size_t);
	bool stopListening;
	std::pair<bool,boost::asio::ip::udp::endpoint> udp_destination; //bool is true if a client has initiated connection
	boost::asio::ip::udp::endpoint udp_destination_temp;
	boost::thread listeningThread;
	boost::thread udp_server_thread;


	//from receiver :
	boost::asio::io_service io_service_receiver;
	boost::asio::io_service io_service_udp_server;
	//boost::asio::io_service::work  work_receiver;
	boost::asio::ip::udp::socket socket_receiver;
	boost::shared_ptr<boost::asio::ip::udp::socket> socket_udp_sender;
	boost::asio::ip::udp::endpoint sender_endpoint;
	char data_[1024];
	boost::system::error_code io_error_;

	int receivedId;
	std::array<double,2> receivedPosition;
	double receivedOrientation;
	//async handler for incoming data
	void ReadIncomingData(const boost::system::error_code& error, std::size_t bytes_recvd);
protected:
	void LaunchComm();
	void LaunchUDPServer(int port);
	void SendPositionUDP();
public:
	Agent(int id, vector<double> initialPosition=vector<double>(2,0), double initialOrientation=0);
	~Agent(void);

	TrackGenerator trackGenerator;

	void ReorganizeNeighbors(int idArg, double xArg, double yArg,double posArg);
	std::vector<Object> getNeighbors();
	// c friendly getNeighbors function
	void	getNeighbors(int* numberOfNeighbors, int** id, double** x, double** y);
	std::vector<Object> getObstacles();
	std::string getLocalAddress();
	void SendPosition();

	void setNeighbors(vector<Object>);
	void setObstacles(vector<Object>);
	void setLocalAddres(std::string);
};
