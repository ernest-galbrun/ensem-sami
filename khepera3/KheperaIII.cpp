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
#include <stdexcept>

#include <ctime>

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <boost/chrono.hpp>

#include "LocalizationSystem.h"
#include "KheperaIII.h"
#include "CommunicationSystem.h"

using namespace std;
using namespace boost;

//int KheperaIII::getTestSerial()
//{return testSerial;}

//CONSTRUCTOR AND DESTRUCTOR----------------------------------
KheperaIII::KheperaIII(int id, bool isVirtual, vector<double> initialPosition, double initialOrientation):
	Agent(id, initialPosition, initialOrientation),
	isVirtual_(isVirtual),
	initSuccessful(false),
	updatePositionMode(0),
	angularSpeed_(0),
	linearSpeed_(0),
	axis(AXIS),
	nIrSensors(NB_SENSORS),
	irValues(vector<int>(nIrSensors)),
	firstRead(true),
	stopContinuousAcquisition(false),
	previousL(0),
	previousR(0),
	io_service_(),
	timer(io_service_,posix_time::milliseconds(0)),
	socket_(io_service_),
	tcp_buf(1000),
	irAmbientValues(11),
	irProximityValues(11),
	ultrasound(50){
	setId(id);
}
	
void KheperaIII::Init(){
	initSuccessful = false;
	tick = 0;	
	if (!isVirtual_){
		stringstream s;
		s<<"10.10.10."<<getId();
		asio::ip::tcp::resolver resolver(io_service_);
		asio::ip::tcp::resolver::query query(s.str(),"14");
		asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
		asio::ip::tcp::resolver::iterator end;
		cout << "Establishing connection with the Robot..." << endl;
		boost::system::error_code& ec = boost::system::error_code();
		while (iter != end) {
			socket_.connect(*iter,ec);
			if (ec == false)
				break;
			iter++;
		}
		if (ec) {
			throw(ios_base::failure(ec.message()));
		}
		else {
			initSuccessful = true;
			vector<string> ans;
			sendMsg("$SetAcquisitionFrequency1x,0,1\r\n",1,&ans);
			sendMsg("$SetAcquisitionFrequency1x,1,1\r\n",1,&ans);
			getEncodersValue(&previousL, &previousR);
			LaunchComm();
		}
	}
	else {
		encoderValues[0] = 0;
		encoderValues[1] = 0;
		LaunchComm();
	}
}

KheperaIII::~KheperaIII()
{
	stopContinuousAcquisition = true;
	continuousThread.join();
	closeSession();
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
	while (!stopContinuousAcquisition){
		lastStepTime = posix_time::microsec_clock::local_time();
		this_thread::sleep(boost::posix_time::milliseconds(TIME_STEP));
		timeStep();
	}
}
//FUNCTIONAL METHODS------------------------------------------
//vSpeed: mm/s		wSpeed: rad/s positive->clockwise
void KheperaIII::setVelocity(double vSpeed, double wSpeed)
{
	if (isVirtual_) {
		linearSpeed_ = vSpeed;
		angularSpeed_ = wSpeed;
	}
	else {
	double rSpeed;
	double lSpeed;	
	lSpeed = K_SPEED*(vSpeed - wSpeed*axis/2);
	rSpeed = K_SPEED*(vSpeed + wSpeed*axis/2);
	string msg = this->speedMsg((int)lSpeed,(int)rSpeed);
	vector<string> ans;
	this->sendMsg(msg,1,&ans);
	}
}

void KheperaIII::timeStep()
{	

	trackGenerator.nextStep();
	UpdatePosition();
	SendPosition();	
}

void KheperaIII::UpdatePosition() {
	if (updatePositionMode==0) {
		UpdatePositionOffline();
	}
	else if (updatePositionMode==1) {
		try {
			this->Object::UpdatePosition();
			int encoderValueLeft,encoderValueRight;
			//getEncodersValue(&encoderValueLeft,&encoderValueRight);
			encoderValueLeft = 0;
			encoderValueRight = 0;
			previousL = encoderValueLeft;
			previousR = encoderValueRight;
		}
		catch(ios_base::failure e){
			UpdatePositionOffline();
		}			
	}
}


