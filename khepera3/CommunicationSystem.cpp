#include <sstream>
#include <string>
#include <array>
#include "CommunicationSystem.h"
#include "Sender.h"
#define WIN32_LEAN_AND_MEAN 

//#include <windows.h>
using namespace std;
using namespace std::tr1;

CommunicationSystem::CommunicationSystem(int id, std::string adMult, int porMult):
	sender(boost::asio::ip::address::from_string(/*"10.10.10.105"*/adMult),porMult),
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


void CommunicationSystem::sendPosition(int id,const std::array<double,2>& position, const double& orientation)
{
	if(enable)
	{
	sender.sendPosition(id,position,orientation);
	}
 }

bool CommunicationSystem::Enabled(){
	return enable;
}


//bool CommunicationSystem::ReceivePosition(int& id, array<double,2>& position){
//	bool result = receiver.ReceivePosition(id, position);/*
//	cout<<result<<"\r\n";
//	cout<<"position received : "<<id<<"\r\n";*/
//	return result;
//}