#pragma once

//#define MEX_COMPILER
//#define WIN32_LEAN_AND_MEAN 
//#include "Serial.h"
#include "Agent.h"

#include "boost/thread.hpp"
#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "CommunicationSystem.h"
#include "LocalizationSystem.h"

using namespace std;


class KheperaIII : public Agent
{
private:
	boost::posix_time::ptime lastStepTime;
	bool isVirtual_; // set to true if we arre dealing with a virtual robot
	double linearSpeed_, angularSpeed_;
	int nIrSensors;
	double axis;
	std::vector<int> irValues;
	boost::array<int,2> encoderValues;
	int previousL;
	int previousR;
	int updatePositionMode; //0 = offline 1 = using cortex 2 = hybrid

	int tick;
	boost::shared_ptr<boost::asio::deadline_timer> timer;
	
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
	void	RunIOService();
	void UpdatePositionOffline();
	virtual bool UpdatePosition();

public:
	KheperaIII(int id, bool isVirtual=false);
	~KheperaIII(void);

	void CloseConnection();

	void timeStep();
	void LaunchContinuousThread();
	void setVelocity(double,double);
	const vector<int>& getIrOutput();
	
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
	int	RecordPulse(int modeLeft, int modeRight, int nStep, int* targetLeft, int* targetRight, int* NAcquisition,
										  int** timeStamp, int** valuesLeft, int** valuesRight);
	int StopInternalTracking();
	int StartInternalTracking();

	int getTestSerial();
	void SetUpdatePositionMode(int mode);
};


