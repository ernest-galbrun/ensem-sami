#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "SocketBoost.h"
#include "Data.h"

#define SERVICE_IP "100.64.209.183"
#define SERVICE_PORT "1510"

using boost::asio::ip::udp;
using namespace std;

char initMessage[] = {0x00, 0x00, 0x84, 0x00, 0x43, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x54, 0x65, 0x73, 0x74, 0x00, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x5c, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x64, 0x00, 0x36, 0x00, 0x34, 0x00, 0x5c, 0x00, 0x63, 0x00, 0x6c, 0x00, 0x2e, 0x00, 0x65, 0x00, 0x78, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x0a, 0x00};
char regularMessage[] = {0x0C, 0x00}; // <- Requête position
char PointsNameMessage[] = {0x0a, 0x00}; // <- Requête pour les points

SocketBoost::SocketBoost(Data& data):parser(data),s(io_service, udp::endpoint(udp::v4(), 0)),resolver(this->io_service){
}

void SocketBoost::init() {
    sendReceive(initMessage, 127, buf, BUFLEN);
    t = boost::thread(boost::bind(&SocketBoost::start, this));
}

void SocketBoost::init(string ip, string port, int timeToWait) {
	setIp(ip);
    setPort(port);
    setTimeToWait(timeToWait);
	init();
}

void SocketBoost::start() {

    while(1) {
       sendReceive(regularMessage, strlen(regularMessage), buf, BUFLEN);

       parser.parse(buf, BUFLEN);

        boost::this_thread::sleep_for(boost::chrono::milliseconds(timeToWait));
        // launch boost::thread_interrupted if the current thread of execution is interrupted
    }
}

void SocketBoost::stop() {
    t.interrupt();
}

void SocketBoost::getPointsName() {
	sendReceive(PointsNameMessage, strlen(PointsNameMessage), bufNames, BUFLEN);
	parser.parse(bufNames, BUFLEN);
}

string SocketBoost::getIp() {
	return ip;
}

void SocketBoost::setIp(string ip) {
	this->ip = ip;
    updateServerEndpoint();
}

string SocketBoost::getPort() {
	return port;
}

void SocketBoost::setPort(string port) {
	this->port = port;
    updateServerEndpoint();
}

int SocketBoost::getTimeToWait() {
	return timeToWait;
}

void SocketBoost::setTimeToWait(int timeToWait) {
	this->timeToWait = timeToWait;
}

size_t SocketBoost::sendReceive(char* message, int size, char* buffer, int bufferLength) {
	try {
        s.send_to(boost::asio::buffer(message, size), server_endpoint);
        return s.receive_from(boost::asio::buffer(buffer, bufferLength), client_endpoint);
    }
    catch ( boost::system::system_error& e) {
       cerr << "Exception while connecting: " << e.what() << "\n";
    }
	return 0;
}

void SocketBoost::updateServerEndpoint() {
  server_endpoint = *(resolver.resolve(udp::resolver::query(ip, port)));
}
