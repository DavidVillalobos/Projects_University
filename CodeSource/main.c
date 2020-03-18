#include <stdio.h> // for printf and scanf
#include <pthread.h> // for threads
#include <math.h> // for log
#include <unistd.h>// for sleep
#include <stdlib.h> // for srand and malloc
#include<string.h>

//  Variables de Configuracion
int LENGHT = 5; //Largo del puente
int MODALITY = 0; //Modalidad
//Media de la formula de al distribucion exponencial
// del tiempo de llegada de los vehiculos en cada sentido
int ARRIVAL_AVERAGE_OF_EAST_CARS = 0;
int ARRIVAL_AVERAGE_OF_WEST_CARS = 0;
// Minimo y maximo de velocidad de los carros en cada sentido
int MIN_VELOCITY_EAST_CARS = 0;
int MAX_VELOCITY_EAST_CARS = 0;
int MIN_VELOCITY_WEST_CARS = 0;
int MAX_VELOCITY_WEST_CARS = 0;
//Tiempo de la luz verde en cada sentido
int EAST_TRAFFIC_LIGHT_TIME = 0;
int WEST_TRAFFIC_LIGHT_TIME = 0;
//Numero K de carros que pasan en cada sentido
int NUMBER_CARS_PASS_WEST = 0;
int NUMBER_CARS_PASS_EAST = 0;

//Variables compartidas
//vectores de campos del puente
int *bridgeBlocks;
//Seguros para evitar que varios carros 
//utilicen el mismo espacio del puente
pthread_mutex_t *bridgeLocks;

//Direccion de al via
int direction = 0;
//Bandera para que el usuario apague la simulacion cuando quiera
int flag = 1;
//Numero de autos (Placas)
int NUMAUTO = 1;
//Semaforo de cada sentido  1 verde, 0 rojo
int eastTrafficLight = 0;
int westTrafficLight = 0;

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

//Cola en ambos sentidos
struct cola* west;
struct cola* east;
//Cola de Carros que fueron procesados
struct cola* finish;

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
    if(direction){
        for (int i = 0; i < LENGHT; i++){
            if(bridgeBlocks[i] != -1){
                printf("\t|%d|\n",bridgeBlocks[i]);
            }else{
                printf("\t| |\n");
            }
        }
    }else{
        for (int i = LENGHT-1; 0 <= i; i--){
            if(bridgeBlocks[i] != -1){
                printf("\t|%d|\n",bridgeBlocks[i]);
            }else{
                printf("\t| |\n");
            }
        }
    }
}

//Imprime la cola
void printCola(struct cola* cola){
    struct nodo* aux = cola->first;
    printf("[ ");
    while(aux){
        printf("%d, ", aux->car->num);
        aux = aux->next;
    }
    printf(" ]");
    printf("\n");
}

void printSimulacion(){
    system("clear");
    printf("Via: Este ");
    (direction)?printf("-->"):printf("<--");
    printf(" Oeste");
    printf("\n");
    if(MODALITY == 2){ printf("Semaforo Este "); (eastTrafficLight)?printf("Verde\n"):printf("Rojo\n"); }
    printf("Este -> ");
    printCola(east);
    printBridge();
    printf("Oeste ->");
    printCola(west);
    if(MODALITY == 2){ printf("Semaforo Oeste "); (westTrafficLight)?printf("Verde\n"):printf("Rojo\n"); }
    printf("\nCruzaron al otro lado: ");
    printCola(finish);
}

//Cruzar el puente
void* cross_bridge(void* arg){
    struct car *car = (struct car*) arg;
    pthread_mutex_lock(&bridgeLocks[0]);
    for (int i = 0; i < LENGHT; i++){
        bridgeBlocks[i] = car->num;
        sleep(car->speed);
        if(i+1<LENGHT){
            pthread_mutex_lock(&bridgeLocks[i+1]);
        }
        bridgeBlocks[i] = -1;
        pthread_mutex_unlock(&bridgeLocks[i]);
    }
    //Agregamos el carro a la lista de procesos terminados
    enqueue(finish, car);
    pthread_exit(0);
}

