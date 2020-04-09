#include"Semaforo.h"

struct Semaforo* initialize_semaforo(){
    struct Semaforo* semaforo = malloc(sizeof(struct Semaforo));
    semaforo->light = 0;
    semaforo->time = 0;
    semaforo->time_in_green = -1;
    return semaforo;
}

void* timer(void* arg){
    struct Semaforo* semaforo  = (struct Semaforo*) arg;
    for (int i = semaforo->time_in_green; 0 < i; i--){
        semaforo->time = i;
        sleep(1);
    }
    semaforo->light = 0;
    pthread_exit(0);
}