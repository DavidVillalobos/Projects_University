#include <pthread.h> // for threads
#include <stdio.h> // for printf and scanf
#include <math.h> // for log
#include <stdlib.h> // for srand and malloc
#include <string.h> // for strlen
#include <unistd.h>
#include"Sector.h"

//vectores de campos del puente
struct Vehicle** bridge;
//Seguros para evitar que varios carros 
//utilicen el mismo espacio del puente
pthread_mutex_t *semaphores;
/*  Seguro para evitar que los semaforos 
    o oficiales utilicen la via al mismo tiempo  */
pthread_mutex_t way_bridge_mutex;
//Declaracion de la condicion acceder a una variable 
pthread_cond_t way_bridge_cond;
//Seguro para verificar el puente este vacio
pthread_mutex_t emptybridge_mutex;
//Declaracion de la condicion cambiar la via del puente si esta vacio 
pthread_cond_t emptybridge_cond;
int way_bridge;//Direccion de la via
int plates;//Numero de autos ('Placas')
int lenght; //Largo del puente
int modality; //Modalidad
int empty_bridge; //Puente vacio
int ki;
struct Sector* sector_east;
struct Sector* sector_west;
pthread_t *threads_east;
pthread_t *threads_west;
int cant_cars;

//Imprime el puente
void show_bridge();

//Imprime la simulacion
void* show_simulation();

//Metodo que el Automovil, utiliza para simular que
//Esta recorriendo el puente
void cross_bridge(struct Vehicle* car);

/*  Verifica si el puente se encuentra vacio
    De estar vacio pone una bandera en true */
void* verify_bridge();

//Modalidad SEMAFOROS
void* semaphore();

//Modalidad OFICIALES
void* officers();

//Reproduce la simulacion
void run_simulation();

//Detiene la simulacion
void stop_simulation();

//Obtiene un trozo de un char* == (string)
char* slide(char *str, char begin, char finish);

/* Registra un variable en el programa desde el archivo de 
   configuracion dependiendo de la seccion y el nombre */
void save_setting(char* section, char* name, int num);

/* Inicializa las configuraciones de la simulacion
   Segun un archivo de configuracion*/
int init_configurations(char* path);

//Muestra ayuda al usuario
void show_help();

/*Verifica que todas las configuraciones
  fueron establecidas con algun valor*/
int verify_all_configured();

//Verifica que la simulacion este correcta
int verify_modality(int argc, char *argv[]);

void* start_rutine(void* arg);