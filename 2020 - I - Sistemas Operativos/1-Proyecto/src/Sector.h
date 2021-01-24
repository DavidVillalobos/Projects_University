#include <pthread.h> // for use threads
#include <stdlib.h> // for use srand and malloc
#include <stdio.h> // for use printf and scanf

//Entidad del sector
struct Sector{
    int side;/* id sector 0 oeste, 1 este, . . .
    Media de la formula de distribucion exponencial
    del tiempo de llegada de los vehiculos en cada sentido */
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

//Nodo de Cola, {Carro, Siguiente, anterior}
struct Node{
    struct Vehicle* car;
    struct Node* next;
    struct Node* prev;
};

struct Sector* initialize_sector(int side);

struct Queue* initialize_queue();

//Encolar o Poner en cola
void enqueue(struct Queue* cola, struct Vehicle* car);

//Desencolar o sacar de la cola
struct Vehicle* dequeue(struct Queue* cola);

//Imprime la cola
void show_queue(struct Queue* cola);

//Encolar o Poner en cola con prioridad
void enqueue_priority(struct Queue* cola, struct Vehicle* car);

//Desencolar o quitar de la cola
struct Vehicle* dequeue(struct Queue* cola);

//Busca un Nodo que contenga el vehiculo car en la cola
struct Node* searchNode(struct Queue* cola, struct Vehicle* car);

/* Verifica y coloca a una ambulancia lo mas
   adelante posible (Hasta topar con otra ambulancia) */
void check_priority(struct Queue* cola, struct Vehicle* car, int way_bridge);

/* Encola con prioridad (coloca a una ambulancia lo mas
   adelante posible (Hasta topar con otra ambulancia) */
void enqueue_priority(struct Queue* cola, struct Vehicle* car);