void KheperaIII::UpdatePositionOffline() {
	double dl, dr, dc, thetaAux;
	int encoderValueLeft,encoderValueRight;
	std::array<double,2> position = getPosition();
	double orientation = getOrientation();
	posix_time::time_duration timeStepDuration = posix_time::microsec_clock::local_time() - lastStepTime;
	if (isVirtual_){
		orientation += angularSpeed_ * timeStepDuration.total_microseconds() / 1000000. / 2;
		position[0] += cos(orientation) * linearSpeed_ * timeStepDuration.total_microseconds() / 1000000.;
		position[1] += sin(orientation) * linearSpeed_ * timeStepDuration.total_microseconds() / 1000000.;
		orientation += angularSpeed_ * timeStepDuration.total_microseconds() / 1000000. / 2;
		setPosition(position[0],position[1]);
		setOrientation(orientation);
	}
	else {
	getEncodersValue(&encoderValueLeft,&encoderValueRight);
	dl = (encoderValueLeft-previousL)*K_ENCODER;
	dr = (encoderValueRight-previousR)*K_ENCODER;
	dc = (dl+dr)/2;
	thetaAux = orientation;
	orientation += ((dr-dl)/AXIS);			
	(position)[0] += dc*cos( (orientation + thetaAux) / 2);
	(position)[1] += dc*sin( (orientation + thetaAux) / 2);
	setPosition(position[0],position[1]);
	setOrientation(orientation);
	previousL = encoderValueLeft;
	previousR = encoderValueRight;
	}
}

const vector<int>& KheperaIII::getIrOutput()
{
	if (isVirtual_){
		for(unsigned int i=0;i<irValues.size();++i)
		{
			irValues[i] = 0;
		}	
	}

	for(unsigned int i=0;i<irValues.size();++i)
	{
		irValues[i] = 0;
	}
	return irValues;
}

void KheperaIII::setEncodersValue(int lValue,int rValue)
{
	if (isVirtual_) {
		return;
	}
	string msg = this->encodersMsg(lValue,rValue);
	vector<string> ans;
	this->sendMsg(msg,1,&ans);
}
void KheperaIII::getEncodersValue(int *left, int* right)
{	
	if (isVirtual_) {
		*left = 0;
		*right = 0;
		return;
	}
	else {
		vector<string> ans;
		stringstream ss;
		char comma;
		clock_t t1,t2;
		t1 = clock();
		
		if(!sendMsg("$GetPosition\r\n",2,&ans)) {
			ss.str(ans[0]);
			ss>>encoderValues[0]>>comma>>encoderValues[1];
		}
		t2 = clock() - t1;
		t2 = t2;
		*left = encoderValues[0];
		*right = encoderValues[1];
	}
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
	
	boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();
	if (isVirtual_) {
		throw (logic_error("Invalid call to \"sendMsg\" with virtual robot."));
	}
	tcpLock.lock();
	
	char buf[1000];
	*answer = vector<string>();
	asio::write(socket_,asio::buffer(msg));
	string ans;
	size_t	bytesRead;
	system::error_code& ec = system::error_code();
	istream is(&tcp_buf);
	if (!firstRead) {
		asio::read_until(socket_,tcp_buf,"\r\n",ec);
		is.getline(buf,1000,'\r');
		is.ignore(1);
	}
	else
		firstRead = false;
	for (int i=0;i<n-1;i++){
		clock_t t1,t2;
		t1 = clock();
		bytesRead = asio::read_until(socket_,tcp_buf,"\r\n",ec);
		t2 = clock() - t1;
		t2 = t2;
		is.getline(buf,1000,'\r');
		is.ignore(1);
		ans = string(buf);
		answer->push_back(ans);
	}
	boost::chrono::duration<double> sec = boost::chrono::system_clock::now() - start;
	double test  = sec.count();
    std::cout << "took " << sec.count() << " seconds\n";
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
	if (!isVirtual_){
		if (initSuccessful)
			this->setVelocity(0,0);
		socket_.close();
	}
}

