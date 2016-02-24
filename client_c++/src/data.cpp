#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <semaphore.h>
#include "Vehicle.cpp"

#define MAXDATA 2048

using namespace std;

// Constructor
Data::Data() {
    sem_data = sem_open("data", O_CREAT);

    this->numberOfVehicles = 0;
}

// Destructor
Data::~Data() {
    free(this->data);
    sem_unlink("data");
}
Vehicle* Data::getVehicle(char* name) {
    Vehicle *data;

    sem_wait(sem_data);
        for (int i=0; i<this->numberOfVehicles; i++) {
            if (this->data[i]->getName() == name) {
                memcpy(data, this->data[i], sizeof(Vehicle));
            }
        }

    sem_post(sem_data);

    return data;
}

void Data::setMultipleVehicles(Vehicle **data, int number) {
    sem_wait(sem_data);
        this->numberOfVehicles = number;

        free(this->data);
        this->data = data;
    sem_post(sem_data);
}
