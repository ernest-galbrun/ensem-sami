#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "SocketBoost.h"

#define SERVICE_PORT "1510"
#define SERVER_IP "100.64.209.183"
#define BUFLEN 2048

using boost::asio::ip::udp;
using namespace std;

char initMessage[] = {0x00, 0x00, 0x84, 0x00, 0x43, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x54, 0x65, 0x73, 0x74, 0x00, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x5c, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x64, 0x00, 0x36, 0x00, 0x34, 0x00, 0x5c, 0x00, 0x63, 0x00, 0x6c, 0x00, 0x2e, 0x00, 0x65, 0x00, 0x78, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x0a, 0x00};
char regularMessage[] = {0x0C, 0x00}; // <- Requête position
// char initMessage[] = {0x0a, 0x00}; // <- Requête pour les points

char buf[BUFLEN];

SocketBoost::SocketBoost(int timeToWait) {
    // Create the packet parser instance
	// this->parser = new Packet_Parser();

    // Configure the boost library and socket
    this->s = new udp::socket(io_service, udp::endpoint(udp::v4(), 0));
    udp::resolver resolver(this->io_service);
    this->server_endpoint = *resolver.resolve(udp::resolver::query(udp::v4(), SERVER_IP, SERVICE_PORT));

    // Save the time between two requests
    this->timeToWait = timeToWait;
}

void SocketBoost::init() {
    try {
        this->s->send_to(boost::asio::buffer(initMessage, 127/*strlen(initMessage)*/), this->server_endpoint);
        size_t reply_length = this->s->receive_from(boost::asio::buffer(buf, BUFLEN), this->client_endpoint);
    }
    catch ( boost::system::system_error& e)
    {
       cerr << "Exception while connecting: " << e.what() << "\n";
    }

    this->t = new boost::thread(boost::bind(&SocketBoost::start, this));
}

void SocketBoost::start() {
    while(1) {
        try {
            this->s->send_to(boost::asio::buffer(regularMessage, strlen(regularMessage)), this->server_endpoint);
            size_t reply_length = this->s->receive_from(boost::asio::buffer(buf, BUFLEN), this->client_endpoint);

			// parser->parse(buf,BUFLEN);

        }
        catch ( boost::system::system_error& e)
        {
           cerr << "Exception while sending: " << e.what() << "\n";
        }

        boost::this_thread::sleep_for(boost::chrono::milliseconds(this->timeToWait*1000));
        // launch boost::thread_interrupted if the current thread of execution is interrupted
    }
}

void SocketBoost::stop() {
    this->t->interrupt();
}
