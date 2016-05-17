#ifndef SOCKET_BOOST_H
#define SOCKET_BOOST_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "PacketParser.h"
#include "Data.h"


#define BUFLEN 2048

class Data;

using boost::asio::ip::udp;

class SocketBoost {

	private:
		char buf[BUFLEN];
		char bufNames[BUFLEN];

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
		void init(string ip, string port, int timeToWait);
		void init_name(string ip, string port, int timeToWait);
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
