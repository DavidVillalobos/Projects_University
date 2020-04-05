#include"Sector.h"

struct Sector* initialize_sector(int side){
    struct Sector* sector = malloc(sizeof(struct Sector));
    sector->ambulance_probability = 0;
    sector->average_cars = 0;
    sector->ready = initialize_queue();
    sector->finish = initialize_queue();
    sector->max_velocity_cars = 0;
    sector->min_velocity_cars = 0;
    sector->side = side;
    sector->transit_officer = initialize_officer();
    sector->semaforo = initialize_semaforo();
    return sector;
}