#include "SocketBoost.h"

#define SERVICE_IP "100.64.209.183"
#define SERVICE_PORT "1510"

using boost::asio::ip::udp;
using namespace std;

SocketBoost::SocketBoost(Data& data):parser(data),s(io_service, udp::endpoint(udp::v4(), 0)),resolver(this->io_service){}

void SocketBoost::init() {
    t = boost::thread(boost::bind(&SocketBoost::start, this));
}

void SocketBoost::init(string ip, string port, int timeToWait) {
	setIp(ip);
  setPort(port);
  setTimeToWait(timeToWait);
	init();
}

void SocketBoost::init_name(string ip, string port, int timeToWait) {
	setIp(ip);
    setPort(port);
    setTimeToWait(timeToWait);
	getPointsName();
}

void SocketBoost::start() {
    char* msg = (char*)malloc(512*sizeof(char));
    int sizeMsg = cortexProtocol.generatePacket(NULL, 0, REGULAR_MESSAGE, msg);

    while(1) {
       sendReceive(msg, sizeMsg, buf, BUFLEN);

       parser.parse(buf, BUFLEN);

        boost::this_thread::sleep_for(boost::chrono::milliseconds(timeToWait));
        // launch boost::thread_interrupted if the current thread of execution is interrupted
    }

    free(msg);
}

void SocketBoost::stop() {
    t.interrupt();
}

void SocketBoost::getPointsName() {
  char* msg = (char*)malloc(512*sizeof(char));
  int sizeMsg = cortexProtocol.generatePacket(NULL, 0, POINTS_NAME_MESSAGE, msg);

	sendReceive(msg, sizeMsg, bufNames, BUFLEN);
	parser.parse(bufNames, BUFLEN);

  free(msg);
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
