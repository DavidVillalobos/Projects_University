#include"Simulation.h"

void show_bridge(){
    printf("  Este  ║|||||||║");
    switch (modality){
    case 1:
        printf(" ");
        break;
    case 2:
        printf("[%s](%d) ", (way_bridge)?"■":" ", sector_east->time_semaphore);
        break;
    case 3:
        printf(" ");
        break;
    default:
        break;
    }
    printf("Via: Este ");
    (way_bridge)?printf("-->"):printf("<--");
    printf(" Oeste\n");
    printf("--------╚═╗   ╔═╝---------------------------------------------------------\n");
    if(way_bridge){
        for (int i = 0; i < lenght; i++){
            if(bridge[i]){
                printf(" ~ ~ ~ ~ ~║┌=┐║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
                printf("~ ~ ~ ~ ~ ║┤%s",(bridge[i]->priority)?"┼":"█");printf("├║");
                printf("[%0*d]", 3, bridge[i]->plate);
                printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
                printf(" ~ ~ ~ ~ ~║└─┘║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            }else{
                printf(" ~ ~ ~ ~ ~║   ║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
                printf("~ ~ ~ ~ ~ ║ | ║ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
                printf(" ~ ~ ~ ~ ~║   ║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            }
        }
    }else{
        for (int i = lenght-1; 0 <= i; i--){
            if(bridge[i]){
                printf(" ~ ~ ~ ~ ~║┌=┐║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
                printf("~ ~ ~ ~ ~ ║┤%s",(bridge[i]->priority)?"┼":"█");printf("├║");
                printf("[%0*d]", 3, bridge[i]->plate);
                printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
                printf(" ~ ~ ~ ~ ~║└─┘║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            }else{
                printf(" ~ ~ ~ ~ ~║   ║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
                printf("~ ~ ~ ~ ~ ║ | ║ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
                printf(" ~ ~ ~ ~ ~║   ║~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            }
        }
    }
    printf("--------╔═╝   ╚═╗---------------------------------------------------------\n");
    printf(" Oeste  ║|||||||║");
    switch (modality){
    case 1:
        printf(" ");
        printf("FIFO\n");
        break;
    case 2:
        printf("[%s](%d) ", (!way_bridge)?"■":" ", sector_east->time_semaphore);
        printf("SEMAFOROS\n");
        break;
    case 3:
        printf(" ");
        printf("OFICIALES\n");
        break;
    default:
        break;
    }
}

void show_entrance_bridge(struct Sector* sector){ 
    struct Node* aux = sector->ready->first;
    printf("                 ");
    for (int i = 0; i < sector->ready->size; i++){
        printf("[%0*d]", 3, aux->car->plate);
        aux = aux->next;
    }
    printf("\n                 ");
    for (int i = 0; i < sector->ready->size; i++){
        printf("═════");
    }
    printf("\n                 ");
    aux = sector->ready->first;
    for (int i = 0; i < sector->ready->size; i++){            
        printf(" %s ", (aux->car->priority)?"[+]":"▄▄▄");
        aux = aux->next;
    }
    printf("\n                 ");
    for (int i = 0; i < sector->ready->size; i++){
        printf("└O─O ");
    }
    printf("\n\n                 ");
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
        if(modality == 2){ 
            printf("\nSemaforo Este "); 
            if(way_bridge)
                printf("Verde [%d]",sector_east->time_semaphore);
            else
                printf("Rojo"); 
        }
        if(modality == 3){
            printf("\nOficial Este k[%d]",sector_east->ki_cars); 
        }
        show_entrance_bridge(sector_east);
        show_bridge();
        show_entrance_bridge(sector_west);
        if(modality == 2){ 
            printf("\nSemaforo Oeste "); 
            if(!way_bridge)
                printf("Verde [%d]", sector_west->time_semaphore);
            else
                printf("Rojo"); 
        }
        if(modality == 3){
            printf("\nOficial Oeste k[%d]", sector_west->ki_cars); 
        }
        printf("\nCruzaron al Oeste: ");
        show_queue(sector_west->finish);
        sleep(0.001);
    }
}

int empty_bridge(){
    for (int j = 0; j < 100; j++){
        for (int i = 0; i < lenght; i++){
            if(bridge[i]){
                return 0;
            }
        }
    }
    return 1;
}

void* semaphore(){
    while(1){
        way_bridge = 1;
        pthread_cond_signal(&way_bridge_cond);
        sleep(sector_east->time_semaphore);
        way_bridge = 0;
        pthread_cond_signal(&way_bridge_cond);
        sleep(sector_west->time_semaphore);
    }
}

void* officers(){
    while(1){
        way_bridge = 1;
        //while contador diferente de mi ki
        //   pthread_cond_wait(&emptybridge_cond, &emptybridge_mutex); 
        // cada vez que un automovil pase ki++ entonces signal
        way_bridge = 0;
    }
}

void* start_tour(void* arg){
    struct Vehicle* car = (struct Vehicle*) arg;
    struct Sector* sector = (car->direction)? sector_east: sector_west;
    enqueue(sector->ready,car);
    while(car->direction != way_bridge){
        pthread_cond_wait(&way_bridge_cond, &way_bridge_mutex);
    }
    pthread_mutex_lock(&semaphores[0]);
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
    //Agregamos el carro a la lista de procesos terminados segun el lado
    if(car->direction){
        enqueue(sector_east->finish, car);
    }else{
        enqueue(sector_west->finish, car);
    }
    pthread_exit(0);
}

void* start_rutine(void* arg){
    int* side = (int*) arg; 
    pthread_t* arr = (side)? threads_east : threads_west;
    struct Sector* sector = (side)? sector_east : sector_west;
    for (int i = 0; i < cant_cars; i++){ //Cantidad arbitraria de carros segun el sector
        int t = - sector->average_cars * log( 1 - (double) (rand()%1000)/1000); // Tiempo de espera
        sleep(t);
        struct Vehicle* car = malloc(sizeof(struct Vehicle)); //Inicializamos el automovil
        car->direction = sector->side;
        car->plate = plates++;
        car->speed = sector->min_velocity_cars + rand() % (sector->max_velocity_cars + 1 - sector->min_velocity_cars);
        car->priority = (10 - sector->ambulance_probability <= rand() % 11)? 1: 0;
        pthread_create(&arr[i],NULL, start_tour, car);//Automovil inicial el recorrido
    }
    pthread_exit(0);
}

void run_simulation(){
    pthread_t mod; //Inician los semaforos o oficiales
    switch (modality){
        case 2: pthread_create(&mod, NULL, semaphore, NULL); break;
        case 3: pthread_create(&mod, NULL, officers, NULL); break;
        default: break;
    }
  /*   pthread_t east; //Inician los automoviles
    int* side_east = malloc(sizeof(int*));
    *side_east = 1;
    pthread_create(&east, NULL, start_rutine, side_east); */
    pthread_t west;
    int side_west = 0;
    pthread_create(&west, NULL, start_rutine, &side_west);
    pthread_t show;
    pthread_create(&show, NULL, show_simulation, NULL);
    //Esperar que los arreglos terminen
/*     pthread_join(east, NULL); */
    pthread_join(west, NULL);
    for (int i = 0; i < cant_cars; i++){
        pthread_join(threads_east[i], NULL);
        //pthread_join(threads_west[i], NULL);
    }
    for(int i = 0; i < lenght; i++){
        pthread_mutex_destroy(&semaphores[i]);
        free(bridge[i]);
    }
    free(bridge);
    free(semaphores);
    pthread_mutex_destroy(&way_bridge_mutex);
    pthread_mutex_destroy(&emptybridge_mutex);
/*     while(sector_west->finish->first)
        free(dequeue(sector_west->finish));
    free(sector_west->finish);
    while(sector_east->finish->first)
        free(dequeue(sector_east->finish));
    free(sector_east->finish); 
    free(sector_east);
    free(sector_west); */
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
    if(strcmp(section, "modality") == 0 && strcmp(name, "id") == 0){
        if(num == 1 || num == 2 || num == 3){
            modality = num;
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
    plates = 0;
    way_bridge = 0;
    FILE *config = fopen (path, "r");
    if(!config) {
        printf("Settings file does not exist in the path: %s\n", path);
        return 0;
    }
    char line[100];
    char* section = NULL;
    char* name = NULL;
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
            char* value = slide(line, 61, 10);
            num = atoi(value);
            comment = slide(line,35, 10);
            save_setting(section, name, num);    
            printf("\t%s: %d", name, num);
            (comment != NULL)? printf("\tComment: %s\n", comment):printf("\n");
        
        }
    }
    fclose (config);//cerramos el fichero
    printf("\nVerifying that all settings have been loaded . . .\n");
    if(!verify_all_configured()){
        printf("*** Error: One or more variables have no value, the simulation was canceled\n");
        return 0;
    }
    cant_cars = 5;
    threads_east = (pthread_t*) malloc (cant_cars * sizeof(pthread_t*));
    threads_west = (pthread_t*) malloc (cant_cars * sizeof(pthread_t*));
    //Colocamos una semilla aleatoria
    srand(time(NULL));
    //Inicializamos los bloqueos y espacios del puente
    for(int i = 0; i < lenght; i++){
        pthread_mutex_init(&semaphores[i], NULL);
        bridge[i] = NULL;
    } 
    pthread_mutex_init(&way_bridge_mutex, NULL);
    pthread_mutex_init(&emptybridge_mutex, NULL);
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