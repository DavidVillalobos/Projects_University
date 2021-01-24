#include"Simulation.h"

void show_bridge(){
    printf("  Este  ║       ║   MODALIDAD");
    switch (modality){
        case 1:printf(" 1) FIFO\n");break;
        case 2: printf(" 2) SEMAFOROS               ");
            printf("(%s)[%d]\n", (way_bridge)?"0":" ", (way_bridge)?ki:0); break;
        case 3:
            printf(" 3) OFICIALES");
            printf("(%s)[%d]\n", (way_bridge)?"0":" ", (way_bridge)?ki:0);break;
        default: break;
    }
    printf("--------╚═╗   ╔═╝-------------------------------------\n");  
    for (int i = 0; i < lenght; i++){
        if(bridge[i]){
            printf(" ~ ~ ~ ~ ~║┌─┐║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            printf(" ~ ~ ~ ~ ~║┤%s├║",(bridge[i]->priority)?"+":"|");
            printf("[%0*d]", 3, bridge[i]->plate);
            printf(" ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            printf(" ~ ~ ~ ~ ~║└─┘║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
        }else{
            printf(" ~ ~ ~ ~ ~║   ║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            printf(" ~ ~ ~ ~ ~║ | ║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            printf(" ~ ~ ~ ~ ~║   ║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
        }
    }
    printf("--------╔═╝   ╚═╗-------------------------------------\n");
    printf(" Oeste  ║       ║   Direccion de la Via: ");
    (way_bridge)?printf("Este - Oeste   "):printf("Oeste - Este   ");
    switch(modality){
        case 2: printf("(%s)[%d]",  (!way_bridge)?"0":" " , (!way_bridge)?ki:0); break;
        case 3: printf("(%s)[%d]", (!way_bridge)?"0":" ", (!way_bridge)?ki:0); break;
    }
}

void show_entrance_bridge(struct Sector* sector){ 
    struct Node* aux = sector->ready->first;
    if(sector->side == 0){
        printf("\n        ║        ");
    }else{
        printf("\n                 ");
    }
    for (int i = 0; i < sector->ready->size; i++){
        printf("[%0*d]", 3, aux->car->plate);
        aux = aux->next;
    }
    if(sector->side == 1){
        printf("\n        ╔════════");
    }else{
        printf("\n        ║        ");
    }
    for (int i = 0; i < sector->ready->size; i++){
        printf("═════");
    }
    printf("\n        ║        ");
    aux = sector->ready->first;
    for (int i = 0; i < sector->ready->size; i++){            
        printf(" %s ", (aux->car->priority)?"-+-":"───");
        aux = aux->next;
    }
    printf("\n        ║        ");
    for (int i = 0; i < sector->ready->size; i++){
        printf("└O─O ");
    }
    printf("\n        ║        ");
    if(sector->side == 0){
        printf("\n        ╚════════");
    }else{
        printf("\n        ║        ");
    }
    for (int i = 0; i < sector->ready->size; i++){
        printf("═════");
    }
    printf("\n"); 
}

void* show_simulation(){
    while(1){
        system("clear");
        printf("\nCruzaron al Este: ");
        show_queue(sector_east->finish);
        show_entrance_bridge(sector_east);
        show_bridge();
        show_entrance_bridge(sector_west);
        printf("\nCruzaron al Oeste: ");
        show_queue(sector_west->finish);
        sleep(1);
    }
}

int view_direction_bridge(){
    struct Vehicle* car; // Verifica 70 veces, para asegurarse
    for (int j = 0; j < 70; j++){ // por que los carros estan en movimiento
        for (int i = 0; i < lenght; i++){
            car = bridge[i]; //Se toma el carro por si cambia de lugar
            if(car){ 
                return car->direction;
            }
        }
    }
    return -1;
}

void* semaphore(){
    while(1){
        way_bridge = 1;
        for (ki = sector_east->time_semaphore; 0 < ki; ki--){ // Para poder visualizar los segundos en el semaforo
            sleep(1);
        }
        way_bridge = 0;
        for(ki = sector_west->time_semaphore; 0 < ki; ki--){
            sleep(1);
        }
    }
}

void* officers(){
    while(1){
        way_bridge = 1;
        ki = sector_east->ki_cars;
        //(Si aun pueden pasar vehiculos, y tengo vehiculos) o (el otro sector no tiene vehiculos) o (tengo carros esperando y el otro lado no tiene ambulancias esperando)
        while( (0 < ki && sector_east->ready->first) || (0 < ki && sector_east->ready->first && 0 == sector_west->ready->sizeAmbulances)){
            sleep(1);
        }
        way_bridge = 0;
        ki = sector_west->ki_cars;
        while( (0 < ki && sector_west->ready->first) || (0 < ki && sector_west->ready->first && 0 == sector_east->ready->sizeAmbulances)){
           sleep(1);
        }
    }
}

void verify_fifo(struct Vehicle* car, struct Sector* sector){
    struct Sector* other_sector = (sector->side)? sector_west : sector_east;
    while(sector->ready->sizeAmbulances == 0 && other_sector->ready->first && 0 < other_sector->ready->sizeAmbulances){
        sleep(1);
    }
    while(car->direction != way_bridge){ //Mientras el puente no este en mi direccion 
        if(view_direction_bridge() == -1){ //Si el puente esta vacio
            way_bridge = car->direction;
        }
        sleep(1);
    }
    while(sector->ready->first->car != car){ //Esperar hasta que sea el primero
        //Verificar una ambulancia puede rayar
        if(car->priority && car->direction == way_bridge){
            check_priority(sector->ready, car, way_bridge);
        }
        sleep(1);
    }
}

void verify_semaphore(struct Vehicle* car, struct Sector* sector){
    int flag = 1;
    struct Sector* other_sector = (sector->side)? sector_west : sector_east;
    while(sector->ready->sizeAmbulances == 0 && other_sector->ready->first && 0 < other_sector->ready->sizeAmbulances){
        sleep(1);
    }
    if(car->priority){
        while(flag){
            if(view_direction_bridge() != !car->direction && sector->ready->first->car == car){
                flag = 0;
            }else{
                if(car->direction == way_bridge){
                    check_priority(sector->ready, car, way_bridge);
                }
                sleep(1);
            }
        }
    }else{
        while(flag){
            if(way_bridge != car->direction || view_direction_bridge() == !car->direction){
                sleep(1);
            }else{
                if(sector->ready->first->car == car){
                    flag = 0;
                }else{
                    sleep(1);
                }
            }
        }
    }
}

void verify_officers(struct Vehicle* car, struct Sector* sector){
    int flag = 1;
    if(car->priority){
        while(flag){
            if(view_direction_bridge() != !car->direction && sector->ready->first->car == car){
                flag = 0;
            }else{
                if(car->direction == way_bridge){
                    check_priority(sector->ready, car, way_bridge);
                }
                sleep(1);
            }
        }
    }else{
        while(flag){
            if(way_bridge != car->direction || view_direction_bridge() == !car->direction){
                sleep(1);
            }else{
                if(sector->ready->first->car == car && ki > 0){
                    flag = 0;
                }else{
                    sleep(1);
                }
            }
        }
    }
}

void* start_tour(void* arg){
    struct Vehicle* car = (struct Vehicle*) arg;
    struct Sector* sector = (car->direction)? sector_east: sector_west;
    if(car->priority && way_bridge == car->direction){
        enqueue_priority(sector->ready, car);
    }else{
        enqueue(sector->ready, car);
    }
    switch(modality){
        case 1: verify_fifo(car, sector); break;
        case 2: verify_semaphore(car, sector); break;
        case 3: verify_officers(car, sector); break;
    }
    //Entrando al puente
    if(modality == 3){
        pthread_mutex_lock(&ki_oficcers_mutex);
        ki--; //Pasa un carro, asi se el informa a los oficiales
        pthread_mutex_unlock(&ki_oficcers_mutex);
    }
    if(car->direction){ // Este - Oeste
        pthread_mutex_lock(&semaphores[0]);
        //pthread_cond_signal(&emptybridge_cond);
        dequeue(sector->ready);
        //Empezar a cruzar el puente 
        bridge[0] = car;
        for (int i = 0; i < lenght; i++){
            sleep(car->speed);//Utilizando el puente
            if(i+1<lenght){//Si me falta camino, pido el de adelante
                pthread_mutex_lock(&semaphores[i+1]);//P(Puente[i + 1])
                bridge[i+1] = car;
            }
            bridge[i] = NULL;
            pthread_mutex_unlock(&semaphores[i]);//V(Puente[i]) libero el que estoy
        }
    }else{// Oeste - Este
        //Entrando al puente
        pthread_mutex_lock(&semaphores[lenght-1]);
        //pthread_cond_signal(&emptybridge_cond);
        dequeue(sector->ready);
        //Empezar a cruzar el puente 
        bridge[lenght-1] = car;
        for (int i = lenght-1; 0 <= i; i--){
            sleep(car->speed);//Utilizando el puente
            if(i-1 >= 0){//Si me falta camino, pido el de adelante
                pthread_mutex_lock(&semaphores[i-1]);//P(Puente[i + 1])
                bridge[i-1] = car;
            }
            bridge[i] = NULL;
            pthread_mutex_unlock(&semaphores[i]);//V(Puente[i]) libero el que estoy
        }
    }
    //Saliendo del puente
    // otra via esta esperando por el paso 
    //Agregamos el carro a la lista de procesos terminados segun el lado
    if(car->direction){
        enqueue(sector_west->finish, car);
    }else{
        enqueue(sector_east->finish, car);
    }
    pthread_exit(0); //Termina el recorrido
}

void* start_rutine(void* arg){
    struct Sector* sector = (struct Sector*) arg;
    pthread_t* arr = (sector->side)? threads_east : threads_west;
    for (int i = 0; i < cant_cars; i++){ //Cantidad arbitraria de carros segun el sector
        // Tiempo de espera
        sleep(- sector->average_cars * log( 1 - (double) (rand()%1000)/1000));
        struct Vehicle* car = malloc(sizeof(struct Vehicle)); //Inicializamos el automovil
        car->direction = sector->side;
        pthread_mutex_lock(&plates_mutex);
        car->plate = plates++;
        pthread_mutex_unlock(&plates_mutex);
        car->speed = sector->min_velocity_cars + rand() % (sector->max_velocity_cars + 1 - sector->min_velocity_cars);
        car->priority = (sector->ambulance_probability)?(10 - sector->ambulance_probability <= rand() % 11)? 1: 0: 0;
        pthread_create(&arr[i],NULL, start_tour, car);//Automovil inicial el recorrido
    }
    pthread_exit(0);
}

void run_simulation(){
    //Un hilo para mantener la informacion imprimiendose
    pthread_t show;
    pthread_create(&show, NULL, show_simulation, NULL);
    pthread_t mod; //Inician los semaforos o oficiales
    switch (modality){
        case 2: pthread_create(&mod, NULL, semaphore, NULL); break;
        case 3: pthread_create(&mod, NULL, officers, NULL); break;
        default: break;
    }
    //Inician los automoviles
    pthread_t east; 
    pthread_create(&east, NULL, start_rutine, sector_east); 
    pthread_t west;
    pthread_create(&west, NULL, start_rutine, sector_west);
    //Esperar que los arreglos terminen
    pthread_join(east, NULL);
    pthread_join(west, NULL);
    for (int i = 0; i < cant_cars; i++){
        pthread_join(threads_east[i], NULL);
        pthread_join(threads_west[i], NULL);
    }
    for(int i = 0; i < lenght; i++){
        pthread_mutex_destroy(&semaphores[i]);
        free(bridge[i]);
    }
    free(bridge);
    free(semaphores);
    pthread_mutex_destroy(&plates_mutex);
    pthread_mutex_destroy(&ki_oficcers_mutex);
    atexit(free_data);
} 

void free_data(){
    sleep(2);
    system("clear");
    printf("Simulacion Finalizada . . .");
    while(sector_west->finish->first)
        free(dequeue(sector_west->finish));
    while(sector_east->finish->first)
        free(dequeue(sector_east->finish));
    free(sector_east->finish);
    free(sector_west->finish);
    free(sector_east->ready);
    free(sector_west->ready);
    free(sector_east);
    free(sector_west);
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
    if(indexBegin > tam) return NULL;
    char *substr = malloc(sizeof(char*));
    int i = indexBegin;
    for(; i < indexFinish && i < strlen(str); i++)
        substr[i-indexBegin] = str[i];
    substr[i] = '\0';
    return substr;
}

void save_setting(char* section, char* name, int num){
    if(strcmp(section, "modality") == 0){
        if(strcmp(name, "id") == 0){
            if(num == 1 || num == 2 || num == 3){
                modality = num;
            }
        }else if(strcmp(name, "cant_cars") == 0){
            cant_cars = num;
        }
    }else if(strcmp(section, "bridge") == 0){
        if(strcmp(name, "length") == 0){
            if(0 < num){
                lenght = num;
                bridge = (struct Vehicle**) malloc (lenght * sizeof(struct Vehicle**));
                semaphores = (pthread_mutex_t*) malloc (lenght * sizeof(pthread_mutex_t));
            }
        }
    }else if(strcmp(section, "sector:east") == 0 || strcmp(section, "east") == 0){
        if(strcmp(name, "average_cars") == 0){
           sector_east->average_cars = num;
        }else if(strcmp(name, "k_number_cars") == 0){
            sector_east->ki_cars = num;
        }else if(strcmp(name, "time_green_light") == 0){
            sector_east->time_semaphore = num;
        }else if(strcmp(name, "maximum_speed_cars") == 0){
            sector_east->max_velocity_cars = num;
        }else if(strcmp(name, "minimum_speed_cars") == 0){
            sector_east->min_velocity_cars = num;
        }else if(strcmp(name, "ambulance_probability") == 0){
            sector_east->ambulance_probability = num;
        }
    }else if(strcmp(section, "sector:west") == 0 || strcmp(section, "west") == 0){
        if(strcmp(name, "average_cars") == 0){
            sector_west->average_cars = num;
        }else if(strcmp(name, "k_number_cars") == 0){
            sector_west->ki_cars = num;
        }else if(strcmp(name, "time_green_light") == 0){
            sector_west->time_semaphore = num;
        }else if(strcmp(name, "maximum_speed_cars") == 0){
            sector_west->max_velocity_cars = num;
        }else if(strcmp(name, "minimum_speed_cars") == 0){
            sector_west->min_velocity_cars = num;
        }else if(strcmp(name, "ambulance_probability") == 0){
            sector_west->ambulance_probability = num;
        }
    }
}

int init_configurations(char* path){
    sector_west = initialize_sector(0);
    sector_east = initialize_sector(1);
    lenght = -1;
    modality = -1;
    plates = 1;
    way_bridge = 1;
    cant_cars = 20;
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
    printf("Read Configurations of file %s\n", path);
    while(fgets(line, 100, config) != NULL){
        if(line[0] == 91){
            section = slide(line, 91, 93);
            comment = slide(line, 35, 10);
            printf("  Section: %s", section);
            (comment != NULL)? printf("\tComment: %s\n", comment):printf("\n");
        }
        else if(line[0] != 10){
            name = slide(line, 0,32);
            if(name != NULL && name[0] != 35){
                value = slide(line, 61, 10);
                num = atoi(value);
                comment = slide(line,35, 10);
                if(section != NULL){
                    save_setting(section, name, num);
                    printf("\t%s: %d", name, num);
                    (comment != NULL)? printf("\tComment: %s\n", comment):printf("\n");
                }
            }
        }
    }
    fclose (config);//cerramos el fichero
    printf("\nVerifying that all settings have been loaded . . .\n");
    if(!verify_all_configured()){
        printf("*** Error: One or more variables have no value or not section, the simulation was canceled\n");
        return 0;
    }
    threads_east = (pthread_t*) malloc (cant_cars * sizeof(pthread_t));
    threads_west = (pthread_t*) malloc (cant_cars * sizeof(pthread_t));
    //Colocamos una semilla aleatoria
    srand(time(NULL));
    //Inicializamos los bloqueos y espacios del puente
    for(int i = 0; i < lenght; i++){
        pthread_mutex_init(&semaphores[i], NULL);
        bridge[i] = NULL;
    } 
    pthread_mutex_init(&plates_mutex, NULL);
    pthread_mutex_init(&ki_oficcers_mutex, NULL);
    if(modality == -1){
        printf("Choose one mode of simulation\n");
        printf("\t1) FIFO\n");
        printf("\t2) Semaphores\n");
        printf("\t3) Transit officers \n");
        int value = 0;
        printf("Enter a value: ");
        scanf("%d", &value);
        getchar();// For ignore \n
        modality = value;
        if(!(modality == 1 || modality == 2 || modality == 3)){
            printf("Error: The modality id must be a 1, 2 or 3\n");
            return 0;
        }
    }
    return 1;
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
    if(lenght == -1){
        printf("   The lenght of bridge is missing\n");
        printf("   or enter zero or negative value\n");
        flag = 0;
    }if(sector_east->average_cars == -1){
        printf("   The average of cars in the eastern sector is missing\n");
        flag = 0;
    } if(sector_east->ki_cars == -1){
        printf("   The K number of cars in the eastern sector is missing\n");
        flag = 0;
    }if(sector_east->time_semaphore == -1){
        printf("   The light time in traffic light green in the eastern sector is missing\n");
        flag = 0;
    }if(sector_east->max_velocity_cars == -1){
        printf("   The maximum velocity of cars in the eastern sector is missing\n");
        flag = 0;
    }if(sector_east->min_velocity_cars == -1){
        printf("   The minimum velocity of cars in the eastern sector is missing\n");
        flag = 0;
    }if(sector_east->ambulance_probability == -1){
        printf("   The probability of ambulance in the eastern sector is missing\n");
        flag = 0;
    }if(sector_west->average_cars == -1){
        printf("   The average of cars in the western sector is missing\n");
        flag = 0;
    }if(sector_west->ki_cars == -1){
        printf("   The K number of cars in the western sector is missing\n");
        flag = 0;
    }if(sector_west->time_semaphore == -1){
        printf("   The light time in traffic light green in the western sector is missing\n");
        flag = 0;
    }if(sector_west->max_velocity_cars == -1){
        printf("   The maximum velocity of cars in the western sector is missing\n");
        flag = 0;
    }if(sector_west->min_velocity_cars == -1){
        printf("   The minimum velocity of cars in the western sector is missing\n");
        flag = 0;
    }if(sector_west->ambulance_probability == -1){
        printf("   The probability of ambulance in the western sector is missing\n");
        flag = 0;
    }
    return flag;
}