//Creador de Vehiculos
void* createCar(){
    while(flag){
        //Esperar segun distribucion exponencial
        double  a = - ARRIVAL_AVERAGE_OF_EAST_CARS * log( 1 - (double) (rand()%1000)/1000);
        //printf("\n Sleep %f", a);
        sleep(a);
        //Crear carro y definimos los atributos
        struct car* car = malloc(0);
        pthread_attr_init(&car->attr);
        car->speed = MIN_VELOCITY_EAST_CARS + rand() % (MAX_VELOCITY_EAST_CARS + 1 - MIN_VELOCITY_EAST_CARS);
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
    for (int i = 0; i < LENGHT; i++){
        if(bridgeBlocks[i] != -1){
            return 0;
        }
    }
    return 1;
}

//Elige un carro de las colas
struct car* chooseCar(){
    struct car* aux = NULL;
    if(bridgeBlocks[0] == -1){
        struct cola* ceder = NULL;
        struct cola* pasar = NULL;
        switch(MODALITY){
            case 1: {
                if(direction){ pasar = east; ceder = west;}
                else{ pasar = west; ceder = east;}
                if(pasar->first){
                    aux = dequeue(pasar);
                }else if(ceder->first && emptyBridge()){
                    //Como el puente va a cambiar de direccion solo 
                    //puede hacerlo SI Y SOLO SI el puente esta vacio
                    direction = !direction;
                    aux = dequeue(ceder);    
                }
                break;
            }
            case 2:{
                int currentTrafficLight, otherTrafficLight;
                if(direction){ 
                    pasar = east; ceder = west; 
                    currentTrafficLight = eastTrafficLight;
                    otherTrafficLight = westTrafficLight;
                }else{ 
                    pasar = west; ceder = east;
                    currentTrafficLight = westTrafficLight;
                    otherTrafficLight = eastTrafficLight;
                }
                if(pasar->first && currentTrafficLight){ aux = dequeue(pasar); }
                else if(ceder->first && otherTrafficLight && emptyBridge()){
                    //Como el puente va a cambiar de direccion solo 
                    //puede hacerlo SI Y SOLO SI el puente esta vacio
                    direction = !direction;
                    aux = dequeue(ceder);    
                }
                break;
            }
            default: break;
        }
    }
    return aux;
}

void* coordinateTrafficLights(){
    while(flag){
        eastTrafficLight = 1;
        westTrafficLight = 0;
        sleep(EAST_TRAFFIC_LIGHT_TIME);
        eastTrafficLight = 0;
        westTrafficLight = 1;
        sleep(WEST_TRAFFIC_LIGHT_TIME);
    }
    pthread_exit(0);
}

//Se encarga de escuchar las peticiones del usuario
void* userListener(){
    while(flag){
        char c;
        scanf(" %c ",&c);
        if(c == '*'){
            flag = 0;
        }
    }
    pthread_exit(0);
} 

//        INICIANDO SIMULACION
//         [/////////     ]
void startSimulation(){
    while(flag){
        //Se elige un automovil
        struct car* car = chooseCar();
        if(car){//LLego algun automovil
            pthread_create(&(car->tid), &(car->attr), cross_bridge, car);
            //pthread_join(car->tid, NULL);
        }
        sleep(0.001);
        printSimulacion();
    }
}

char* slide(char *str, char begin, char finish){
    int tam =  strlen(str) - 1;
    int indexBegin = 0;
    if(begin != 0){
        while(str[indexBegin] != begin && indexBegin-1 < tam)
            indexBegin++;
        indexBegin++;
    }
    int indexFinish = tam;
    if(finish != 0){
        indexFinish = indexBegin;
        while(str[indexFinish] != finish && indexFinish-1 < tam)
            indexFinish++;
    }
    char *substr = malloc(0);
    int i = indexBegin;
    for(; i < indexFinish && i < strlen(str); i++)
        substr[i-indexBegin] = str[i];
    substr[i] = '\0';
    return substr;
}

void saveVariableSetting(char* section, char* name, int num){
     if(section != NULL){
         if(strcmp(section, "modality") == 0){
            if(strcmp(name, "id") == 0){
                MODALITY = num;
            }
         }else if(strcmp(section, "bridge") == 0){
            if(strcmp(name, "length") == 0){
                LENGHT = num;
                bridgeBlocks =  (int*) malloc(LENGHT * sizeof(int));
                bridgeLocks =  (pthread_mutex_t*) malloc(LENGHT * sizeof(pthread_mutex_t));
            }
         }else if(strcmp(section, "sector:east") == 0){
            if(strcmp(section, "arrive-exp-time-cars") == 0){
                ARRIVAL_AVERAGE_OF_EAST_CARS = num;
            }else if(strcmp(section, "number-cars-pass") == 0){
                NUMBER_CARS_PASS_EAST = num;
            }else if(strcmp(section, "traffic-light-time") == 0){
                EAST_TRAFFIC_LIGHT_TIME = num;
            }else if(strcmp(section, "speed-cars-upper") == 0){
                MAX_VELOCITY_EAST_CARS = num;
            }else if(strcmp(section, "speed-cars-lower") == 0){
                MIN_VELOCITY_EAST_CARS = num;
            }
         }else if(strcmp(section, "sector:west") == 0){
            if(strcmp(section, "arrive-exp-time-cars") == 0){
                ARRIVAL_AVERAGE_OF_WEST_CARS = num;
            }else if(strcmp(section, "number-cars-pass") == 0){
                NUMBER_CARS_PASS_WEST = num;
            }else if(strcmp(section, "traffic-light-time") == 0){
                WEST_TRAFFIC_LIGHT_TIME = num;
            }else if(strcmp(section, "speed-cars-upper") == 0){
                MAX_VELOCITY_WEST_CARS = num;
            }else if(strcmp(section, "speed-cars-lower") == 0){
                MIN_VELOCITY_WEST_CARS = num;
            }
         }
     }
}

void getConfigurations(char* path) {
    FILE *fichero_config = fopen (path, "r");
    char line[100];
    char* section = NULL;
    while(fgets(line, 100, fichero_config) != NULL){
        if(line[0] == 13){ section = NULL; }
        else if(line[0] == 91)
            section = slide(line, 91, 93);
        else{
            char* name = slide(line, 0, 32);
            char* value = slide(line, 92, 32);
            int num = atoi(value) - ((value[strlen(value)-1] == 104)? 30 : 48);
            //char* comment = slide(line,35,13);
            saveVariableSetting(section, name, num);
        }
        
    }
    fclose (fichero_config);
}


int main(){
    //Inicializamos las configuraciones
    getConfigurations("config.ini");
    //Colocamos una semilla aleatoria
    srand(time(NULL));
    //Creamos las colas de ambos sectores
    west = malloc(sizeof(struct cola));
    east = malloc(sizeof(struct cola));
    finish = malloc(sizeof(struct cola));
    west->last = west->first = east->last = east->first = finish->last = finish->first = NULL;
    //Inicializamos los bloqueos del puente
    for(int i = 0; i < LENGHT; i++){
        pthread_mutex_init(&bridgeLocks[i], NULL);
        bridgeBlocks[i] = -1;
    }
    //Creamos el hilo que crea automoviles
    pthread_t tid2;
    pthread_attr_t attr2;
    pthread_attr_init(&attr2);
    pthread_create(&tid2, &attr2, createCar, NULL);
    //Creamos un hilo para que coordina los semaforos
    pthread_t tid3;
    pthread_attr_t attr3;
    pthread_attr_init(&attr3);
    pthread_create(&tid3, &attr3, coordinateTrafficLights, NULL);    
    //Creamos un hilo que escucha las peticiones del usuario
    pthread_t tid4;
    pthread_attr_t attr4;
    pthread_attr_init(&attr4);
    pthread_create(&tid4, &attr4, userListener, NULL);   

    startSimulation();
    //Finalizamos los hilos
    for(int i = 0; i < LENGHT; i++){
        pthread_mutex_destroy(&bridgeLocks[i]);
    }
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    while(east->first){
        struct car* car = dequeue(east);
        pthread_join(car->tid, NULL);
        free(car);
    }
    while(west->first){
        struct car* car = dequeue(west);
        pthread_join(car->tid, NULL);
        free(car);
    }
    while(finish->first){
        struct car* car = dequeue(finish);
        pthread_join(car->tid, NULL);
        free(car);
    }
}