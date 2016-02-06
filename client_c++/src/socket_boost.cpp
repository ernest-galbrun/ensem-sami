#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#define SERVICE_PORT "1510"
#define SERVER_IP "100.64.209.183"
#define BUFLEN 2048

using boost::asio::ip::udp;
using namespace std;

char initMessage[] = {0x0C, 0x00};
char regularMessage[] = {0x0C, 0x00};
char buf[BUFLEN];

class SocketBoost {
    private:
        boost::asio::io_service io_service;
        udp::endpoint server_endpoint;
        udp::endpoint client_endpoint;
        udp::socket *s;

        boost::thread *t;

        void connect() {
            try {
                // this->s->send_to(boost::asio::buffer(initMessage, strlen(initMessage)), this->server_endpoint);
                // size_t reply_length = this->s->receive_from(boost::asio::buffer(buf, BUFLEN), this->client_endpoint);
            }
            catch ( boost::system::system_error& e)
            {
               cerr << "Exception while connecting: " << e.what() << "\n";
            }
        }

    public:
        SocketBoost(int timeToWait) {
            this->s = new udp::socket(io_service, udp::endpoint(udp::v4(), 0));

            udp::resolver resolver(this->io_service);
            this->server_endpoint = *resolver.resolve(udp::resolver::query(udp::v4(), SERVER_IP, SERVICE_PORT));

            this->connect();

            this->t = new boost::thread(boost::bind(&SocketBoost::getLastData, this, timeToWait));
        }

        void getLastData(int timeToWait) {
            while(1) {
                cout << "Send\n";
                try {
                this->s->send_to(boost::asio::buffer(regularMessage, strlen(regularMessage)), this->server_endpoint);
                this->s->async_receive_from(boost::asio::buffer(buf, BUFLEN),
                                            this->server_endpoint,
                                            boost::bind(&SocketBoost::updateData,
                                                        this,
                                                        boost::asio::placeholders::error,
                                                        boost::asio::placeholders::bytes_transferred)
                                            );
                }
                catch ( boost::system::system_error& e)
                {
                   cerr << "Exception while sending: " << e.what() << "\n";
                }

                boost::this_thread::sleep_for(boost::chrono::milliseconds(timeToWait*1000));
                // lunch boost::thread_interrupted if the current thread of execution is interrupted
            }
        }

        void updateData(const boost::system::error_code& errorCode, size_t nBytesTransferred) {
            if (errorCode != 0)
                cerr << "Error while receiving" << errorCode << "\n";
            else
                cout << "Receive \n";
        }

        void stop() {
            this->t->interrupt();
        }

};

int main(int argc, char* argv[]) {
    SocketBoost *t = new SocketBoost(1);

    // while(1){}

    return 0;
}
