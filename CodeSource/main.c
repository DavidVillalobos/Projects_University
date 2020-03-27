#include <stdio.h> // for printf and scanf
#include <pthread.h> // for threads
#include <math.h> // for log
#include <unistd.h>// for sleep
#include <stdlib.h> // for srand and malloc
#include<string.h> // for strlen

//  Variables de Configuracion/compartidas

//vectores de campos del puente
int *bridge;
//Seguros para evitar que varios carros 
//utilicen el mismo espacio del puente
pthread_mutex_t *semaphores;
//Seguro para evitar que los semaforos o oficiales
//utilicen la misma via
pthread_mutex_t way_bridge;
int way = 1;//Direccion de la via
int simulation = 1; //simulacion encendida o apagada
int num_cars = 1;//Numero de autos ('Placas')
int lenght = 5; //Largo del puente
int modality = 0; //Modalidad

//           ENTIDADES DE LA SIMULACION

//Sector, cada lado de la simulacion
struct sector_t{
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
    struct officer_t* transit_officer;
    //Cola en espera por cruzar el puente
    struct queue_t* ready;
    //Cola despues de cruzar
    struct queue_t* finish;//(aqui llegan los que venian del otro sector)
    //Semaforo del sector
    struct semaphore_t* semaphore;
};

struct sector_t* east;
struct sector_t* west;

//Carros, {Velocidad, Direccion, Placa, Prioridad}
struct car_t{
    int speed, direction, num, priority;
    pthread_t tid;
};

//Semaforo, {Color de luz, tiempo}
struct semaphore_t{
    int light, time_in_green, time;
    pthread_t tid;
};

//Oficial de Transito, {k, ki}
struct officer_t{
    //Numero K de carros que pasan en cada sentido
    int number_cars_pass, number;
    pthread_t tid;
};

//Cola, {Primero, Ultimo}
struct queue_t{
    struct node_t* first;
    struct node_t* last;
};

//Nodo de Cola, {Carro, Siguiente}
struct node_t{
    struct car_t* car;
    struct node_t* next;
};

//Encolar o Poner en cola
void enqueue(struct queue_t* cola, struct car_t* car) {
    struct node_t* newnodo = malloc(sizeof(struct node_t));
    newnodo->car = car;
    newnodo->next = NULL;
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
}

//Encolar con prioridad, (de primero)
void enqueue_priority(struct  queue_t* cola, struct car_t* car){
    struct node_t* newnodo = malloc(sizeof(struct node_t));
    newnodo->car = car;
    newnodo->next = NULL;
    if(cola->first){
        newnodo->next = cola->first;
    }
    cola->first = newnodo;
};


//Desencolar o quitar de la cola
struct car_t* dequeue(struct queue_t* cola){
    if(cola->first){
        struct node_t* nodo = cola->first;
        cola->first = cola->first->next;
        return nodo->car;
    }
    return NULL;
}

//Imprimir el puente
void printBridge(){
    if(way){
        for (int i = 0; i < lenght; i++){
            if(bridge[i] != -1){
                printf("\t|%d|\n",bridge[i]);
            }else{
                printf("\t| |\n");
            }
        }
    }else{
        for (int i = lenght-1; 0 <= i; i--){
            if(bridge[i] != -1){
                printf("\t|%d|\n",bridge[i]);
            }else{
                printf("\t| |\n");
            }
        }
    }
}

