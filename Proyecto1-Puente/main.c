#include <stdio.h> // for printf and scanf
#include <pthread.h> // for threads
#include <math.h> // for log
#include <unistd.h>// for sleep
#include <stdlib.h> // for srand and malloc

#define lenght 10 //Largo del puente
#define media 1 //Media de la formula de al distribucion exponencial
// del tiempo de llegada de los vehiculos
#define modality 1
// Minimo y maximo de velocidad de los carros
#define MIN_VELOCITY 5
#define MAX_VELOCITY 6

//Variables compartidas
//vectores de campos del puente
int vecCampos[lenght];
//Seguros para evitar que varios carros utilicen el mismo campo del puente
pthread_mutex_t locks[lenght];

//Direccion de al via
int direction = 0;
//Bandera para que el usuario apague la simulacion cuando quiera
int flag = 1;
//Numero de autos (Placas)
int NUMAUTO = 1;

//           ENTIDADES DE LA SIMULACION

//Carros, {Velocidad, Direccion, Placa, Prioridad}
struct car{
    int speed, direction, num, priority;
    pthread_t tid;
    pthread_attr_t attr;
};

//Nodo de Cola, {Carro, Siguiente}
struct nodo{
    struct car* car;
    struct nodo* next;
};

//Cola, {Primero, Ultimo}
struct cola{
    struct nodo* first;
    struct nodo* last;
};

//Encolar o Poner en cola
void enqueue(struct cola* cola, struct car* car) {
    struct nodo* newnodo = malloc(sizeof(struct car));
    newnodo->car = car;
    newnodo->next = NULL;
    //if(car->priority){
    //    if(cola->first){
    //        newnodo->next = cola->first;
    //        cola->first = newnodo; 
    //    }else{
    //        cola->first = newnodo;
    //    }
    //}else{
    if(cola->first){
        if(cola->first->next){
            cola->last->next = newnodo;
        }else{
            cola->first->next = newnodo; 
        }
        cola->last = newnodo;
    }else{
        cola->first = newnodo;
    }
    //}
}

//Desencolar o quitar de la cola
struct car* dequeue(struct cola* cola){
    if(cola->first){
        struct nodo* nodo = cola->first;
        cola->first = cola->first->next;
        return nodo->car;
    }
    return NULL;
}

void insertFirst(struct cola* cola, struct car* car){
    struct nodo* newnodo = malloc(sizeof(struct car));
    newnodo->car = car;
    newnodo->next = cola->first;
    cola->first = newnodo;
}

//Imprimir el puente
void printBridge(){
    for (int i = 0; i < lenght; i++){
        if(vecCampos[i] != -1){
            printf("\t|%d|\n",vecCampos[i]);
        }else{
            printf("\t| |\n");
        }
    }
}

//Cola en ambos sentidos
struct cola* west;
struct cola* east;
//Cola de Carros que fueron procesados
struct cola* finish;

//Imprime la cola
void printCola(struct cola* cola){
    struct nodo* aux = cola->first;
    printf("[");
    while(aux){
        printf("{%d}", aux->car->num);
        aux = aux->next;
    }
    printf("]");
    printf("\n");
}

void printSimulacion(){
    system("clear");
    printf("Via: Este ");
    (direction)?printf("-->"):printf("<--");
    printf(" Oeste");
    printf("\n");
    printf("Este -> ");
    printCola(east);
    printBridge();
    printf("Oeste -> ");
    printCola(west);
    printf("Cruzaron al otro lado: ");
    printCola(finish);
}

//Cruzar el puente
void* cross_bridge(void* arg){
    struct car *car = (struct car*) arg;
    pthread_mutex_lock(&locks[0]);
    for (int i = 0; i < lenght; i++){
        vecCampos[i] = car->num;
        printSimulacion();
        sleep(car->speed);
        if(i+1<lenght){
            pthread_mutex_lock(&locks[i+1]);
        }
        vecCampos[i] = -1;
        pthread_mutex_unlock(&locks[i]);
    }
    //Agregamos el carro a la lista de procesos terminados
    enqueue(finish, car);
    pthread_exit(0);
}

