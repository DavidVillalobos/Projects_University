#include"Simulation.h"

struct Simulation* initialize_simulation(){
    struct Simulation* simulation = malloc(sizeof(struct Simulation));
    simulation->west = initialize_sector(0);
    simulation->east = initialize_sector(1);
    simulation->lenght = 0;
    simulation->modality = 0;
    simulation->num_cars = 0;
    simulation->running = 0;
    simulation->way = 0;
    return simulation;
}

struct Simulation* simulation;

//Imprimir el puente
void printBridge(){
    if(simulation->way){
        for (int i = 0; i < simulation->lenght; i++){
            if(simulation->bridge[i] != -1){
                printf("\t|%d|\n",simulation->bridge[i]);
            }else{
                printf("\t| |\n");
            }
        }
    }else{
        for (int i = simulation->lenght-1; 0 <= i; i--){
            if(simulation->bridge[i] != -1){
                printf("\t|%d|\n",simulation->bridge[i]);
            }else{
                printf("\t| |\n");
            }
        }
    }
}

void printSimulacion(){
    system("clear");
    printf("\nVia: Este ");
    (simulation->way)?printf("-->"):printf("<--");
    printf(" Oeste\n");
    printf("\nCruzaron al Este: ");
    show_queue(simulation->east->finish);
    if(simulation->modality == 2){ 
        printf("\nSemaforo Este "); 
        if(simulation->east->semaforo->light == -1)
            printf("Amarillo");
        else if(simulation->east->semaforo->light)
            printf("Verde (%d)",simulation->east->semaforo->time);
        else
            printf("Rojo"); 
    }
    if(simulation->modality == 3){
        printf("\nOficial Este k(%d)",simulation->east->transit_officer->number); 
    }
    printf("\nEste -> ");
    show_queue(simulation->east->ready);
    printBridge();
    printf("Oeste ->");
    show_queue(simulation->west->ready);
    if(simulation->modality == 2){ 
        printf("\nSemaforo Oeste "); 
        if(simulation->west->semaforo->light == -1)
            printf("Amarillo");
        else if(simulation->west->semaforo->light)
            printf("Verde (%d)",simulation->west->semaforo->time);
        else
            printf("Rojo"); 
    }
    if(simulation->modality == 3){
        printf("\nOficial Oeste k(%d)",simulation->west->transit_officer->number); 
    }
    printf("\nCruzaron al Oeste: ");
    show_queue(simulation->west->finish);
}

//Cruzar el puente
void* cross_bridge(void* arg){
    struct Vehicle *car = (struct Vehicle*) arg;
    simulation->bridge[0] = car->num;
    for (int i = 0; i < simulation->lenght; i++){
        sleep(car->speed);//Utilizando el puente
        if(i+1<simulation->lenght){//Si me falta camino, pido el de adelante
            pthread_mutex_lock(&simulation->semaphores[i+1]);//P(Puente[i + 1])
            simulation->bridge[i+1] = car->num;
        }
        simulation->bridge[i] = -1;
        pthread_mutex_unlock(&simulation->semaphores[i]);//V(Puente[i]) libero el que estoy
    }
    //Agregamos el carro a la lista de procesos terminados segun el lado
    enqueue((car->direction)?simulation->west->finish:simulation->east->finish, car);
    pthread_exit(0);
}


void* activatecarMaker(void* arg){
    struct Sector* sector = (struct Sector*) arg;
    while(simulation){// - media * log(e)[1 - (0 < rand() < 1)]
        float  a = - sector->average_cars * log( 1 - (double) (rand()%1000)/1000);
        sleep(a);//Esperar
        //Crear carro y definimos los atributos
        struct Vehicle* car = malloc(sizeof(struct Vehicle));
        car->direction = sector->side;
        car->num = simulation->num_cars++;
        car->speed = sector->min_velocity_cars + rand() % (sector->max_velocity_cars + 1 - sector->min_velocity_cars);
        car->priority = (10 - sector->ambulance_probability <= rand() % 11)? 1: 0;
        enqueue(sector->ready, car);        
    }
    pthread_exit(0);
}

//Creador de Vehiculos  in the exponential distribution

