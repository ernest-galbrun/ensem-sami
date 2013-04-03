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
#include <cmath>

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
using namespace boost::asio;

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
	stopContinuousAcquisition(false),
	previousL(0),
	previousR(0),
	io_service_(),
	work(io_service_),
	timer(io_service_,posix_time::milliseconds(0)),
	socket_(io_service_),
	irAmbientValues(11),
	irProximityValues(11),
	ultrasound(50),
	updateFirstCall(true){
	setId(id);
}

//KheperaIII io thread for processing asyncronous IO functions
void KheperaIII::RunIOService() {
		io_service_.run();
}


// send the message and wait for the response, which must contain n lines, the last one 
// repeating the message command
int KheperaIII::sendMsg(string msg, int n, vector<string>* answer, chrono::duration<double> timeout=chrono::seconds(1))
{
	
	
	if (isVirtual_) {
		throw (logic_error("Invalid call to \"sendMsg\" with virtual robot."));
	}
	tcpLock.lock();
	chrono::system_clock::time_point start = chrono::system_clock::now();
	dataReceived = false;
	tcp_answer = vector<string>();
	system::error_code& ec = system::error_code();
    ostream request_stream(&tcp_buf_write);
    request_stream << msg;
	asio::async_write(socket_,tcp_buf_write,
		boost::bind(&KheperaIII::write_handler,this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred,n,msg));
	int count = 0;
	while ((!dataReceived) && (chrono::system_clock::now() - start < timeout)){
		this_thread::sleep(boost::posix_time::milliseconds(1));
		++count;
	}
	if(!dataReceived) {
		tcpLock.unlock();
		initSuccessful = false;
		throw(TCPFailure(ec.message()));
	}
	*answer = tcp_answer;
	tcpLock.unlock();
	return 0;	
}


void KheperaIII::write_handler(const boost::system::error_code& error,std::size_t bytes_transferred, int n, const string& msg) {
	asio::async_read_until(socket_,tcp_buf_read,"\r\n",
		boost::bind(&KheperaIII::read_handler,this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred,n-1,msg));
}
	

void KheperaIII::read_handler(const boost::system::error_code& error,std::size_t bytes_transferred, int n, const string& msg) {
	istream is(&tcp_buf_read);
	is.getline(buf,1000,'\r');
	is.ignore(1);
	string ans(buf);
	tcp_answer.push_back(ans);
	if (n!=0){		
		asio::async_read_until(socket_,tcp_buf_read,"\r\n",
			boost::bind(&KheperaIII::read_handler,this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred,n-1,msg));
		
	} else {
		string command_sent = msg.substr(1,msg.find_first_of (",\r")-1);
		string ack = tcp_answer.back();
		if (command_sent == ack) {
			dataReceived = true;
		}
	}
}

void KheperaIII::connect_handler(const boost::system::error_code& error) {
  if (!error)  {    
	boost::asio::ip::tcp::no_delay option(true);
	socket_.set_option(option);
	boost::asio::socket_base::keep_alive option2(true);
	socket_.set_option(option2);
	initSuccessful = true;
  }
}

void KheperaIII::OpenTCPConnection(){
	stopTCP=false;
	boost::system::error_code& ec = boost::system::error_code();
	stringstream s;
	s<<"10.10.10."<<getId();
	asio::ip::tcp::resolver resolver(io_service_);
	asio::ip::tcp::resolver::query query(s.str(),"14");
	asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
	asio::ip::tcp::resolver::iterator end;
	cout << "Establishing connection with the Robot..." << endl;
	while (iter != end) {
		socket_.async_connect(*iter,boost::bind(&KheperaIII::connect_handler,this,boost::asio::placeholders::error));
		iter++;
	}
	
	TCPThread = thread(&KheperaIII::RunIOService,this);
	for (int i=0;(i<100) & (!initSuccessful);++i) {
		this_thread::sleep(boost::posix_time::milliseconds(20));
	}
	if (!initSuccessful) {
		throw(TCPFailure(ec.message()));
	}	else {
		vector<string> ans;
		sendMsg("$SetAcquisitionFrequency1x,0,1\r\n",1,&ans);
		sendMsg("$SetAcquisitionFrequency1x,1,1\r\n",1,&ans);
		getEncodersValue(&previousL, &previousR);
	}
}
	
void KheperaIII::Init(){
	initSuccessful = false;
	tick = 0;	
	if (!isVirtual_){		
		OpenTCPConnection();		
		LaunchComm();
	}
	else {
		encoderValues[0] = 0;
		encoderValues[1] = 0;
		LaunchComm();
	}
}

KheperaIII::~KheperaIII() {
	stopContinuousAcquisition = true;
	if (continuousThread.joinable()) {
		continuousThread.join();
	}
	stopTCP=true;
	closeSession();
	io_service_.stop();
	if (TCPThread.joinable()) {
		TCPThread.join();
	}
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
		try {
			timeStep();
		} catch (TCPFailure e) {
			break;
		}
	}
}

void KheperaIII::FollowLine(bool on,float aggressivity,int speed){
 if (!isVirtual_){
	stringstream msg;
	if (on)
		msg << "$FollowLine,"<<"1,"<<aggressivity<<','<<speed<<"\r\n";
	else
		msg << "$FollowLine,0,0,0\r\n";
	vector<string> ans;
	this->sendMsg(msg.str(),1,&ans);
 }

}

void KheperaIII::Cross(int direction, float aggressivity, int speed){
	 if (!isVirtual_){
	stringstream msg;
	msg << "$Cross,"<<direction<<','<<aggressivity<<','<<speed<<"\r\n";
	vector<string> ans;
	this->sendMsg(msg.str(),1,&ans,chrono::seconds(30));
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
	SendPositionUDP();
}

void KheperaIII::UpdatePosition() {
	if (updatePositionMode==0 || (updatePositionMode==2 && !updateFirstCall)) {
		UpdatePositionOffline();
	}
	else if (updatePositionMode==1 || updateFirstCall) {
		updateFirstCall = false;
		try {
			this->Object::UpdatePosition();
			int encoderValueLeft,encoderValueRight;
			if (updatePositionMode==2)	{
				getEncodersValue(&encoderValueLeft,&encoderValueRight);
			} else {
				encoderValueLeft = 0;
				encoderValueRight = 0;
			}
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
	// sometimes, the robot erroneously returns a value with an offset of 16776960
	// this detects the offset and ignores it...
	if (abs(encoderValueLeft-previousL) > 100000)
		return;//encoderValueLeft+=16776960;
	if (abs(encoderValueRight-previousR) > 100000)
		return;//encoderValueRight+=16776960;
	

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

void KheperaIII::closeSession()
{	
	if (!isVirtual_){
		if (initSuccessful){
			this->setVelocity(0,0);
			socket_.close();
		}
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
		
		sendMsg(message.str(),N+1,&answer,chrono::seconds(60));
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

void KheperaIII::AllowIncomingUDPConnection(int port){

	if (isVirtual_){
		return;
	}
	stringstream message;
	string ip(GetOwnIP_wifi());
	replace(ip.begin(),ip.end(),('.'),(','));
	message<< "$AllowUDPUpdate,"<<ip<<','<<port<<"\r\n";
	vector<string> answer;
	sendMsg(message.str(),1, &answer);
	LaunchUDPServer(port);
}