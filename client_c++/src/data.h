#include <semaphore.h>
#include "Vehicle.cpp"

#ifndef DATA_H
#define DATA_H

class Data {

	private:
        Vehicle **data;
        sem_t *sem_data;
		int numberOfVehicles;

	public:
        Data();
        ~Data();
        Vehicle getVehicle(char* name);
		void setMultipleVehicles(Vehicle **data, int number);
};

#endif