//Imprime la cola
void printCola(struct queue_t* cola){
    struct node_t* aux = cola->first;
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

void printSimulacion(){
    system("clear");
    printf("\nVia: Este ");
    (way)?printf("-->"):printf("<--");
    printf(" Oeste\n");
    printf("\nCruzaron al Este: ");
    printCola(east->finish);
    if(modality == 2){ 
        printf("\nSemaforo Este "); 
        if(east->semaphore->light == -1)
            printf("Amarillo");
        else if(east->semaphore->light)
            printf("Verde (%d)",east->semaphore->time);
        else
            printf("Rojo"); 
    }
    if(modality == 3){
        printf("\nOficial Este k(%d)",east->transit_officer->number); 
    }
    printf("\nEste -> ");
    printCola(east->ready);
    printBridge();
    printf("Oeste ->");
    printCola(west->ready);
    if(modality == 2){ 
        printf("\nSemaforo Oeste "); 
        if(west->semaphore->light == -1)
            printf("Amarillo");
        else if(west->semaphore->light)
            printf("Verde (%d)",west->semaphore->time);
        else
            printf("Rojo"); 
    }
    if(modality == 3){
        printf("\nOficial Oeste k(%d)",west->transit_officer->number); 
    }
    printf("\nCruzaron al Oeste: ");
    printCola(west->finish);
}

//Cruzar el puente
void* cross_bridge(void* arg){
    struct car_t *car = (struct car_t*) arg;
    bridge[0] = car->num;
    for (int i = 0; i < lenght; i++){
        sleep(car->speed);//Utilizando el puente
        if(i+1<lenght){//Si me falta camino, pido el de adelante
            pthread_mutex_lock(&semaphores[i+1]);//P(Puente[i + 1])
            bridge[i+1] = car->num;
        }
        bridge[i] = -1;
        pthread_mutex_unlock(&semaphores[i]);//V(Puente[i]) libero el que estoy
    }
    //Agregamos el carro a la lista de procesos terminados segun el lado
    enqueue((car->direction)?west->finish:east->finish, car);
    pthread_exit(0);
}


void* activatecarMaker(void* arg){
    struct sector_t* sector = (struct sector_t*) arg;
    while(simulation){// - media * log(e)[1 - (0 < rand() < 1)]
        float  a = -sector->average_cars * log( 1 - (double) (rand()%1000)/1000);
        sleep(a);//Esperar
        //Crear carro y definimos los atributos
        struct car_t* car = malloc(sizeof(struct car_t));
        car->direction = sector->side;
        car->num = num_cars++;
        car->speed = sector->min_velocity_cars + rand() % (sector->max_velocity_cars + 1 - sector->min_velocity_cars);
        car->priority = (10 - sector->ambulance_probability <= rand() % 11)? 1: 0;
        (car->priority)? enqueue_priority(sector->ready, car) : enqueue(sector->ready, car);        
    }
    pthread_exit(0);
}

//Creador de Vehiculos  in the exponential distribution

int emptyBridge(){
    for (int j = 0; j < 50; j++){
        for (int i = 0; i < lenght; i++){
            if(bridge[i] != -1){
                return 0;
            }
        }
    }
    return 1;
}

void* fifo(void* arg){
    struct sector_t* ceder; // cede paso al otro lado
    struct sector_t* pasar; // tiene la via
    struct car_t* car = NULL;
    while (simulation){
        if(way){ pasar = east; ceder = west;}
        else{ pasar = west; ceder = east;}
        if(pasar->ready->first){
            //P(Puente[0]) pido el primer espacio
            pthread_mutex_lock(&semaphores[0]);
            car = dequeue(pasar->ready);
            pthread_create(&(car->tid), NULL, cross_bridge, car);
            car = NULL;
        }else if(ceder->ready->first && emptyBridge()){
            //Como el puente va a cambiar de direccion solo 
            //puede hacerlo SI Y SOLO SI el puente esta vacio
            //P(Puente[0]) pido el primer espacio
            pthread_mutex_lock(&semaphores[0]);
            car = dequeue(ceder->ready);
            way = ceder->side;
            pthread_create(&(car->tid), NULL, cross_bridge, car);
            car = NULL;
        }
    }
    pthread_exit(0);
}

void* timer(void* arg){
    struct semaphore_t* semaphore  = (struct semaphore_t*) arg;
    for (int i = semaphore->time_in_green; 0 < i; i--){
        semaphore->time = i;
        sleep(1);
    }
    semaphore->light = 0;
    pthread_exit(0);
}

void* activateSemaphore(void* arg){
    struct sector_t* sector = (struct sector_t*) arg; 
    pthread_t time;
    struct car_t* car = NULL;
    while(simulation){
        pthread_mutex_lock(&way_bridge); // Bloquea sentido del camino
        sleep(1);
        sector->semaphore->light = 1;
        pthread_create(&time, NULL, timer, sector->semaphore); //Inicia el temporizador del semaforo
        while(!emptyBridge());
        way = sector->side;
        while(sector->semaphore->light){ 
            if(sector->ready->first &&  pthread_mutex_trylock(&semaphores[0]) == 0){
                //P(Puente[0]) pido el primer espacio
                car = dequeue(sector->ready);
                pthread_create(&(car->tid), NULL, cross_bridge, car);
            }
        }
        pthread_mutex_unlock(&way_bridge); // Desbloquea el sentido del camino
        sector->semaphore->light = -1;//Luz en amarillo
        sleep(1);//tiempo de luz amarilla
        sector->semaphore->light = 0;// Luz roja
    }
    pthread_exit(0);
}

void* semaphore(){
    pthread_create(&east->semaphore->tid, NULL, activateSemaphore, east);
    sleep(1);
    pthread_create(&west->semaphore->tid, NULL, activateSemaphore, west);
    pthread_join(east->semaphore->tid, NULL);
    pthread_join(west->semaphore->tid, NULL);
    pthread_exit(0);
}

void* establishOfficer(void* arg){
    struct sector_t* sector = (struct sector_t*) arg; 
    struct car_t* car = NULL;
    while(simulation){
        if(emptyBridge()){
            pthread_mutex_lock(&way_bridge); // Bloquea sentido del camino
            way = sector->side;
            for (int i = 0; i < sector->transit_officer->number_cars_pass && sector->ready->first; i++){
                pthread_mutex_lock(&semaphores[0]);
                sector->transit_officer->number = sector->transit_officer->number_cars_pass - i;
                car = dequeue(sector->ready);
                pthread_create(&car->tid, NULL, cross_bridge, car);
            }
            sector->transit_officer->number = 0;
            pthread_mutex_unlock(&way_bridge); // Desbloquea el sentido del camino
            sleep(1);
        }
    }
    pthread_exit(0);
}

void* officerTransit(){
    pthread_create(&east->transit_officer->tid, NULL, establishOfficer, east);
    pthread_create(&west->transit_officer->tid, NULL, establishOfficer, west);
    pthread_join(east->transit_officer->tid, NULL);
    pthread_join(west->transit_officer->tid, NULL);
    pthread_exit(0);
}

//Se encarga de escuchar las peticiones del usuario
void* userListener(){
    while(simulation){
        char c;
        scanf(" %c ",&c);
        if(c == '*'){
            simulation = 0;
        }
    }
    pthread_exit(0);
}

void playSimulation(){
    //Creamos un hilo que escucha peticiones al usuario
    pthread_t user;
    pthread_create(&user, NULL, userListener, NULL);
    //Creamos un hilo que administra la modalidad
    pthread_t mod;
    switch (modality){
        case 1: { 
            pthread_create(&mod, NULL, fifo, NULL);
            break; 
        }
        case 2: {
            pthread_create(&mod, NULL, semaphore, NULL);
            break;
        }
        case 3:{
            pthread_create(&mod, NULL, officerTransit, NULL);
            break;
        }
        default: break;
    }
    //Creamos los hilos que crean automoviles
    pthread_t cars_east;
    pthread_create(&cars_east, NULL, activatecarMaker, east);
    pthread_t cars_west;
    pthread_create(&cars_west, NULL, activatecarMaker, west);
    //Veamos la simulacion
    while(simulation) printSimulacion();
    //Esperamos que los hilos terminen
    pthread_join(user, NULL);
    pthread_join(mod, NULL);
    pthread_join(cars_east, NULL);
    pthread_join(cars_west, NULL);
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

int compare(char* string_a, char* string_b){
    int tam_a = strlen(string_a);
    int tam_b = strlen(string_b);
    if(tam_a != tam_b) return 0;
    for (int i = 0; i < tam_a; i++){
        if(string_a[i] != string_b[i]){
            return 0;
        }
    }
    return 1;
}

void saveVariableSetting(char* section, char* name, int num, char* comment){
    //printf("In %s, varible %s, is load with %d, comments: %s\n",section, name, num, comment);
    if(compare(section, "modality") && compare(name, "id")){
        modality = num;
    }else if(compare(section, "bridge")){
        if(compare(name, "length")){
            lenght = num;
            bridge = (int*) malloc (lenght * sizeof(int));
            semaphores = (pthread_mutex_t*) malloc (lenght * sizeof(pthread_mutex_t));
        }
    }else if(compare(section, "sector:east")){
        if(compare(name, "arrive-exp-time-cars")){
            east->average_cars = num;
        }else if(compare(name, "number-cars-pass")){
            east->transit_officer->number_cars_pass = num;
        }else if(compare(name, "traffic-light-time")){
            east->semaphore->time_in_green = num;
        }else if(compare(name, "speed-cars-upper")){
            east->max_velocity_cars = num;
        }else if(compare(name, "speed-cars-lower")){
            east->min_velocity_cars = num;
        }else if(compare(name, "ambulance-probability")){
            east->ambulance_probability = num;
        }
    }else if(compare(section, "sector:west")){
        if(compare(name, "arrive-exp-time-cars")){
            west->average_cars = num;
        }else if(compare(name, "number-cars-pass")){
            west->transit_officer->number_cars_pass = num;
        }else if(compare(name, "traffic-light-time")){
            west->semaphore->time_in_green = num;
        }else if(compare(name, "speed-cars-upper")){
            west->max_velocity_cars = num;
        }else if(compare(name, "speed-cars-lower")){
            west->min_velocity_cars = num;
        }else if(compare(name, "ambulance-probability")){
            west->ambulance_probability = num;
        }
    }
}

int initConfigurations(char* path) {
    FILE *config = fopen (path, "r");
    if(!config){ return 0;}
    char line[100];
    char* section = NULL;
    char* name = NULL;
    char* value = NULL;
    char* comment = NULL;
    int num = 0;
    east = malloc(sizeof(struct sector_t));
    west = malloc(sizeof(struct sector_t));
    east->semaphore = malloc(sizeof(struct semaphore_t));
    east->semaphore->light = 0; //Luz roja
    east->side = 1; 
    west->semaphore = malloc(sizeof(struct semaphore_t));
    west->semaphore->light = 0; //Luz roja
    west->side = 0; 
    east->transit_officer = malloc(sizeof(struct officer_t));
    west->transit_officer = malloc(sizeof(struct officer_t));
    while(fgets(line, 100, config) != NULL){
        if(line[0] == 91){
            section = slide(line, 91, 93);
            //comment = slide(line,35,13);
        }
        else if(line[0] == 13) section = NULL;
        else if(section != NULL){
            name = slide(line, 0, 32);
            value = slide(line, 92, 32);
            num = atoi(value) - ((value[strlen(value)-1] == 104)? 30 : 48);
            comment = slide(line,35,13);
            saveVariableSetting(section, name, num, comment);    
        }
    }
    fclose (config);//cerramos el fichero
    //Creamos las colas de ambos sectores
    east->ready = malloc(sizeof(struct queue_t));
    west->ready = malloc(sizeof(struct queue_t));
    //Creamos la cola de finish de ambos sectores
    east->finish = malloc(sizeof(struct queue_t));
    west->finish = malloc(sizeof(struct queue_t));
    //Inicializamos las colas
    east->ready->last = east->ready->first = west->ready->last = west->ready->first = NULL;
    east->finish->last = east->finish->first = west->finish->last = west->finish->first = NULL;
    //Colocamos una semilla aleatoria
    srand(time(NULL));
    //Inicializamos los bloqueos y espacios del puente
    for(int i = 0; i < lenght; i++){
        pthread_mutex_init(&semaphores[i], NULL);
        bridge[i] = -1;
    } 
    pthread_mutex_init(&way_bridge, NULL);
    return 1;
}

void stopSimulation(){
    system("clear");
    printf("\n\t\t FINALIZANDO SIMULACION . . .\n");
    //Finalizamos los hilos
    for(int i = 0; i < lenght; i++){
        pthread_mutex_destroy(&semaphores[i]);
    }
    pthread_mutex_destroy(&way_bridge);
    if(modality == 2){
        free(east->semaphore);
        free(west->semaphore);
    }
    while(east->ready->first){
        struct car_t* car = dequeue(east->ready);
        pthread_join(car->tid, NULL);
        free(car);
    }
    free(east->ready);
    while(west->ready->first){
        struct car_t* car = dequeue(west->ready);
        pthread_join(car->tid, NULL);
        free(car);
    }
    free(west->ready);
    while(east->finish->first){
        struct car_t* car = dequeue(east->finish);
        pthread_join(car->tid, NULL);
        free(car);
    }
    //free(finishEast); one problem in free . . . . 
    while(west->finish->first){
        struct car_t* car = dequeue(west->finish);
        pthread_join(car->tid, NULL);
        free(car);
    }
    //free(finishWest);

}

int main(int argc, char *argv[]){
    char* path = "config.ini";
    if(argc == 2) path = argv[1];
    //Inicializamos las configuraciones
    if(initConfigurations(path)){
        playSimulation();//Iniciamos Simulacion
        stopSimulation();//Detenemos Simulacion
    }else{
        printf("Ocurrio algun error al cargar las configuraciones\n");
    }
}