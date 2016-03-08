#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include "PacketParser.h"

#ifndef SOCKET_BOOST_H
#define SOCKET_BOOST_H

using boost::asio::ip::udp;

class SocketBoost {

	private:
        boost::asio::io_service io_service;
        udp::endpoint server_endpoint;
        udp::endpoint client_endpoint;
        udp::socket *s;

        boost::thread *t;

        Packet_Parser * parser;

        int timeToWait;
	public:
        SocketBoost(int timeToWait);
        void init();
        void start();
        void stop();

};

#endif
