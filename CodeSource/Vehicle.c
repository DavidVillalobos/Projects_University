#include"Vehicle.h"

void initialize_vehicle(struct Vehicle* car){
    car = malloc(sizeof(struct Vehicle));
    car->direction = 0;
    car->num = 0;
    car->priority = 0;
    car->speed = 0;
}