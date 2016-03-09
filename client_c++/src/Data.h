#include <semaphore.h>
#include "Vehicle.h"

#ifndef DATA_H
#define DATA_H

using namespace std;

class Data {

	private:
		bool charCompare(string c1, string c2);
        Vehicle **data;
		int numberOfVehicles;
        sem_t *sem_data;

	public:
		Vehicle *lastReturned;

        Data();
        ~Data();
        Vehicle *getVehicle(string name);
		void setMultipleVehicles(Vehicle **data, int number);
};

#endif
