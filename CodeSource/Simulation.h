#include <pthread.h> // for threads
#include <stdio.h> // for printf and scanf
#include <math.h> // for log
#include <stdlib.h> // for srand and malloc
#include<string.h> // for strlen
#include"Sector.h"

struct Simulation{
    //vectores de campos del puente
    int *bridge;
    //Seguros para evitar que varios carros 
    //utilicen el mismo espacio del puente
    pthread_mutex_t *semaphores;
    //Seguro para evitar que los semaforos o oficiales
    //utilicen la misma via
    pthread_mutex_t way_bridge;
    int way;//Direccion de la via
    int running; //simulacion encendida o apagada
    int plates;//Numero de autos ('Placas')
    int lenght; //Largo del puente
    int modality; //Modalidad
    struct Sector* east;
    struct Sector* west;
};

/* Utilizado para enviar multiples parametros
   a un metodo con pthread_create */
struct Args{
    struct Simulation* simulation;
    struct Vehicle* vehicle;
    struct Sector* sector;
};

//Inicializa la simulacion
struct Simulation* initialize_simulation();

//Imprime el puente
void show_bridge();

//Imprime la simulacion
void show_simulation();

//Metodo que el Automovil, utiliza para simular que
//Esta recorriendo el puente
void* cross_bridge(void* arg);

//Creador de Vehiculos con la distribucion exponencial
void* activate_car_maker(void* arg);

//Verifica si el puente se encuentra vacio
int empty_bridge(struct Simulation* simulation);

//Modalidad FIFO
void* fifo(void* arg);

//Activador o "Motor" de un semaforo para algun sector
void* activate_semaforo(void* arg);

//Modalidad SEMAFOROS
void* semaphore(void* arg);

//Establece un Oficial para algun sector
void* establish_officer(void* arg);

//Modalidad OFICIALES
void* officer_transit(void *arg);

//Se encarga de esperar que el usuario apague la simulacion
void* user_listener(void* arg);

//Reproduce la simulacion
void run_simulation(struct Simulation* simulation);

//Detiene la simulacion
void stop_simulation();

//Permite obtener un analisis simple, acerca de la simulacion
void show_final_statistics();

//Obtiene un trozo de un char* == (string)
char* slide(char *str, char begin, char finish);

//Compara dos char* (strings) para verificar que son iguales
int compare(char* string_a, char* string_b);

//Registra un variable en el sistema, dependiendo de la seccion y el nombre
void save_setting(struct Simulation* simulation, char* section, char* name, int num, char* comment);

/* Inicializa las configuraciones de la simulacion
   Segun un archivo de configuracion*/
int init_configurations(struct Simulation* simulation, char* path);

//Muestra ayuda al usuario
void show_help();

/*Verifica que todas las configuraciones
  fueron establecidas con algun valor*/
int verify_all_configured(struct Simulation* simulation);

//Verifica que la simulacion este correcta
int verify_modality(struct Simulation* simulation, int argc, char *argv[]);