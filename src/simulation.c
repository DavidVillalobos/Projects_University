#include <pthread.h> // for threads
#include <stdio.h> // for printf and scanf
#include <math.h> // for log
#include <stdlib.h> // for srand and malloc
#include <string.h> // for strlen
#include <unistd.h>

// Agentes
struct agent_t{
    int type;
    int state;
    int position[2];
    int velocity;
    pthread_t id;
    int coefficient[3];
    int* way[2];
};

// Posiciones de la matriz
struct boxes_t{
    int wall;
    int cant;
    pthread_mutex_t id;
    int type_agent_infect;// -1 no agent
};  //¿Que pasa si hay mas de un agente infectado por casilla?
//    1) Se n-plica el porcentaje de contagio
//    2) Se utiliza el ultimo que entro 

//const int K_VELOCITY = 20;

// Enfermedad
char* name;
float mortality;
int time_to_die;
int time_to_heal;
float contagion_rate[4][4];
int reinfection;

// Mapa
int map_weight;
int map_height;
struct boxes_t** map;
/*
//Simulation
struct queue_t* groups;

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
    if(strcmp(section, "agents") == 0){
        if(strcmp(name, "name") == 0){
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
    //sector_west = initialize_sector(0);
    //sector_east = initialize_sector(1);
    //lenght = -1;
   // modality = -1;
    //plates = 1;
    //way_bridge = 1;
    //cant_cars = 20;
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
} */