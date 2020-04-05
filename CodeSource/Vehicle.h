#include<pthread.h>
#include<stdlib.h> // for srand and malloc

//Carros, {Velocidad, Direccion, Placa, Prioridad}
struct Vehicle{
    int speed, direction, num, priority;
    pthread_t tid;
};

void initialize_vehicle(struct Vehicle* car);