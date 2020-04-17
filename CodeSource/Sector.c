#include"Sector.h"

//Inicializar una cola
struct Queue* initialize_queue(){
    struct Queue* cola = malloc(sizeof(struct Queue));
    cola->first = NULL;
    cola->last = NULL;
    cola->size = 0;
    cola->sizeAmbulances = 0;
    return cola;
}

//Encolar o Poner en cola
void enqueue(struct Queue* cola, struct Vehicle* car) {
    struct Node* nodo = malloc(sizeof(struct Node));
    nodo->car = car;
    nodo->next = NULL;
    if(cola->first){
        cola->last->next = nodo;
        cola->last = nodo;
    }else{
        cola->first = cola->last = nodo;
    }
    cola->size++;
}

void enqueue_priority(struct Queue* cola, struct Vehicle* car){
    struct Node* nodo = malloc(sizeof(struct Node));
    nodo->car = car;
    nodo->next = NULL;
    if(cola->first){
        nodo->next = cola->first; 
        cola->first = nodo;
    }else{
        cola->first = cola->last = nodo;
    }
    cola->size++;
}

//Desencolar o quitar de la cola
struct Vehicle* dequeue(struct Queue* cola){
    if(cola->first){
        struct Node* nodo = cola->first;
        cola->first = cola->first->next;
        cola->size--;
        return nodo->car;
    }
    return NULL;
}

//Imprime la cola
void show_queue(struct Queue* cola){
    struct Node* aux = cola->first;
    printf("[ ");
    while(aux){
        printf("%d(%c)", aux->car->plate, (aux->car->priority)?'+':'-');
        if((aux = aux->next)) printf(", ");
    }
    printf(" ] - > size: %d\n", cola->size);
}

struct Sector* initialize_sector(int side){
    struct Sector* sector = malloc(sizeof(struct Sector));
    sector->ambulance_probability = -1;
    sector->average_cars = -1;
    sector->ready = initialize_queue();
    sector->finish = initialize_queue();
    sector->max_velocity_cars = -1;
    sector->min_velocity_cars = -1;
    sector->side = side;
    return sector;
}