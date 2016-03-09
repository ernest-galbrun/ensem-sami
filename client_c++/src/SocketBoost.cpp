#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "SocketBoost.h"

#define BUFLEN 2048

using boost::asio::ip::udp;
using namespace std;

char initMessage[] = {0x00, 0x00, 0x84, 0x00, 0x43, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x54, 0x65, 0x73, 0x74, 0x00, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x5c, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x64, 0x00, 0x36, 0x00, 0x34, 0x00, 0x5c, 0x00, 0x63, 0x00, 0x6c, 0x00, 0x2e, 0x00, 0x65, 0x00, 0x78, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x0a, 0x00};
char regularMessage[] = {0x0C, 0x00}; // <- Requête position
char PointsNameMessage[] = {0x0a, 0x00}; // <- Requête pour les points

char buf[BUFLEN];

SocketBoost::SocketBoost() {
    this->s = new udp::socket(io_service, udp::endpoint(udp::v4(), 0));
    udp::resolver resolver(this->io_service);
    this->server_endpoint = *resolver.resolve(udp::resolver::query(udp::v4(), this->ip, this->port));
}

void SocketBoost::init() {    
	this->sendReceive(initMessage, 127, buf, BUFLEN);
    this->t = new boost::thread(boost::bind(&SocketBoost::start, this));
}

void SocketBoost::init(string ip, string port) {
	this->setIp(ip);
	this->setPort(port);
	this->init();
}

void SocketBoost::start() {

    while(1) {
		this->sendReceive(regularMessage, strlen(regularMessage), buf, BUFLEN);
		this->parser->parse(buf, BUFLEN);

        boost::this_thread::sleep_for(boost::chrono::milliseconds(this->timeToWait*1000));
        // launch boost::thread_interrupted if the current thread of execution is interrupted
    }
}

void SocketBoost::stop() {
    this->t->interrupt();
}

void SocketBoost::getPointsName() {
	this->sendReceive(PointsNameMessage, strlen(PointsNameMessage), buf, BUFLEN);
	this->parser->parse(buf, BUFLEN);
}

string SocketBoost::getIp() {
	return this->ip;
}

void SocketBoost::setIp(string ip) {
	this->ip = ip;
}

string SocketBoost::getPort() {
	return this->port;
}

void SocketBoost::setPort(string port) {
	this->port = port;
}

int SocketBoost::getTimeToWait() {
	return this->timeToWait;
}

void SocketBoost::setTimeToWait(int timeToWait) {
	this->timeToWait = timeToWait;
}

size_t SocketBoost::sendReceive(char* message, int size, char* buffer, int bufferLength) {
	try {
        this->s->send_to(boost::asio::buffer(message, size), this->server_endpoint);
        return this->s->receive_from(boost::asio::buffer(buffer, bufferLength), this->client_endpoint);
    }
    catch ( boost::system::system_error& e) {
       cerr << "Exception while connecting: " << e.what() << "\n";
    }
	return 0;
}
