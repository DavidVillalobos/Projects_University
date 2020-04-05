#include<stdlib.h> // for srand and malloc
#include"Queue.h"
#include"Semaforo.h"
#include"Officer.h"

//sector, cada lado de la simulacion
struct Sector{
    //Lado del sector 0 oeste, 1 este, . . .
    int side;//id
    //Media de la formula de distribucion exponencial
    // del tiempo de llegada de los vehiculos en cada sentido
    int average_cars;
    // Minimo y maximo de velocidad de los carros en cada sentido
    int min_velocity_cars;
    int max_velocity_cars;
    //Probabilidad de ambulancia en cada sentido
    int ambulance_probability;
    //Oficial de transito
    struct Officer* transit_officer;
    //Cola en espera por cruzar el puente
    struct Queue* ready;
    //Cola despues de cruzar
    struct Queue* finish;//(aqui llegan los que venian del otro sector)
    //Semaforo del sector
    struct Semaforo* semaforo;
};

struct Sector* initialize_sector(int side);