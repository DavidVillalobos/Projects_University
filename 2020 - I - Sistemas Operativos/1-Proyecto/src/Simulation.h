#include <pthread.h> // for threads
#include <stdio.h> // for printf and scanf
#include <math.h> // for log
#include <stdlib.h> // for srand and malloc
#include <string.h> // for strlen
#include <unistd.h>
#include"Sector.h"

//vectores de campos del puente
struct Vehicle** bridge; //Unicamente para poder visualizarlos

// Mutex para evitar que varios carros 
// utilicen el mismo espacio del puente
pthread_mutex_t *semaphores;
// Mutex para ir aumentando las matriculas de los autos
pthread_mutex_t plates_mutex;
// Mutex para la cantidad de carros que permite un oficial
pthread_mutex_t ki_oficcers_mutex;

int way_bridge;// Direccion de la via
int plates;// Numero de autos ('Placas')
int lenght; // Largo del puente
int modality; // Id de la Modalidad
int ki; // Funciona como iterador de segundos en el semaforo
// Y cantidad de automoviles que han pasado

// Sectores en ambos sentidos
struct Sector* sector_east;
struct Sector* sector_west;

//Arreglo de Hilos de cada sector
pthread_t *threads_east;
pthread_t *threads_west;

int cant_cars; //Cantidad de carros de la simulacion por cada sector

// Se encarga de mostrar el puente
void show_bridge();

// Se encarga de mostrar la lista de carros que estan por entrar al puente
void show_entrance_bridge(struct Sector* sector);

// Muestra toda la simulacion junta actualizandose cada segundo
void* show_simulation();

/* Permite a un automovil visualizar la direccion del
puente retornando su direccion actual de los carros que lo 
recorren , retorna -1 si esta vacio */
int view_direction_bridge();

// Semaforo que esta cambiado la via cada cantidad de segundos
void* semaphore();

// Oficial que esta cambiando la via por cada cantidad de automoviles
void* officers();

// Verifica las condiciones de un automovil antes de entrar al puente
// para las modalidades
void verify_fifo(struct Vehicle* car, struct Sector* sector);

void verify_semaphore(struct Vehicle* car, struct Sector* sector);

void verify_officers(struct Vehicle* car, struct Sector* sector);

// Simula el recorrido del automovil
void* start_tour(void* arg);

// Recorre el arreglo ejecutando cada hilo
void* start_rutine(void* arg);

//Reproduce la simulacion
void run_simulation();

//Libera la memoria utilizada en el programa
void free_data();

//Obtiene un trozo de un char* = (string)
char* slide(char *str, char begin, char finish);

/* Registra un variable en el programa desde el archivo de 
   configuracion dependiendo de la seccion y el nombre */
void save_setting(char* section, char* name, int num);

/* Inicializa las configuraciones de la simulacion
   Segun un archivo de configuracion*/
int init_configurations(char* path);

//Muestra ayuda al usuario al escribir ./start help
void show_help();

/*Verifica que todas las configuraciones
  fueron establecidas con algun valor*/
int verify_all_configured();