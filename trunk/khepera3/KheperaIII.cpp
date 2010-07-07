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
	nIrSensors = NB_SENSORS;
	axis = AXIS;
	irValues = (int*)malloc(nIrSensors*sizeof(int));
	//serial = new CSerial();
	long aux1,aux2;
	
	localizationSystem = new LocalizationSystem(this);
	communicationSystem = new CommunicationSystem(this);

	stringstream s;
	s<<"10.10.10."<<id;

	asio::ip::tcp::resolver resolver(io_service_);
	asio::ip::tcp::resolver::query query(s.str(),"14");
	asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
	asio::ip::tcp::resolver::iterator end;
	socket_ = boost::shared_ptr<boost::asio::ip::tcp::socket>(new asio::ip::tcp::socket(io_service_));
	cout << "Estabilishing connection with the Robot..." << endl;
	boost::system::error_code& ec = boost::system::error_code();
	while (iter != end) {
		socket_->connect(*iter,ec);
		if (ec == false)
			break;
	}

	if (ec) {
		cout<< "ERROR: connection to the robo failed. Error code: "<<ec<<".\n";
	}
	//serialPort = serialPortArg;
	
		
	//wstring str2(serialPort.length(), L' '); 

	//copy(serialPort.begin(), serialPort.end(), str2.begin());

//#ifdef MEX_COMPILER
//	long a = serial->Open(serialPort.c_str());
//#else
//	long a = serial->Open((LPCSTR)str2.c_str());
//#endif
//	
//	testSerial = a;
	//if(a==0)
	//{
	//	
	//	aux1=serial->Setup(CSerial::EBaud115200,CSerial::EData8,CSerial::EParNone,CSerial::EStop1);
	//	aux2=serial->SetupHandshaking(CSerial::EHandshakeHardware);
	//	cout << "Done!!!" << endl;
	//}
	/*else
	{
		cout << "ERROR: Can not access the robot!!!" << endl;
		exit(0);
	}*/
}

KheperaIII::~KheperaIII()
{
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

	this->sendMsg(msg);
}

void KheperaIII::timeStep()
{	
	//NEED REAL-TIME
	//Sleep(TIME_STEP);
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
	return irValues;
}



void KheperaIII::setEncodersValue(int lValue,int rValue)
{
	string msg = this->encodersMsg(lValue,rValue);
	this->sendMsg(msg);
}
int* KheperaIII::getEncodersValue()
{
	int* ret = (int*)malloc(2*sizeof(int));
	/*string aux;
	string::size_type index;
	

	string commandMsg = "R\n";
	string data = this->sendMsg(commandMsg);

	
	index = data.find(",",0);
	data = data.substr(index+1);
	index = data.find(",",0);
	aux = data.substr(0,index);
	ret[0] = atoi(aux.c_str());
	aux = data.substr(index+1);
	ret[1] = atoi(aux.c_str());*/

	
	return ret;
}
//AUXILIAR METHODS--------------------------------------------
string KheperaIII::speedMsg(double lSpeed, double rSpeed)
{
	string msg = "D,l";
	
	//char *myBuff;
	//// Create a new char array
	//myBuff = new char[100];
	//// Set it to empty
	//memset(myBuff,'\0',100);
	//// Convert lSpeed to string
	//_itoa_s((int)lSpeed,myBuff,100,10);
	//// Copy the lSpeed into the msg
	//msg = msg+myBuff+",l";
	//// Set it to empty
	//memset(myBuff,'\0',100);
	//// Convert rSpeed to string
	//_itoa_s((int)rSpeed,myBuff,100,10);
	//msg = msg+myBuff+"\n";
	//// Delete the buffer
	//delete[] myBuff;

	return msg;
}

string KheperaIII::encodersMsg(int lValue, int rValue)
{
	string msg = "I,l";
	
	//char *myBuff;
	//// Create a new char array
	//myBuff = new char[100];
	//// Set it to empty
	//memset(myBuff,'\0',100);
	//// Convert lSpeed to string
	//_itoa_s(lValue,myBuff,100,10);
	//// Copy the lSpeed into the msg
	//msg = msg+myBuff+",l";
	//// Set it to empty
	//memset(myBuff,'\0',100);
	//// Convert rSpeed to string
	//_itoa_s(rValue,myBuff,100,10);
	//msg = msg+myBuff+"\n";
	//// Delete the buffer
	//delete[] myBuff;

	return msg;
}
string KheperaIII::sendMsg(string msg)
{
	//byte abBuffer[1000];
 //   memset(abBuffer,'\0',1000);

	//byte msgAux[1000];
	//memset(msgAux,'\0',1000);

	//string data = "";
	//DWORD dwBytesRead;
	//int nRec;
	//int i;
	//int stop;
	//

	////serial->Write(msg.c_str());
	//
	//dwBytesRead = 0;
 //   nRec = 0;
	//stop = 0;

	//while(stop==0)
	//{
	//serial->WaitEvent();
	//serial->SetupReadTimeouts(CSerial::EReadTimeoutNonblocking);
	//serial->Read(abBuffer,sizeof(abBuffer),&dwBytesRead);
	//	for(i=0; i<dwBytesRead; i++)
	//	{
	//		if(abBuffer[i] == 0x0A)
	//			{	
	//				stop =1;
	//				i=dwBytesRead;
	//			}
	//		else
	//			{
	//				if(stop == 0)
	//				{msgAux[i+nRec] = abBuffer[i];}
	//			}
	//	}
	//	nRec= nRec+dwBytesRead;
	//}
	//
	//for(i=0;i<nRec;i++)
	//{
	//	data = data + (char)msgAux[i];
	//}
	////cout << "data: " << data << " msgAux: " << msgAux <<endl;

	return "";
}

void KheperaIII::initComm(std::string adLoc, std::string adMult, int porMult)
{
	boost::thread thr(boost::bind(&CommunicationSystem::init,communicationSystem,adLoc, adMult,porMult));
}

void KheperaIII::closeSession()
{
	this->setVelocity(0,0);
	//serial->Close();
}