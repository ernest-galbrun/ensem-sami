#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <semaphore.h>

#include "Data.h"
#include "Vehicle.h"

#define MAXDATA 2048

using namespace std;

// Constructor
Data::Data() {
    sem_data = sem_open("data", O_CREAT);
    this->lastReturned = (Vehicle *)malloc(sizeof(Vehicle));

    this->numberOfVehicles = 0;
}

// Destructor
Data::~Data() {
    free(this->data);
    free(this->lastReturned);
    sem_unlink("data");
}
Vehicle *Data::getVehicle(char* name) {
    sem_wait(sem_data);
        for (int i=0; i<this->numberOfVehicles; i++) {
            if (this->data[i]->getName() == name) {
                memcpy(this->lastReturned, this->data[i], sizeof(Vehicle));
            }
        }

    sem_post(sem_data);

    return this->lastReturned;
}

void Data::setMultipleVehicles(Vehicle **data, int number) {
    sem_wait(sem_data);
        for (int i = 0; i<this->numberOfVehicles; i++) {
            free(this->data[i]);
        }

        this->numberOfVehicles = number;
        this->data = data;
    sem_post(sem_data);
}
