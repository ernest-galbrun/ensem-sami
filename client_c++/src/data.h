#include <semaphore.h>
#include "Vehicle.h"

#ifndef DATA_H
#define DATA_H

class Data {

	private:
		bool charCompare(char* c1, char* c2);
        Vehicle **data;
		int numberOfVehicles;
        sem_t *sem_data;

	public:
		Vehicle *lastReturned;

        Data();
        ~Data();
        Vehicle *getVehicle(char* name);
		void setMultipleVehicles(Vehicle **data, int number);
};

#endif
