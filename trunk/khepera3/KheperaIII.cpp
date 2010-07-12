//#include <winsock2.h>
//#include <windows.h>
//#include "Serial.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <tchar.h>
#include <sstream>

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "LocalizationSystem.h"
#include "KheperaIII.h"
#include "CommunicationSystem.h"

using namespace std;
using namespace boost;

//int KheperaIII::getTestSerial()
//{return testSerial;}

//CONSTRUCTOR AND DESTRUCTOR----------------------------------
KheperaIII::KheperaIII(int id)
{
	setId(id);
	tick = 0;
	timer = boost::shared_ptr<asio::deadline_timer>(new asio::deadline_timer(io_service_,posix_time::milliseconds(0)));
	tcp_buf = boost::shared_ptr<asio::streambuf>(new asio::streambuf(100));

	nIrSensors = NB_SENSORS;
	axis = AXIS;
	irValues = (int*)malloc(nIrSensors*sizeof(int));
	//serial = new CSerial();
	long aux1,aux2;
	
	localizationSystem = boost::shared_ptr<LocalizationSystem> (new LocalizationSystem(this));
	communicationSystem = boost::shared_ptr<CommunicationSystem> (new CommunicationSystem(this));

	stringstream s;
	s<<"10.10.10."<<id;

	asio::ip::tcp::resolver resolver(io_service_);
	asio::ip::tcp::resolver::query query(s.str(),"14");
	asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
	asio::ip::tcp::resolver::iterator end;
	socket_ = boost::shared_ptr<boost::asio::ip::tcp::socket>(new asio::ip::tcp::socket(io_service_));
	cout << "Establishing connection with the Robot..." << endl;
	boost::system::error_code& ec = boost::system::error_code();
	while (iter != end) {
		socket_->connect(*iter,ec);
		if (ec == false)
			break;
		iter++;
	}

	if (ec) {
		cout<< "ERROR: connection to the robo failed. Error code: "<<ec<<".\n";
	}
	vector<string> test;
	//sendMsg("$GetPosition\r\n",2,&test);
}

KheperaIII::~KheperaIII()
{
}

void KheperaIII::ContinuousChecks(){
	while (true)
		timeStep();
}
//FUNCTIONAL METHODS------------------------------------------
//vSpeed: cm/s		wSpeed: rad/s positive->clockwise
void KheperaIII::setVelocity(double vSpeed, double wSpeed)
{
	double rSpeed;
	double lSpeed;
	
	lSpeed = K_SPEED*(vSpeed - wSpeed*axis/2);
	rSpeed = K_SPEED*(vSpeed + wSpeed*axis/2);
	string msg = this->speedMsg(lSpeed,rSpeed);
	vector<string> ans;
	this->sendMsg(msg,1,&ans);
}

void KheperaIII::timeStep()
{	
	timer->expires_from_now(posix_time::milliseconds(TIME_STEP));
	timer->wait();
	this->trackGenerator->nextStep();
	this->localizationSystem->atualizePosition();
	this->communicationSystem->sendPosition();	
}

int* KheperaIII::getIrOutput()
{
	/*string commandMsg = "N\n";
	string data;
	string aux;
	string::size_type index;
	int i;

	data = this->sendMsg(commandMsg);

	for(i=0;i<nIrSensors;i++)
	{
		index = data.find(",",0);
		data = data.substr(index+1);
		index = data.find(",",0);
		aux = data.substr(0,index);
		
		irValues[i] = atoi(aux.c_str());
	}*/
	int		irValues[2];
	irValues[0] = 0;
	irValues[1] = 0;
	return irValues;
}



void KheperaIII::setEncodersValue(int lValue,int rValue)
{
	string msg = this->encodersMsg(lValue,rValue);
	vector<string> ans;
	this->sendMsg(msg,1,&ans);
}
int* KheperaIII::getEncodersValue()
{
	int* ret = (int*)malloc(2*sizeof(int));
	vector<string> ans;
	stringstream ss;
	char comma;
	sendMsg("$GetPosition\r\n",2,&ans);
	ss.str(ans[0]);
	ss>>ret[0]>>comma>>ret[1];
	return ret;
}
//AUXILIAR METHODS--------------------------------------------
string KheperaIII::speedMsg(int lSpeed, int rSpeed)
{
	stringstream msg;
	msg << "$SetSpeed,"<<lSpeed<<','<<rSpeed<<"\r\n";
	return msg.str();
}

string KheperaIII::encodersMsg(int lValue, int rValue)
{
	stringstream msg;
	msg << "$ResetPosition,"<<lValue<<','<<rValue<<"\r\n";
	return msg.str();
}

// send the msg and wait for the response, which must contain n lines, the last one 
// repeating the message command
int KheperaIII::sendMsg(string msg, int n, vector<string>* answer)
{
	char buf[1000];
	tcpLock.lock();
	*answer = vector<string>();
	asio::write(*socket_,asio::buffer(msg));
	//tcp_buf->prepare(msg.size());
	string ans;
	char cr,lf;
	int	bytesRead;
	system::error_code& ec = system::error_code();
	istream is(&*tcp_buf);
	for (int i=0;i<n;i++){
		bytesRead = asio::read_until(*socket_,*tcp_buf,"\r\n",ec);
		//tcp_buf->commit(bytesRead);
		is.getline(buf,1000,'\r');
		is.ignore(1);
		ans = string(buf);
		//tcp_buf->consume(bytesRead);
		//tcp_buf->consume(2);
		answer->push_back(ans);
	}
	string cmdSent = msg.substr(1,msg.find(',')-1);
	//tcp_buf->consume(tcp_buf->size());
	tcpLock.unlock();
	if (cmdSent.compare(ans))
		return 0;
	else
		return -1;
}

void KheperaIII::initComm(std::string adLoc, std::string adMult, int porMult)
{
	boost::thread thr(boost::bind(&CommunicationSystem::init,communicationSystem,adLoc, adMult,porMult));
}

void KheperaIII::closeSession()
{
	this->setVelocity(0,0);
	socket_->close();
}