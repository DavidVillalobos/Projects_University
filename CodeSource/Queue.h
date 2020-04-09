#include <stdlib.h> // for srand and malloc
#include <stdio.h> // for printf and scanf
#include"Vehicle.h"

//Cola, {Primero, Ultimo}
struct Queue{
    struct Node* first;
    struct Node* last;
    int size;
    int cantAmbulances;
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