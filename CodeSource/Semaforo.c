#include"Semaforo.h"

struct Semaforo* initialize_semaforo(){
    struct Semaforo* semaforo = malloc(sizeof(struct Semaforo));
    semaforo->light = 0;
    semaforo->time = 0;
    semaforo->time_in_green = 0;
    return semaforo;
}