//Creador de Vehiculos
void* createCar(){
    while(flag){
        //Esperar segun distribucion exponencial
        double  a = - media * log((double) (rand()%1000)/1000);
        //printf("\n Sleep %f", a);
        sleep(a);
        //Crear carro y definimos los atributos
        struct car* car = malloc(sizeof(struct car));
        pthread_attr_init(&car->attr);
        car->speed = MIN_VELOCITY + rand() % (MAX_VELOCITY + 1 - MIN_VELOCITY);
        car->num = NUMAUTO; 
        NUMAUTO++;
        //Asignamos una proporcion de 4/10 para las ambulancias(Prioridad)
        if(6 < rand() % 11){ car->priority = 1;}
        else{ car->priority = 0;}
        //Asignamos una direccion con proporcion 1/2
        car->direction = rand() & 1;
        //Encolamos el vehiculo (Simula que llega de algun sector) 
        if(car->direction){
            enqueue(east, car);
        }else{
            enqueue(west, car);
        }
        //Mensaje para el Usuario
        //printf("LLego un automovil proveniente del sector");
        //if(car->direction){ printf(" este");}else{printf(" oeste");}
        //printf(" con matricula: %d\n", car->num);
    }
    pthread_exit(0);
}

int emptyBridge(){
    for (int i = 0; i < lenght; i++){
        if(vecCampos[i] != -1){
            return 0;
        }
    }
    return 1;
}

//Elige un carro de las colas
struct car* chooseCar(){
    struct car* aux = NULL;
    struct cola* ceder = NULL;
    struct cola* pasar = NULL;
    switch(modality){
        case 1: {
            if(direction){ pasar = east; ceder = west;}
            else{ pasar = west; ceder = east;}
            if(pasar->first){
                if(vecCampos[0] == -1){
                    aux = dequeue(pasar);
                }
            }else if(ceder->first && emptyBridge()){
                //Como el puente va a cambiar de direccion solo 
                //puede hacerlo SI Y SOLO SI el puente esta vacio
                direction = !direction;
                aux = dequeue(ceder);    
            }
            break;
        }
        default: break;
    }
    return aux;
}

//Se encarga de escuchar las peticiones del usuario
void* listenerUser(){
    while(flag){
        char input;
        scanf(" %c ",&input);
        if(input == '*'){//Por el momento solo de salida
            flag = 0;
        }
        //if(finish->first){
        //    struct car* car = dequeue(finish);
        //    pthread_join(car->tid, NULL);
        //    free(car);
        //}
    }
    pthread_exit(0);
}

int main(){
    //Colocamos una semilla aleatoria
    srand(time(NULL));
    //Creamos las colas de ambos sectores
    west = malloc(sizeof(struct cola));
    east = malloc(sizeof(struct cola));
    finish = malloc(sizeof(struct cola));
    west->last = west->first = east->last = east->first = finish->last = finish->first = NULL;
    //Inicializamos los bloqueos del puente
    for(int i = 0; i < lenght; i++){
        pthread_mutex_init(&locks[i], NULL);
        vecCampos[i] = -1;
    }
    //Creamos el hilo que crea automoviles
    pthread_t tid2;
    pthread_attr_t attr2;
    pthread_attr_init(&attr2);
    pthread_create(&tid2, &attr2, createCar, NULL);
    //Creamos un hilo para que responda al usuario
    //pthread_t tid3;
    //pthread_attr_t attr3;
    //pthread_attr_init(&attr3);
    //pthread_create(&tid3, &attr3, listenerUser, NULL);
    
    //        INICIANDO SIMULACION
    //         [/////////     ]
    
    while(flag){
        //Se elige un automovil
        struct car* car = chooseCar();
        if(car){//LLego algun automovil
            pthread_create(&(car->tid), &(car->attr), cross_bridge, car);
            //pthread_join(car->tid, NULL);
        }
        //sleep(2);
    }
    //Finalizamos los hilos
    for(int i = 0; i < lenght; i++){
        pthread_mutex_destroy(&locks[i]);
    }
    pthread_join(tid2, NULL);
    //pthread_join(tid3, NULL);
    while(east->first){
        struct car* car = dequeue(east);
        pthread_join(car->tid, NULL);
    }
    while(west->first){
        struct car* car = dequeue(west);
        pthread_join(car->tid, NULL);
    }
    while(finish->first){
        struct car* car = dequeue(finish);
        pthread_join(car->tid, NULL);
    }
}