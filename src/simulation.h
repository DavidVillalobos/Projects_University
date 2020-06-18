#include <pthread.h> // for threads
#include <stdio.h> // for printf and scanf
#include <math.h> // for log
#include <stdlib.h> // for srand and malloc
#include <string.h> // for strlen
#include <unistd.h>

// Agentes
struct agent_t{
    int type; //1 Recto, 2 Estacional, 3 Aleatorio, 4 Estatico
    int state; //* 0 Muerto, 1 Sano, 2 Enfermo, 3 Curado
    pthread_mutex_t lock_state; //* Bloqueo para el cambio de estados
    int pos[2]; // [0]x,  y[1]
    int velocity;
    pthread_t thread;
    float coefficient[3]; //~ a(x)^2 + b(x) + c
    int route[2][7]; // Vector de 7 puntos, por donde pasa el Estacional
    int r; //Auxiliar de movimiento
    int direction; // 1 Derecha(x++), 0 Izquierda(x--)
};

// Posicion de la matriz
struct boxes_t{
   int cant;
   int state; //* -1 (Libre,sana) 0 (Pared) 1, 2, 3, 4
   pthread_mutex_t lock_state; // Bloqueo para el cambio de estados
   pthread_mutex_t lock_cant; // Bloqueo para la cantidad
}; 

// Enfermedad
char* name;
float mortality;
int time_to_die;
int time_to_heal;
float contagion_rate[4][4];
int reinfection; //Allow reinfection
int cant_sick;
pthread_mutex_t lock_cant_sick;
int cant_healthy;
pthread_mutex_t lock_cant_healthy;
int cant_death;
pthread_mutex_t lock_cant_death;
int cant_recovered;
pthread_mutex_t lock_cant_recovered;

// Mapa
int map_width;
int map_height;
struct boxes_t** map;

//Simulation
int cant_agents;
int cant_groups; // cantidad de grupos
int *tam_groups;//Vector con la cantidad de los grupos
struct agent_t*** groups;//Vector de Vectores de agentes* (grupos)
int seconds;
// Configuracion del mapa
void settings_map();
// Configuracion de la enfermedad
void settings_disease();
// Configuracion de los agentes
void configuration_agents();

// Inicializar las configuraciones
void init_configurations();

//Inicial el hilo del agente
void* star_agent(void*);

// Iniciar el programa durante n segundos
void start_simulation(int);

// libera la memoria utilizada
void free_memory();

// Genera una pared rectangular en los puntos especificados
void build_wall(int x1, int y1, int x2, int y2);

// Pinta el mapa por consola
void print();

// Verifica el contagio en la casilla que se encuentra
void verify_contagion(struct agent_t*);

// Calcula una recta dados dos puntos
int generate_straight(struct agent_t*);

// Calcula una curva dados tres puntos
int generate_curve(struct agent_t*);

//Avanza un espacio segun la recta generada
void move_straight(struct agent_t*);

//Avanza un espacio segun la curva generada
int move_curve(struct agent_t* agent);

// Guarda una captura de la simulacion
void take_capture(int); //Recibe el segundo por el que va

//Temporizador para morir
void* death_timer(void* arg);

//Temporizador para sanar
void* sickness_timer(void* arg);