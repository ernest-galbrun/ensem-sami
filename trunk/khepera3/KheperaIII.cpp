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
KheperaIII::KheperaIII(int id):
	Agent(id),
	axis(AXIS),
	nIrSensors(NB_SENSORS),
	irValues(vector<int>(nIrSensors)),
	firstRead(true),
	stopContinuousAcquisition(false),
	previousL(0),
	previousR(0)
{
	setId(id);
	tick = 0;
	timer = boost::shared_ptr<asio::deadline_timer>(new asio::deadline_timer(io_service_,posix_time::milliseconds(0)));
	tcp_buf = boost::shared_ptr<asio::streambuf>(new asio::streambuf(100));	
	
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
		cout<< "ERROR: connection to the robot failed. Error code: "<<ec<<".\n";
	}
	else {
		vector<string> ans;
		sendMsg("$SetAcquisitionFrequency1x,1,1\r\n",1,&ans);
		getEncodersValue(&previousL, &previousR);
		LaunchComm();
	}
}



KheperaIII::~KheperaIII()
{
	stopContinuousAcquisition = true;
	continuousThread.join();
}

void	KheperaIII::CloseConnection()// use instead of destructor because of heap corruption in matlab
{
	stopContinuousAcquisition = true;
	continuousThread.join();
}

void KheperaIII::LaunchContinuousThread(){	
	continuousThread=  thread(&KheperaIII::ContinuousChecks, this);
}

void KheperaIII::ContinuousChecks(){
	//io_service_.run();
	while (!stopContinuousAcquisition){
		timer->expires_from_now(posix_time::milliseconds(TIME_STEP));
		timer->wait();
		timeStep();
	}
}
//FUNCTIONAL METHODS------------------------------------------
//vSpeed: cm/s		wSpeed: rad/s positive->clockwise
void KheperaIII::setVelocity(double vSpeed, double wSpeed)
{
	double rSpeed;
	double lSpeed;
	
	lSpeed = K_SPEED*(vSpeed - wSpeed*axis/2);
	rSpeed = K_SPEED*(vSpeed + wSpeed*axis/2);
	string msg = this->speedMsg((int)lSpeed,(int)rSpeed);
	vector<string> ans;
	this->sendMsg(msg,1,&ans);
}

void KheperaIII::timeStep()
{	
	trackGenerator.nextStep();
	UpdatePosition();
	SendPosition();	
}

bool KheperaIII::UpdatePosition() {
	if (updatePositionMode==0) {
		UpdatePositionOffline();
	}
	else if (updatePositionMode==1) {
		if (!this->Object::UpdatePosition()) {
			UpdatePositionOffline();
		}
	}
	return true;
}


void KheperaIII::UpdatePositionOffline() {
	double dl, dr, dc, thetaAux;
	int encoderValueLeft,encoderValueRight;
	boost::array<double,2> position = getPosition();
	double orientation = getOrientation();
	getEncodersValue(&encoderValueLeft,&encoderValueRight);
	dl = (encoderValueLeft-previousL)*K_ENCODER;
	dr = (encoderValueRight-previousR)*K_ENCODER;
	dc = (dl+dr)/2;

	thetaAux = orientation;
	orientation += (dr-dl)/AXIS;
			
	(position)[0] += dc*cos( (orientation + thetaAux)/2);
	(position)[1] =+ dc*sin( (orientation + thetaAux)/2);

	setPosition(position[0],position[1]);
	setOrientation(orientation);

	previousL = encoderValueLeft;
	previousR = encoderValueRight;
}

const vector<int>& KheperaIII::getIrOutput()
{
	/*string commandMsg = "N\n";
	string data;
	string aux;
	string::size_type index;
	int i;
	data = this->sendMsg(commandMsg);*/

	for(unsigned int i=0;i<irValues.size();++i)
	{
		/*index = data.find(",",0);
		data = data.substr(index+1);
		index = data.find(",",0);
		aux = data.substr(0,index);*/		
		irValues[i] = 0;
	}
	return irValues;
}

