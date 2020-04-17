#include <pthread.h> // for threads
#include <stdlib.h> // for srand and malloc
#include <stdio.h> // for printf and scanf

//Entidad del sector
struct Sector{
    int side;//id sector 0 oeste, 1 este, . . .
    //Media de la formula de distribucion exponencial
    // del tiempo de llegada de los vehiculos en cada sentido
    int average_cars;
    // Minimo y maximo de velocidad de los carros en cada sentido
    int min_velocity_cars;
    int max_velocity_cars;
    //Probabilidad de ambulancia en cada sentido
    int ambulance_probability;
    //Cola en espera por cruzar el puente
    struct Queue* ready;
    //Cola despues de cruzar
    struct Queue* finish;//(aqui llegan los que venian del otro sector)
    int time_semaphore;
    int ki_cars;
};

struct Sector* initialize_sector(int side);

//Carros, {Velocidad, Direccion, Placa, Prioridad (Ambulancia)}
struct Vehicle{
    int speed, direction, plate, priority;
};

//Cola, {Primero, Ultimo}
struct Queue{
    struct Node* first;
    struct Node* last;
    int size;
    int sizeAmbulances;
};

//Nodo de Cola, {Carro, Siguiente}
struct Node{
    struct Vehicle* car;
    struct Node* next;
};

struct Queue* initialize_queue();

//Encolar o Poner en cola
void enqueue(struct Queue* cola, struct Vehicle* car);

//Encolar o Poner en cola con prioridad
void enqueue_priority(struct Queue* cola, struct Vehicle* car);

//Desencolar o quitar de la cola
struct Vehicle* dequeue(struct Queue* cola);

//Imprime la cola
void show_queue(struct Queue* cola);
