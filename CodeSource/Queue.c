#include"Queue.h"

//Inicializar una cola
struct Queue* initialize_queue(){
    struct Queue* cola = malloc(sizeof(struct Queue));
    cola->first = NULL;
    cola->last = NULL;
    cola->size = 0;
    cola->cantAmbulances = 0;
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
    if(car->priority){
        cola->cantAmbulances++;
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
    cola->cantAmbulances++;
}

//Desencolar o quitar de la cola
struct Vehicle* dequeue(struct Queue* cola){
    if(cola->first){
        struct Node* nodo = cola->first;
        cola->first = cola->first->next;
        cola->size--;
        if(nodo->car->priority){
            cola->cantAmbulances--;
        }
        return nodo->car;
    }
    return NULL;
}

//Imprime la cola
void show_queue(struct Queue* cola){
    struct Node* aux = cola->first;
    printf("[ ");
    while(aux){
        printf("%d(%c)", aux->car->num, (aux->car->priority)?'+':'-');
        if((aux = aux->next)) printf(", ");
    }
    printf(" ] - > size: %d\n", cola->size);
}