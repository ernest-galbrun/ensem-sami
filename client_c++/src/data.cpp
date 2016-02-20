#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <semaphore.h>
#include "Vehicle.cpp"

#define MAXDATA 2048

using namespace std;

class Data {
    private:
        Vehicle *data;
        sem_t *sem_data;

    public:
        // Constructor
        Data() {
            this->data = (Vehicle*)malloc(sizeof(Vehicle));
            sem_data = sem_open("data", O_CREAT);
        }

        // Destructor
        ~Data() {
            free(this->data);
            sem_unlink("data");
        }
        Vehicle getData() {
            sem_wait(sem_data);

            Vehicle data;
            memcpy(data, this->data, sizeof(Vehicle));

            sem_post(sem_data);

            return data;
        }

        void setData(Vehicle *data) {
            sem_wait(sem_data);

            memcpy(this->data, data, sizeof(Vehicle));

            sem_post(sem_data);
        }
};
