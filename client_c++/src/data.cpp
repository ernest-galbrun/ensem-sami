#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <semaphore.h>

#define MAXDATA 2048

using namespace std;

class Data {
    private:
        char *data;
        sem_t *sem_data;

    public:
        // Constructor
        Data() {
            this->data = (char*)malloc(MAXDATA*sizeof(char)+1);
            sem_data = sem_open("data", O_CREAT);
        }

        // Destructor
        ~Data() {
            free(this->data);
            sem_unlink("data");
        }
        void getData() {
            sem_wait(sem_data);

            sem_post(sem_data);
        }

        void setData() {
            sem_wait(sem_data);

            sem_post(sem_data);
        }
};
