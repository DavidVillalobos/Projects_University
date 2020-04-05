#include"Queue.h"

//Inicializar una cola
struct Queue* initialize_queue(){
    struct Queue* cola = malloc(sizeof(struct Queue));
    cola->first = NULL;
    cola->last = NULL;
    return cola;
}

//Encolar o Poner en cola
void enqueue(struct Queue* cola, struct Vehicle* car) {
    struct Node* nodo = malloc(sizeof(struct Node));
    nodo->car = car;
    nodo->next = NULL;
    if(car->priority){
        if(cola->first){
            nodo->next = cola->first;
        }else{
            cola->last = nodo;
        }
    }else{
        if(cola->first){
            if(cola->first->next){
                cola->last->next = nodo;
            }else{
                cola->first->next = nodo; 
            }
            cola->last = nodo;
        }
    }
    cola->first = nodo;
}

//Desencolar o quitar de la cola
struct Vehicle* dequeue(struct Queue* cola){
    if(cola->first){
        struct Node* nodo = cola->first;
        cola->first = cola->first->next;
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
        aux = aux->next;
        if(aux){
            printf(", ");
        }
    }
    printf(" ]");
    printf("\n");
}