#include "CommunicationSystem.h"
#include "Receiver.h"
#include "Sender.h"
#define WIN32_LEAN_AND_MEAN 

//#include <windows.h>
#include "KheperaIII.h"
#include "Agent.h"

CommunicationSystem::CommunicationSystem(KheperaIII *robotArg)
{
	robot = robotArg;
	enable = 0;
}

CommunicationSystem::~CommunicationSystem()
{
}

void CommunicationSystem::init(std::string adLoc, std::string adMult, int porMult)
{
	localAddress = adLoc;
	multicastAddress = adMult;
	multicastPort = porMult;
	receiver = new Receiver(io_service,boost::asio::ip::address::from_string("0.0.0.0"),boost::asio::ip::address::from_string(multicastAddress),multicastPort,this);
	sender = new Sender(io_service2, boost::asio::ip::address::from_string(multicastAddress),multicastPort);

	enable = 1;
	receiver->run();
	io_service.run();
	io_service2.run();
	
}

void CommunicationSystem::reorganizeNeighbors(int idArg, double xArg, double yArg)
{

	
	if(robot->getId() != idArg && enable==1)
	{
		if(robot->getnNeighbors()==0)
		{
			Agent *neighbors = new Agent[1]; 
			neighbors[0].setId(idArg);
			neighbors[0].setPosition(xArg,yArg);
			robot->setNeighbors(neighbors);
			robot->setnNeighbors(1);
			
			std::cout << "Primeiro Vizinho:" << std::endl;
			std::cout << "id: " <<idArg <<" x: " << xArg << " y: " << yArg << std::endl;
		}
		else
		{
			int test = this->testNeighbor(idArg);
			
			if(test != 99) // neighbor already exist
			{
				//std::cout << "vizinho velho:" << std::endl;
				robot->getNeighbors()[test].setPosition(xArg,yArg);
			}
			else //new neighbor
			{
				std::cout << "novo vizinho:" << std::endl;
				std::cout << "id: " <<idArg <<" x: " << xArg << " y: " << yArg << std::endl;
				Agent *neighbors = new Agent[robot->getnNeighbors()+1];
				
				this->copyNeighbors(neighbors);
				neighbors[robot->getnNeighbors()].setId(idArg);
				neighbors[robot->getnNeighbors()].setPosition(xArg,yArg);
				
				robot->setNeighbors(neighbors);
				robot->setnNeighbors(robot->getnNeighbors()+1);
			}
		}
	}
}

void CommunicationSystem::sendPosition()
{
	if(enable==1)
	{
	sender->sendPosition(robot->getId(),robot->getPosition()[0],robot->getPosition()[1]);
	}
}

int CommunicationSystem::testNeighbor(int idArg)
{
	int i;
	int aux = 99;
	for(i=0;i < robot->getnNeighbors();i++)
	{
		if(robot->getNeighbors()[i].getId() == idArg)
		{aux = i;}
	}

	return aux;
}

void CommunicationSystem::copyNeighbors(Agent* neighCopy)
{
	int i;
	for(i=0;i < robot->getnNeighbors();i++)
	{
		neighCopy[i].setId(robot->getNeighbors()[i].getId());
		neighCopy[i].setPosition(robot->getNeighbors()[i].getPosition()[0],robot->getNeighbors()[i].getPosition()[1]);
	}
}