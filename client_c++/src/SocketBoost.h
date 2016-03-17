#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include "PacketParser.h"
#include "Data.h"

#ifndef SOCKET_BOOST_H
#define SOCKET_BOOST_H

using boost::asio::ip::udp;

class SocketBoost {

	private:
    boost::asio::io_service io_service;
    udp::endpoint server_endpoint;
    udp::endpoint client_endpoint;
    udp::socket s;

	udp::resolver resolver;

    boost::thread t;

    Packet_Parser parser;

    int timeToWait;
		string ip;
		string port;

		size_t sendReceive(char* message, int size, char* buffer, int bufferLength);
		void init();
		void updateServerEndpoint();

	public:
    	SocketBoost(Data& data);
		void init(string ip, string port);
    	void start();
    	void stop();
		void getPointsName();

		void setIp(string ip);
		void setPort(string port);
		void setTimeToWait(int timeToWait);

		string getIp();
		string getPort();
		int getTimeToWait();
};

#endif