int emptyBridge(){
    for (int j = 0; j < 50; j++){
        for (int i = 0; i < simulation->lenght; i++){
            if(simulation->bridge[i] != -1){
                return 0;
            }
        }
    }
    return 1;
}

void* fifo(void* arg){
    struct Sector* ceder; // cede paso al otro lado
    struct Sector* pasar; // tiene la via
    struct Vehicle* car = NULL;
    while (simulation){
        if(simulation->way){ pasar = simulation->east; ceder = simulation->west;}
        else{ pasar = simulation->west; ceder = simulation->east;}
        if(pasar->ready->first){
            //P(Puente[0]) pido el primer espacio
            pthread_mutex_lock(&simulation->semaphores[0]);
            car = dequeue(pasar->ready);
            pthread_create(&(car->tid), NULL, cross_bridge, car);
            car = NULL;
        }else if(ceder->ready->first && emptyBridge()){
            //Como el puente va a cambiar de direccion solo 
            //puede hacerlo SI Y SOLO SI el puente esta vacio
            //P(Puente[0]) pido el primer espacio
            pthread_mutex_lock(&simulation->semaphores[0]);
            car = dequeue(ceder->ready);
            simulation->way = ceder->side;
            pthread_create(&(car->tid), NULL, cross_bridge, car);
            car = NULL;
        }
    }
    pthread_exit(0);
}

void* timer(void* arg){
    struct Semaforo* semaforo  = (struct Semaforo*) arg;
    for (int i = semaforo->time_in_green; 0 < i; i--){
        semaforo->time = i;
        sleep(1);
    }
    semaforo->light = 0;
    pthread_exit(0);
}

void* activateSemaphore(void* arg){
    struct Sector* sector = (struct Sector*) arg; 
    pthread_t time;
    struct Vehicle* car = NULL;
    while(simulation->running){
        pthread_mutex_lock(&simulation->way_bridge); // Bloquea sentido del camino
        sleep(1);
        sector->semaforo->light = 1;
        pthread_create(&time, NULL, timer, sector->semaforo); //Inicia el temporizador del semaforo
        while(!emptyBridge());
        simulation->way = sector->side;
        while(sector->semaforo->light){ 
            if(sector->ready->first &&  pthread_mutex_trylock(&simulation->semaphores[0]) == 0){
                //P(Puente[0]) pido el primer espacio
                car = dequeue(sector->ready);
                pthread_create(&(car->tid), NULL, cross_bridge, car);
            }
        }
        pthread_mutex_unlock(&simulation->way_bridge); // Desbloquea el sentido del camino
        sector->semaforo->light = -1;//Luz en amarillo
        sleep(1);//tiempo de luz amarilla
        sector->semaforo->light = 0;// Luz roja
    }
    pthread_exit(0);
}

void* semaphore(void* arg){
    pthread_create(&simulation->east->semaforo->tid, NULL, activateSemaphore, simulation->east);
    sleep(1);
    pthread_create(&simulation->west->semaforo->tid, NULL, activateSemaphore, simulation->west);
    pthread_join(simulation->east->semaforo->tid, NULL);
    pthread_join(simulation->west->semaforo->tid, NULL);
    pthread_exit(0);
}

void* establishofficer(void* arg){
    struct Sector* sector = (struct Sector*) arg; 
    struct Vehicle* car = NULL;
    while(simulation){
        if(emptyBridge()){
            pthread_mutex_lock(&simulation->way_bridge); // Bloquea sentido del camino
            simulation->way = sector->side;
            for (int i = 0; i < sector->transit_officer->number_cars_pass && sector->ready->first; i++){
                pthread_mutex_lock(&simulation->semaphores[0]);
                sector->transit_officer->number = sector->transit_officer->number_cars_pass - i;
                car = dequeue(sector->ready);
                pthread_create(&car->tid, NULL, cross_bridge, car);
            }
            sector->transit_officer->number = 0;
            pthread_mutex_unlock(&simulation->way_bridge); // Desbloquea el sentido del camino
            sleep(1);
        }
    }
    pthread_exit(0);
}