int KheperaIII::GetMode(int* left, int* right){
	if (isVirtual_) {
		*left = 0;
		*right = 0;
		return 0;
	}
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
	if (isVirtual_) {
		for (int i=0;i<3;i++)
			(*PIDLeft)[i]=0;
		for (int i=0;i<3;i++)
			(*PIDRight)[i]=0;
		return 0;
	}
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
	if (isVirtual_) {
		*left = 0;
		*right = 0;
		return 0;
	}
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
	if (isVirtual_)
		return 0;
	stringstream message, ssAnswer;
	vector<string> answer;
	message << "$SetMode,"<<left<<','<<right<<"\r\n";
	sendMsg(message.str(),1, &answer);
	return 0;
}

int KheperaIII::SetPID(int pLeft, int iLeft, int dLeft, int pRight, int iRight, int dRight){	
	if (isVirtual_)
		return 0;
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
	if (isVirtual_)
		return 0;
	stringstream message, ssAnswer;
	vector<string> answer;
	message << "$SetPoint,"<<targetLeft<<','<<targetRight<<"\r\n";
	sendMsg(message.str(),1, &answer);
	return 0;
}

int KheperaIII::ResetPosition(int posLeft, int posRight){
	if (isVirtual_)
		return 0;
	stringstream message, ssAnswer;
	vector<string> answer;
	message << "$ResetPosition,"<<posLeft<<','<<posRight<<"\r\n";
	sendMsg(message.str(),1, &answer);
	return 0;
}

int KheperaIII::StopMotors(){
	if (isVirtual_)
		return 0;
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
	if (isVirtual_)
		return 0;
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
	if (isVirtual_) {
		*timeStamp = (int*) malloc(N * sizeof(int));
		*valuesLeft = (int*) malloc(N * sizeof(int));
		*valuesRight = (int*) malloc(N * sizeof(int));
		for (int i=0;i<N;i++){
			(*timeStamp)[i] = i;
			(*valuesLeft)[i] = 0;
			(*valuesRight)[i] = 0;
		}
	}
	else {
		
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
	}
	return 0;
}

int KheperaIII::StopInternalTracking(){
	stopContinuousAcquisition = true;
	return 0;
}

int KheperaIII::StartInternalTracking(){
	if (stopContinuousAcquisition) {
		LaunchContinuousThread();
	}
	stopContinuousAcquisition = false;
	return 0;
}

void KheperaIII::SetUpdatePositionMode(int mode){
	updatePositionMode=mode;
}

void KheperaIII::GetAmbientIR(int* timestamp, int** values){
	
	if (isVirtual_){
		*timestamp = 0;
		*values = &irAmbientValues[0];
		return;
	}
	stringstream message, ssAnswer;
	vector<string> answer;
	char comma;	
	message << "$GetInfraredAmbient\r\n";
	sendMsg(message.str(), 2, &answer);
	ssAnswer.str(answer[0]);
	ssAnswer>>*timestamp;
	for (unsigned int i=0;i<irAmbientValues.size();++i){
		ssAnswer >> comma >> irAmbientValues[i];
	}
	*values = &irAmbientValues[0];
}


void KheperaIII::GetProximityIR(int* timestamp, int** values){
	if (isVirtual_){
		*timestamp = 0;
		*values = &irProximityValues[0];
		return;
	}
	stringstream message, ssAnswer;
	vector<string> answer;
	char comma;	
	message << "$GetInfraredProximity\r\n";
	sendMsg(message.str(), 2, &answer);
	ssAnswer.str(answer[0]);
	ssAnswer >>*timestamp;
	for (unsigned int i=0;i<irProximityValues.size();++i){
		ssAnswer >>comma >> irProximityValues[i];
	}
	*values = &irProximityValues[0];
}


void KheperaIII::GetUltrasound(int** values){
	if (isVirtual_){
		*values = &ultrasound[0];
		return;
	}
	stringstream message, ssAnswer;
	vector<string> answer;
	char comma;	
	message << "$GetUltrasound\r\n";
	sendMsg(message.str(), 2, &answer);
	ssAnswer.str(answer[0]);
	for (unsigned int i=0;i<ultrasound.size();++i){
		ssAnswer >> ultrasound[i];
		if (i!=ultrasound.size())
			ssAnswer >> comma;
	}
	*values = &ultrasound[0];
}