void KheperaIII::setEncodersValue(int lValue,int rValue)
{
	string msg = this->encodersMsg(lValue,rValue);
	vector<string> ans;
	this->sendMsg(msg,1,&ans);
}
void KheperaIII::getEncodersValue(int *left, int* right)
{
	int* ret = (int*)malloc(2*sizeof(int));
	vector<string> ans;
	stringstream ss;
	char comma;
	if(!sendMsg("$GetPosition\r\n",2,&ans)) {
		ss.str(ans[0]);
		ss>>encoderValues[0]>>comma>>encoderValues[1];
	}
	*left = encoderValues[0];
	*right = encoderValues[1];
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
// send the message and wait for the response, which must contain n lines, the last one 
// repeating the message command
int KheperaIII::sendMsg(string msg, int n, vector<string>* answer)
{
	tcpLock.lock();
	
	char buf[1000];
	*answer = vector<string>();
	asio::write(*socket_,asio::buffer(msg));
	string ans;
	size_t	bytesRead;
	system::error_code& ec = system::error_code();
	istream is(&*tcp_buf);
	if (!firstRead) {
		asio::read_until(*socket_,*tcp_buf,"\r\n",ec);
		is.getline(buf,1000,'\r');
		is.ignore(1);
	}
	else
		firstRead = false;
	for (int i=0;i<n-1;i++){
		bytesRead = asio::read_until(*socket_,*tcp_buf,"\r\n",ec);
		is.getline(buf,1000,'\r');
		is.ignore(1);
		ans = string(buf);
		answer->push_back(ans);
	}
	tcpLock.unlock();
	return 0;	
}

void	KheperaIII::RunIOService(){
	tcpLock.lock();
	io_service_.run();
	tcpLock.unlock();
}

void	KheperaIII::ReadLastLineHandler(const boost::system::error_code& e, std::size_t size){
	//communicationStackCount--;
}

void KheperaIII::closeSession()
{
	this->setVelocity(0,0);
	socket_->close();
}

int KheperaIII::GetMode(int* left, int* right){
	stringstream message, ssAnswer;
	vector<string> answer;
	char comma;
	message << "$GetMode\r\n";
	sendMsg(message.str(), 2, &answer);
	ssAnswer.str(answer[0]);
	ssAnswer >> *left >> comma >> *right;
	return 0;
}

int KheperaIII::GetPID(int (*PIDLeft)[3], int (*PIDRight)[3]){
	stringstream message, ssAnswer, ssAnswerRight;
	vector<string> answer;
	char comma;
	int modeLeft, modeRight;
	GetMode(&modeLeft, &modeRight);
	if (modeLeft!=0) {
		modeLeft--;
		modeLeft/=2;
		message << "$GetPID,"<<modeLeft<<",0\r\n";
		sendMsg(message.str(),2,&answer);
		ssAnswer.str(answer[0]);
		ssAnswer >> (*PIDLeft)[0] >> comma >> (*PIDLeft)[1] >> comma >> (*PIDLeft)[2];
	}
	else {
		for (int i=0;i<3;i++)
			(*PIDLeft)[i]=0;
	}
	if (modeRight != 0) {
		modeRight--;
		modeRight/=2;
		message.str("");
		message << "$GetPID,"<<modeRight<<",1\r\n";
		sendMsg(message.str(),2,&answer);
		ssAnswer.clear();
		ssAnswerRight.str(answer[0]);
		//ssAnswer.seekg (0, ios::beg);
		ssAnswerRight >> (*PIDRight)[0] >> comma >> (*PIDRight)[1] >> comma >> (*PIDRight)[2];
	}
	else {
		for (int i=0;i<3;i++)
			(*PIDRight)[i]=0;
	}
	return 0;
}

int KheperaIII::GetSpeed(int* left, int* right){	
	stringstream message, ssAnswer;
	vector<string> answer;
	char comma;
	message << "$GetSpeed\r\n";
	sendMsg(message.str(),2, &answer);
	ssAnswer.str(answer[0]);
	ssAnswer >> *left >> comma >> *right;
	return 0;
}

int KheperaIII::SetMode(int left, int right){
	stringstream message, ssAnswer;
	vector<string> answer;
	message << "$SetMode,"<<left<<','<<right<<"\r\n";
	sendMsg(message.str(),1, &answer);
	return 0;
}

int KheperaIII::SetPID(int pLeft, int iLeft, int dLeft, int pRight, int iRight, int dRight){	
	stringstream message, ssAnswer;
	vector<string> answer;
	int modeLeft, modeRight;
	GetMode(&modeLeft, &modeRight);
	if (modeLeft !=0) {
		modeLeft--;
		modeLeft/=2;
		message << "$SetPID,"<<modeLeft<<",0,"<<pLeft<<','<<iLeft<<','<<dLeft<<"\r\n";
		sendMsg(message.str(),1, &answer);
		message.str("");
	}
	if (modeRight != 0) {
		modeRight--;
		modeRight/=2;
		message << "$SetPID,"<<modeRight<<",1,"<<pRight<<','<<iRight<<','<<dRight<<"\r\n";
		sendMsg(message.str(),1, &answer);
	}
	return 0;
}

int KheperaIII::SetTargetPoint(int targetLeft, int targetRight){
	stringstream message, ssAnswer;
	vector<string> answer;
	message << "$SetPoint,"<<targetLeft<<','<<targetRight<<"\r\n";
	sendMsg(message.str(),1, &answer);
	return 0;
}

int KheperaIII::ResetPosition(int posLeft, int posRight){
	stringstream message, ssAnswer;
	vector<string> answer;
	message << "$ResetPosition,"<<posLeft<<','<<posRight<<"\r\n";
	sendMsg(message.str(),1, &answer);
	return 0;
}

int KheperaIII::StopMotors(){
	stringstream message, ssAnswer;
	vector<string> answer;
	message << "$MotorStop,0\r\n";
	sendMsg(message.str(),1, &answer);
	message.str("");
	message << "$MotorStop,1\r\n";
	sendMsg(message.str(),1, &answer);
	return 0;
}

int KheperaIII::StartMotors(){
	stringstream message, ssAnswer;
	vector<string> answer;
	message << "$MotorStart,0\r\n";
	sendMsg(message.str(),1, &answer);
	message.str("");
	message << "$MotorStart,1\r\n";
	sendMsg(message.str(),1, &answer);
	return 0;
}

int	KheperaIII::RecordPulse(int modeLeft, int modeRight, int nStep, int* targetLeft, int* targetRight, int* NAcquisition,
							int** timeStamp, int** valuesLeft, int** valuesRight){
	stringstream message, ssAnswer;
	vector<string> answer;
	message<< "$RecordPulse,"<<modeLeft<<','<<modeRight;
	int N = 0;
	for (int i=0;i<nStep;i++) {
		message<<','<<targetLeft[i]<<','<<targetRight[i]<<','<<NAcquisition[i];
		N+=NAcquisition[i];
	}
	message<<"\r\n";
	sendMsg(message.str(),N+1,&answer);
	*timeStamp = (int*) malloc(N * sizeof(int));
	*valuesLeft = (int*) malloc(N * sizeof(int));
	*valuesRight = (int*) malloc(N * sizeof(int));
	for (int i=0;i<N;i++){
		char comma;
		ssAnswer.clear(); // clear end of stream error flag to allow further read
		ssAnswer.str(answer[i]);
		ssAnswer >> (*timeStamp)[i] >> comma >> (*valuesLeft)[i] >> comma >> (*valuesRight)[i];
	}
	return 0;
}

int KheperaIII::StopInternalTracking(){
	stopContinuousAcquisition = true;
	return 0;
}

int KheperaIII::StartInternalTracking(){
	if (stopContinuousAcquisition == true) {
		LaunchContinuousThread();
	}
	stopContinuousAcquisition = false;
	return 0;
}

void KheperaIII::SetUpdatePositionMode(int mode){
	updatePositionMode=mode;
}