void* officerTransit(void *arg){
    pthread_create(&simulation->east->transit_officer->tid, NULL, establishofficer, simulation->east);
    pthread_create(&simulation->west->transit_officer->tid, NULL, establishofficer, simulation->west);
    pthread_join(simulation->east->transit_officer->tid, NULL);
    pthread_join(simulation->west->transit_officer->tid, NULL);
    pthread_exit(0);
}

//Se encarga de escuchar las peticiones del usuario
void* userListener(void* arg){
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
    switch (simulation->modality){
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
    pthread_create(&cars_east, NULL, activatecarMaker, simulation->east);
    pthread_t cars_west;
    pthread_create(&cars_west, NULL, activatecarMaker, simulation->west);
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
    char *substr = malloc(sizeof(char*));
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
        simulation->modality = num;
    }else if(compare(section, "bridge")){
        if(compare(name, "length")){
            simulation->lenght = num;
            simulation->bridge = (int*) malloc (simulation->lenght * sizeof(int));
            simulation->semaphores = (pthread_mutex_t*) malloc (simulation->lenght * sizeof(pthread_mutex_t));
        }
    }else if(compare(section, "sector:east")){
        if(compare(name, "arrive-exp-time-cars")){
           simulation->east->average_cars = num;
        }else if(compare(name, "number-cars-pass")){
            simulation->east->transit_officer->number_cars_pass = num;
        }else if(compare(name, "traffic-light-time")){
            simulation->east->semaforo->time_in_green = num;
        }else if(compare(name, "speed-cars-upper")){
            simulation->east->max_velocity_cars = num;
        }else if(compare(name, "speed-cars-lower")){
            simulation->east->min_velocity_cars = num;
        }else if(compare(name, "ambulance-probability")){
            simulation->east->ambulance_probability = num;
        }
    }else if(compare(section, "sector:west")){
        if(compare(name, "arrive-exp-time-cars")){
            simulation->west->average_cars = num;
        }else if(compare(name, "number-cars-pass")){
            simulation->west->transit_officer->number_cars_pass = num;
        }else if(compare(name, "traffic-light-time")){
            simulation->west->semaforo->time_in_green = num;
        }else if(compare(name, "speed-cars-upper")){
            simulation->west->max_velocity_cars = num;
        }else if(compare(name, "speed-cars-lower")){
            simulation->west->min_velocity_cars = num;
        }else if(compare(name, "ambulance-probability")){
            simulation->west->ambulance_probability = num;
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
    simulation = initialize_simulation();
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
    //Colocamos una semilla aleatoria
    srand(time(NULL));
    //Inicializamos los bloqueos y espacios del puente
    for(int i = 0; i < simulation->lenght; i++){
        pthread_mutex_init(&simulation->semaphores[i], NULL);
        simulation->bridge[i] = -1;
    } 
    pthread_mutex_init(&simulation->way_bridge, NULL);
    return 1;
}

void stopSimulation(){
    system("clear");
    printf("\n\t\t FINALIZANDO SIMULACION . . .\n");
    //Finalizamos los hilos
    for(int i = 0; i < simulation->lenght; i++){
        pthread_mutex_destroy(&simulation->semaphores[i]);
    }
    pthread_mutex_destroy(&simulation->way_bridge);
    if(simulation->modality == 2){
        free(simulation->east->semaforo);
        free(simulation->west->semaforo);
    }
    while(simulation->east->ready->first){
        struct Vehicle* car = dequeue(simulation->east->ready);
        pthread_join(car->tid, NULL);
        free(car);
    }
    free(simulation->east->ready);
    while(simulation->west->ready->first){
        struct Vehicle* car = dequeue(simulation->west->ready);
        pthread_join(car->tid, NULL);
        free(car);
    }
    free(simulation->west->ready);
    while(simulation->east->finish->first){
        struct Vehicle* car = dequeue(simulation->east->finish);
        pthread_join(car->tid, NULL);
        free(car);
    }
    //free(finishEast); one problem in free . . . . 
    while(simulation->west->finish->first){
        struct Vehicle* car = dequeue(simulation->west->finish);
        pthread_join(car->tid, NULL);
        free(car);
    }
    //free(finishWest);
}