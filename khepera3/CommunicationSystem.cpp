#include <sstream>
#include <string>
#include "CommunicationSystem.h"
#include "Receiver.h"
#include "Sender.h"
#define WIN32_LEAN_AND_MEAN 

//#include <windows.h>
using namespace std;

CommunicationSystem::CommunicationSystem(int id, std::string adMult, int porMult):
	receiver(boost::asio::ip::address::from_string("0.0.0.0"),boost::asio::ip::address::from_string(adMult),porMult),
	sender(boost::asio::ip::address::from_string(adMult),porMult),
	multicastAddress(adMult),
	multicastPort(porMult),
	enable(true)
{
	stringstream ss_localip;
	ss_localip<<"10.10.10."<<id;
	localAddress = ss_localip.str();
}

CommunicationSystem::~CommunicationSystem()
{
}


void CommunicationSystem::sendPosition(int id,const boost::array<double,2>& position)
{
	if(enable)
	{
	sender.sendPosition(id,position);
	}
}

bool CommunicationSystem::Enabled(){
	return enable;
}


bool CommunicationSystem::ReceivePosition(int& id, boost::array<double,2>& position){
	bool result = receiver.ReceivePosition(id, position);/*
	cout<<result<<"\r\n";
	cout<<"position received : "<<id<<"\r\n";*/
	return result;
}