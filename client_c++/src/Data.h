#ifndef DATA_H
#define DATA_H

#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <boost/thread/mutex.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

#include "Vehicle.h"
#include "Data.h"

using namespace std;

class SocketBoost;

class Data
{

	private:
		boost::mutex dataLock;
		boost::mutex dataLockName;
		vector<Vehicle> data;
		vector<string> nameInfo;
		vector<int> posInfo;
		vector<string> getPointsNames(string name);

		int timeToWait;
		string ip;
		string port;

	public:
		Data();
  	Data(const Data & data);
		vector<string> getVehiclesNames();
		Vehicle getVehicle(string name);
		void setAll(std::vector<Vehicle> data);
		void setPointsNames(vector<string> nameInfo, vector<int> posInfo);

		void setIp(string ip);
		void setPort(string port);
		void setTimeToWait(int timeToWait);

};

#endif
