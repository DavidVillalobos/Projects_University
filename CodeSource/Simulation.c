#include"Simulation.h"

struct Simulation* initialize_simulation(){
    struct Simulation* simulation = malloc(sizeof(struct Simulation));
    simulation->west = initialize_sector(0);
    simulation->east = initialize_sector(1);
    simulation->lenght = -1;
    simulation->modality = -1;
    simulation->plates = 0;
    simulation->running = 0;
    simulation->way = 0;
    return simulation;
}

struct Simulation* simulation;

void show_bridge(){
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

void show_simulation(){
    system("clear");
    printf("\nVia: Este ");
    (simulation->way)?printf("-->"):printf("<--");
    printf(" Oeste\n");
    printf("\nCruzaron al Este: ");
    show_queue(simulation->east->finish);
    if(simulation->modality == 2){ 
        printf("\nSemaforo Este "); 
        if(simulation->east->semaforo->light)
            printf("Verde (%d)",simulation->east->semaforo->time);
        else
            printf("Rojo"); 
    }
    if(simulation->modality == 3){
        printf("\nOficial Este k(%d)",simulation->east->transit_officer->number); 
    }
    printf("\nEste -> ");
    show_queue(simulation->east->ready);
    show_bridge();
    printf("Oeste ->");
    show_queue(simulation->west->ready);
    if(simulation->modality == 2){ 
        printf("\nSemaforo Oeste "); 
        if(simulation->west->semaforo->light)
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
    if(car->direction){//si venia del este va para el oeste
        enqueue(simulation->west->finish, car);
    }else{// si venia del oeste va para el este
        enqueue(simulation->east->finish, car);
    }
    pthread_exit(0);
}

void* activate_car_maker(void* arg){
    struct Sector* sector = (struct Sector*) arg;
    while(simulation->running){// - media * log(e)[1 - (0 < rand() < 1)]
        sleep(- sector->average_cars * log( 1 - (double) (rand()%1000)/1000));
        //Crear carro y definimos los atributos
        struct Vehicle* car = malloc(sizeof(struct Vehicle));
        car->direction = sector->side;
        car->num = simulation->plates++;
        car->speed = sector->min_velocity_cars + rand() % (sector->max_velocity_cars + 1 - sector->min_velocity_cars);
        car->priority = (10 - sector->ambulance_probability <= rand() % 11)? 1: 0;
        if(car->priority){
            enqueue_priority(sector->ready, car);
        }else{
            enqueue(sector->ready, car);
        }
    }
    pthread_exit(0);
}

int empty_bridge(){
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
    while (simulation->running){
        if(simulation->way){ pasar = simulation->east; ceder = simulation->west;}
        else{ pasar = simulation->west; ceder = simulation->east;}
        if(pasar->ready->first && !pasar->ready->first->car->priority){
            if(ceder->ready->first && ceder->ready->first->car->priority){
                while(!empty_bridge() && !pasar->ready->first->car->priority);
                if(!pasar->ready->first->car->priority){
                    struct Sector* aux = ceder;
                    ceder = pasar;
                    pasar = aux;
                    simulation->way = pasar->side;
                }
            }    
        }
        if(pasar->ready->first){
            //P(Puente[0]) pido el primer espacio
            pthread_mutex_lock(&simulation->semaphores[0]);
            car = dequeue(pasar->ready);
            pthread_create(&(car->tid), NULL, cross_bridge, car);
            car = NULL;
        }else if(ceder->ready->first && empty_bridge()){
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

void* activate_semaforo(void* arg){
    struct Sector* sector = (struct Sector*) arg; 
    struct Sector* other_sector = (sector->side)? simulation->west : simulation->east; 
    pthread_t time;
    struct Vehicle* car = NULL;
    while(simulation->running){
        pthread_mutex_lock(&simulation->way_bridge); // Bloquea sentido del camino
        sleep(1);
        sector->semaforo->light = 1;
        pthread_create(&time, NULL, timer, sector->semaforo); //Inicia el temporizador del semaforo
        while(!empty_bridge());
        simulation->way = sector->side;
        while(sector->semaforo->light){ 
            if(sector->ready->first){
                //Si mi carro tiene prioridad o si el otro lado no tiene prioridad
                if(sector->ready->first->car->priority || !(other_sector->ready->first && other_sector->ready->first->car->priority)){
                    if(pthread_mutex_trylock(&simulation->semaphores[0]) == 0){
                        //P(Puente[0]) pido el primer espacio
                        car = dequeue(sector->ready);
                        pthread_create(&(car->tid), NULL, cross_bridge, car);
                    }
                }
            }
        }
        pthread_mutex_unlock(&simulation->way_bridge); // Desbloquea el sentido del camino
        sector->semaforo->light = 0;// Luz roja
        sleep(1);
    }
    pthread_exit(0);
}

void* semaphore(void* arg){
    pthread_create(&simulation->east->semaforo->tid, NULL, activate_semaforo, simulation->east);
    sleep(1);
    pthread_create(&simulation->west->semaforo->tid, NULL, activate_semaforo, simulation->west);
    pthread_join(simulation->east->semaforo->tid, NULL);
    pthread_join(simulation->west->semaforo->tid, NULL);
    pthread_exit(0);
}

void* establish_officer(void* arg){
    struct Sector* sector = (struct Sector*) arg; 
    struct Sector* other_sector = (sector->side)? simulation->west : simulation->east; 
    struct Vehicle* car = NULL;
    while(simulation->running){
        pthread_mutex_lock(&simulation->way_bridge); // Bloquea sentido del camino
        simulation->way = sector->side;
        sector->transit_officer->number = sector->transit_officer->number_cars_pass;
        while(0 < sector->transit_officer->number && sector->ready->first){
            if(!sector->ready->first->car->priority && other_sector->ready->first && other_sector->ready->first->car->priority){
                break; //Si no tengo prioridad y hay un carro al otro lado con prioridad
            }
            pthread_mutex_lock(&simulation->semaphores[0]);
            car = dequeue(sector->ready);
            pthread_create(&car->tid, NULL, cross_bridge, car);
            sector->transit_officer->number--;
        }
        while(!empty_bridge()){ //Mientras los carros esten pasando el puente aun
            if(0 < sector->transit_officer->number && sector->ready->first){
                if(sector->ready->first->car->priority || !(other_sector->ready->first && !other_sector->ready->first->car->priority)){
                    pthread_mutex_lock(&simulation->semaphores[0]);
                    car = dequeue(sector->ready);
                    pthread_create(&car->tid, NULL, cross_bridge, car);
                    sector->transit_officer->number--;
                }
            }
        }
        pthread_mutex_unlock(&simulation->way_bridge); // Desbloquea el sentido del camino
        sector->transit_officer->number = 0;
        sleep(1);
    }
    pthread_exit(0);
}

void* officer_transit(void *arg){
    pthread_create(&simulation->east->transit_officer->tid, NULL, establish_officer, simulation->east);
    pthread_create(&simulation->west->transit_officer->tid, NULL, establish_officer, simulation->west);
    pthread_join(simulation->east->transit_officer->tid, NULL);
    pthread_join(simulation->west->transit_officer->tid, NULL);
    pthread_exit(0);
}

void* user_listener(void* arg){
    while (getchar() != '\n');
    simulation->running = 0;
    pthread_exit(0);
}

void play_simulation(){
    simulation->running = 1; //Encendemos la simulacion
    //Creamos un hilo que escucha peticiones al usuario
    pthread_t user;
    pthread_create(&user, NULL, user_listener, NULL);
    //Creamos un hilo que administra la modalidad
    pthread_t mod;
    switch (simulation->modality){
        case 1: { pthread_create(&mod, NULL, fifo, NULL); break; }
        case 2: { pthread_create(&mod, NULL, semaphore, NULL); break; }
        case 3:{ pthread_create(&mod, NULL, officer_transit, NULL); break; }
        default: break;
    }
    //Creamos los hilos que crean automoviles
    pthread_t cars_east_maker;
    pthread_create(&cars_east_maker, NULL, activate_car_maker, simulation->east);
    pthread_t cars_west_maker;
    pthread_create(&cars_west_maker, NULL, activate_car_maker, simulation->west);
    //Veamos la simulacion
    while(simulation->running) show_simulation();
    //Esperamos que los carros que ya iban en el puente terminen de pasar 
    while(!empty_bridge());
    //Esperamos que los hilos terminen
    pthread_join(user, NULL);
    pthread_join(mod, NULL);
    pthread_join(cars_east_maker, NULL);
    pthread_join(cars_west_maker, NULL);
    system("clear");
    //Se muestran los resultados finales
    show_final_statistics();
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

void save_setting(char* section, char* name, int num, char* comment){
    if(compare(section, "modality") && compare(name, "id")){
        if(num == 1 || num == 2 || num == 3){
            simulation->modality = num;
        }
    }else if(compare(section, "bridge")){
        if(compare(name, "length")){
            if(-1 < num){
                simulation->lenght = num;
                simulation->bridge = (int*) malloc (simulation->lenght * sizeof(int));
                simulation->semaphores = (pthread_mutex_t*) malloc (simulation->lenght * sizeof(pthread_mutex_t));
            }
        }
    }else if(compare(section, "sector:east") || compare(section, "east")){
        if(compare(name, "average_cars")){
           simulation->east->average_cars = num;
        }else if(compare(name, "k_number_cars")){
            simulation->east->transit_officer->number_cars_pass = num;
        }else if(compare(name, "time_green_light")){
            simulation->east->semaforo->time_in_green = num;
        }else if(compare(name, "maximum_speed_cars")){
            simulation->east->max_velocity_cars = num;
        }else if(compare(name, "minimum_speed_cars")){
            simulation->east->min_velocity_cars = num;
        }else if(compare(name, "ambulance_probability")){
            simulation->east->ambulance_probability = num;
        }
    }else if(compare(section, "sector:west") || compare(section, "west")){
        if(compare(name, "average_cars")){
            simulation->west->average_cars = num;
        }else if(compare(name, "k_number_cars")){
            simulation->west->transit_officer->number_cars_pass = num;
        }else if(compare(name, "time_green_light")){
            simulation->west->semaforo->time_in_green = num;
        }else if(compare(name, "maximum_speed_cars")){
            simulation->west->max_velocity_cars = num;
        }else if(compare(name, "minimum_speed_cars")){
            simulation->west->min_velocity_cars = num;
        }else if(compare(name, "ambulance_probability")){
            simulation->west->ambulance_probability = num;
        }
    }
}

int init_configurations(char* path) {
    FILE *config = fopen (path, "r");
    if(!config) {
        printf("Settings file does not exist in the path: %s\n", path);
        return 0;
    }
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
            comment = slide(line,35, 10);
            printf("Section -> %s comment: %s\n", section, comment);
        }
        else if(line[0] == 10){ printf("\n"); section = NULL;}
        else if(section != NULL){
            name = slide(line, 0, 32);
            value = slide(line, 92, 32);
            num = atoi(value) - ((value[strlen(value)-1] == 104)? 30 : 48);
            comment = slide(line,35, 10);
            save_setting(section, name, num, comment);    
            printf("\tVarible %s, is load with %d, comment: %s\n", name, num, comment);
        }
    }
    fclose (config);//cerramos el fichero
    printf("\nVerifying that all settings have been loaded . . .\n");
    if(!verify_all_configured()){
        printf("*** Error: One or more variables have no value, the simulation was canceled\n");
        return 0;
    }
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

void stop_simulation(){
    //Finalizamos los hilos
    for(int i = 0; i < simulation->lenght; i++){
        pthread_mutex_destroy(&simulation->semaphores[i]);
    }
    pthread_mutex_destroy(&simulation->way_bridge);
    free(simulation->east->semaforo);
    free(simulation->west->semaforo);
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
    free(simulation->east->finish); 
    while(simulation->west->finish->first){
        struct Vehicle* car = dequeue(simulation->west->finish);
        pthread_join(car->tid, NULL);
        free(car);
    }
    free(simulation->west->finish);
}

void show_help(){
    printf("Usage: ./out [PATH] [ID]\n");
    printf("Path: Settings file path\n");
    printf("\tThe configuration file contains all the\n");
    printf("\tvariables necessary for the simulation\n");
    printf("\tExample in test/config.ini\n");
    printf("\tconfig.ini is the default file\n");
    printf("Id: Mode of the simulation\n");
    printf("\tIf you want to test in various\n");
    printf("\tmodalities without modifying the\n");
    printf("\tconfiguration file, you can send a\n");
    printf("\tdifferent id:\n");
    printf("\t\t1) FIFO\n");
    printf("\t\t2) Semaphores\n");
    printf("\t\t3) Transit officers \n");
    printf("This program was built for an operating systems project\n");
    printf("By David Villalobos & Giancarlo Alvarado\n");
}

int verify_all_configured(){
    int flag = 1;
    if(simulation->lenght == -1){
        printf("   The lenght of bridge is missing\n");
        printf("   or enter a negative value\n");
        flag = 0;
    }
    if(simulation->east->average_cars == -1){
        printf("   The average of cars in the eastern sector is missing\n");
        flag = 0;
    }
    if(simulation->east->transit_officer->number_cars_pass == -1){
        printf("   The K number of cars in the eastern sector is missing\n");
        flag = 0;
    }
    if(simulation->east->semaforo->time_in_green == -1){
        printf("   The light time in traffic light green in the eastern sector is missing\n");
        flag = 0;
    }
    if(simulation->east->max_velocity_cars == -1){
        printf("   The maximum velocity of cars in the eastern sector is missing\n");
        flag = 0;
    }
    if(simulation->east->min_velocity_cars == -1){
        printf("   The minimum velocity of cars in the eastern sector is missing\n");
        flag = 0;
    }
    if(simulation->east->ambulance_probability == -1){
        printf("   The probability of ambulance in the eastern sector is missing\n");
        flag = 0;
    }
     if(simulation->west->average_cars == -1){
        printf("   The average of cars in the western sector is missing\n");
        flag = 0;
    }
    if(simulation->west->transit_officer->number_cars_pass == -1){
        printf("   The K number of cars in the western sector is missing\n");
        flag = 0;
    }
    if(simulation->west->semaforo->time_in_green == -1){
        printf("   The light time in traffic light green in the western sector is missing\n");
        flag = 0;
    }
    if(simulation->west->max_velocity_cars == -1){
        printf("   The maximum velocity of cars in the western sector is missing\n");
        flag = 0;
    }
    if(simulation->west->min_velocity_cars == -1){
        printf("   The minimum velocity of cars in the western sector is missing\n");
        flag = 0;
    }
    if(simulation->west->ambulance_probability == -1){
        printf("   The probability of ambulance in the western sector is missing\n");
        flag = 0;
    }
    return flag;
}

void show_final_statistics(){
    int carsEast = simulation->east->ready->size + simulation->west->finish->size;
    int carsWest = simulation->west->ready->size + simulation->east->finish->size;
    int ambulancesEast = simulation->east->ready->cantAmbulances + simulation->west->finish->cantAmbulances;
    int ambulancesWest = simulation->west->ready->cantAmbulances + simulation->east->finish->cantAmbulances;
    printf("MODALITY -> %s\n", (simulation->modality == 1)? "FIFO": (simulation->modality == 2)? "SEMAPHORES":"OFFICERS");
    printf("Amount cars in the simulation: %d\n", carsEast + carsWest);
    printf("Amount ambulances in the simulation: %d\n", ambulancesEast + ambulancesWest);
    //-----------------------------------------------------------------------------------
    printf("Eastern sector\n");
    printf("Amount cars: %d\n", carsEast);
    printf("Amount ambulances: %d\n", ambulancesEast);
    printf("Amount cars in ready: %d\n", simulation->east->ready->size);
    printf("Amount ambulances in ready: %d\n", simulation->east->ready->cantAmbulances);
    printf("Amount cars processed: %d\n", simulation->west->finish->size);
    printf("Amount ambulances processed: %d\n", simulation->west->finish->cantAmbulances);
    printf("Percentage of cars that processed: %5.2f%% \n", ((float)simulation->west->finish->size / carsEast) * 100);
    float porcent = 0;
    if(0 < ambulancesEast){
        porcent = ( (float) simulation->west->finish->cantAmbulances / ambulancesEast) * 100;
    }
    printf("Percentage of ambulances that processed: %5.2f%% \n", porcent);
    //----------------------------------------------------------------------------------
    printf("Western sector\n");
    printf("Amount cars in %d\n", carsWest);
    printf("Amount ambulances: %d\n", ambulancesWest);
    printf("Amount cars in ready: %d\n", simulation->west->ready->size);
    printf("Amount ambulances in ready: %d\n", simulation->west->ready->cantAmbulances);
    printf("Amount cars processed: %d\n", simulation->east->finish->size);
    printf("Amount ambulances processed: %d\n", simulation->east->finish->cantAmbulances);
    printf("Percentage of cars that processed: %5.2f%% \n", ((float)simulation->east->finish->size / carsWest) * 100);
    porcent = 0;
    if(0 < ambulancesWest){
        porcent = ( (float) simulation->east->finish->cantAmbulances / ambulancesWest) * 100;
    }
    printf("Percentage of ambulances that processed: %5.2f%% \n",  porcent);
}