#pragma once

//#define MEX_COMPILER
//#define WIN32_LEAN_AND_MEAN 
//#include "Serial.h"
#include "Agent.h"

#include "boost/thread.hpp"
#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

class LocalizationSystem;
class CommunicationSystem;
using namespace std;


class KheperaIII : public Agent
{
private:
	int nIrSensors;
	double axis;
	int *irValues;
	int encoderValues[2];

	int tick;
	boost::shared_ptr<boost::asio::deadline_timer> timer;
	//CSerial *serial;
	//string serialPort;
	//int testSerial;
	
	boost::asio::io_service      io_service_;
	boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
	boost::mutex tcpLock;
	boost::shared_ptr<boost::asio::streambuf> tcp_buf;
	boost::thread	continuousThread;
	void ContinuousChecks();

	void	ReadLastLineHandler(const boost::system::error_code& e, std::size_t size);
	bool	stopContinuousAcquisition;
	bool	firstRead;
	string speedMsg(int,int);
	string encodersMsg(int,int);
	int sendMsg(string msg, int n, vector<string>* answer);
	boost::shared_ptr<CommunicationSystem> communicationSystem;	
	void	RunIOService();

public:
	KheperaIII(int id);
	~KheperaIII(void);

	boost::shared_ptr<LocalizationSystem> localizationSystem;
	void initComm(std::string,std::string,int);

	void timeStep();
	void LaunchContinuousThread();
	void setVelocity(double,double);
	int* getIrOutput();
	
	void getEncodersValue(int* left, int* right);
	void setEncodersValue(int,int);
	void closeSession();
	int GetMode(int* left, int* right);
	int GetPID(int (*PIDLeft)[3], int (*PIDRight)[3]);
	int GetSpeed(int* left, int* right);
	int SetMode(int left, int right);
	int SetPID(int pLeft, int iLeft, int dLeft, int pRight, int iRight, int dRight);
	int SetTargetPoint(int targetLeft, int targetRight);
	int ResetPosition(int posLeft, int posright);
	int StartMotors();
	int StopMotors();
	int	RecordPulse(int modeLeft, int modeRight, int nStep, double* targetLeft, double* targetRight, int* NAcquisition,
										  double** timeStamp, int** valuesLeft, int** valuesRight);
	int StopInternalTracking();
	int StartInternalTracking();

	int getTestSerial();
};


