#include <stdio.h> // for printf and scanf
#include <pthread.h> // for threads
#include <math.h> // for log
#include <unistd.h>// for sleep
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
    int num_cars;//Numero de autos ('Placas')
    int lenght; //Largo del puente
    int modality; //Modalidad
    struct Sector* east;
    struct Sector* west;
};

struct Simulation* simulation;

//Inicializa la simulacion
struct Simulation* initialize_simulation();

//Imprime el puente
void printBridge();

//Imprime la simulacion
void printSimulacion();

//Metodo que el Automovil, utiliza para simular que
//Esta recorriendo el puente
void* cross_bridge(void* arg);

//Creador de Vehiculos con la distribucion exponencial
void* activatecarMaker(void* arg);

//Verifica si el puente se encuentra vacio
int emptyBridge();

//Modalidad FIFO
void* fifo(void* arg);

//Temporizador de los semaforos
void* timer(void* arg);

//Activador o "Motor" de un semaforo para algun sector
void* activateSemaphore(void* arg);

//Modalidad Semaforos
void* semaphore(void* arg);

//Establece un Oficial para algun sector
void* establishofficer(void* arg);

//Modalidad Oficial de transito
void* officerTransit(void *arg);

//Se encarga de escuchar las peticiones del usuario
void* userListener(void* arg);

//Reproduce la simulacion
void playSimulation();

//Obtiene un trozo de un char* == (string)
char* slide(char *str, char begin, char finish);

//Compara dos char* (strings) para verificar que son iguales
int compare(char* string_a, char* string_b);

//Registra un variable en el sistema, dependiendo de la seccion y el nombre
void saveVariableSetting(char* section, char* name, int num, char* comment);

//Inicializa las configuraciones de la simulacion
//Segun un archivo de configuracion
int initConfigurations(char* path);

//Detiene la simulacion
void stopSimulation();