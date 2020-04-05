#include"pthread.h"
#include<stdlib.h> // for srand and malloc

//Semaforo, {Color de luz, tiempo}
struct Semaforo{
    int light, time_in_green, time;
    pthread_t tid;
};

struct Semaforo* initialize_semaforo();