#include"pthread.h"
#include<stdlib.h> // for srand and malloc
#include <unistd.h>// for sleep

//Semaforo, {Color de luz, tiempo}
struct Semaforo{
    int light, time_in_green, time;
    pthread_t tid;
};

//Inicializa el semaforo
struct Semaforo* initialize_semaforo();

//Temporizador del Semaforo
void* timer(void* arg);