#include"Sector.h"

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

struct Queue* initialize_queue(){
    struct Queue* cola = malloc(sizeof(struct Queue));
    cola->first = cola->last = NULL;
    cola->size = cola->sizeAmbulances = 0;
    return cola;
}

void enqueue(struct Queue* cola, struct Vehicle* car) {
    struct Node* nodo = malloc(sizeof(struct Node));
    nodo->car = car;
    nodo->next = nodo->prev = NULL;
    if(cola->first){
        cola->last->next = nodo;
        nodo->prev = cola->last;
        cola->last = nodo;
    }else{
        cola->first = cola->last = nodo;
    }
    cola->size++;
    if(car->priority){
        cola->sizeAmbulances++;
    }
}

struct Vehicle* dequeue(struct Queue* cola){
    if(cola->first){
        struct Node* nodo = cola->first;
        cola->first = cola->first->next;
        cola->size--;
        if(nodo->car->priority){
            cola->sizeAmbulances--;
        }
        return nodo->car;
    }
    return NULL;
}

void show_queue(struct Queue* cola){
    struct Node* aux = cola->first;
    char buffer[1000];
    sprintf(buffer, "[ ");
    int i = 1;
    while(aux){
        if(i % 16 == 0) sprintf(buffer, "%s\n", buffer);
        sprintf(buffer, "%s %d(%s)", buffer, aux->car->plate, (aux->car->priority)?"+":"-");
        if((aux = aux->next)) sprintf(buffer, "%s, ", buffer);
        i++;
    }
    sprintf(buffer, "%s ] - > size: %d\n", buffer, cola->size);
    printf("%s", buffer);
}

struct Node* searchNode(struct Queue* cola, struct Vehicle* car){
    struct Node* aux = cola->first;
    while(aux){
        if(aux->car->plate == car->plate) return aux;
        aux = aux->next;
    }
    return NULL;
}

void check_priority(struct Queue* cola, struct Vehicle* car, int way_bridge){
    struct Node* nodo = searchNode(cola, car);
    if(nodo){
        while(nodo->prev && !nodo->prev->car->priority && car->direction == way_bridge){
            int speed, plate, priority;
            // Aux = A
            speed = nodo->car->speed;
            plate = nodo->car->plate;
            priority = nodo->car->priority;
            // A = B
            nodo->car->speed = nodo->prev->car->speed;
            nodo->car->plate = nodo->prev->car->plate;
            nodo->car->priority = nodo->prev->car->priority;
            // B = Aux
            nodo->prev->car->speed = speed;
            nodo->prev->car->plate = plate;
            nodo->prev->car->priority = priority;
            
            nodo = nodo->prev;
        }
    }
}

void enqueue_priority(struct Queue* cola, struct Vehicle* car){
    struct Node* nodo = malloc(sizeof(struct Node));
    nodo->car = car;
    nodo->next = nodo->prev = NULL;    
    if(cola->first){
        if(cola->first->car->priority){
            if(cola->first->next){
                struct Node* aux = cola->first;
                while(aux->next && aux->next->car->priority){
                    aux = aux->next;
                }
                if(aux->next){
                    nodo->next = aux->next;
                    nodo->next->prev = nodo;
                    aux->next = nodo;
                    nodo->prev = aux;
                }else{
                    cola->last->next = nodo;
                    nodo->prev = cola->last;
                    cola->last = nodo;
                }
            }else{
                cola->last->next = nodo;
                nodo->prev = cola->last;
                cola->last = nodo;
            }
        }else{
            cola->first->prev = nodo;
            nodo->next = cola->first; 
            cola->first = nodo;
        }
    }else{
        cola->first = cola->last = nodo;
    }
    cola->size++;
    cola->sizeAmbulances++;
}