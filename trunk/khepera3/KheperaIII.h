#pragma once

//#define MEX_COMPILER
//#define WIN32_LEAN_AND_MEAN 
//#include "Serial.h"
#include "Agent.h"

#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"

class LocalizationSystem;
class CommunicationSystem;
using namespace std;


class KheperaIII : public Agent
{
private:
	int nIrSensors;
	double axis;
	int *irValues;
	//CSerial *serial;
	//string serialPort;
	//int testSerial;
	
	boost::asio::io_service      io_service_;
	boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;

	string speedMsg(double,double);
	string encodersMsg(int,int);
	string sendMsg(string);
	CommunicationSystem* communicationSystem;	

public:
	KheperaIII(int id);
	~KheperaIII(void);

	LocalizationSystem* localizationSystem;
	void initComm(std::string,std::string,int);

	void timeStep();
	void setVelocity(double,double);
	int* getIrOutput();
	
	int* getEncodersValue();
	void setEncodersValue(int,int);
	void closeSession();

	int getTestSerial();
};


