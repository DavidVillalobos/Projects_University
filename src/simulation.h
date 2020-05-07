#include <pthread.h> // for threads
#include <stdio.h> // for printf and scanf
#include <math.h> // for log
#include <stdlib.h> // for srand and malloc
#include <string.h> // for strlen
#include <unistd.h>

// Agentes
struct agent_t{
    int type; //1 Recto, 2 Estacional, 3 Aleatorio, 4 Estatico
    int state; // 1 Sano, 2 Enfermo, 3 Curado
    int position[2]; // [x, y]
    int velocity;
    pthread_t id;
    int coefficient[3]; // a(x)^2 + b(x) + c
    int* route[2]; // [x,y][7]  Vector 7 puntos solo para Estacional
};

// Posiciones de la matriz
struct boxes_t{
    int wall;
    int cant;
    int type_agent_infect;// -1 no agent
    pthread_mutex_t id;
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

//Simulation
int *tam_groups;//Vector con la cantidad de los grupos
struct agent_t** groups;//Vector de Vectores de agentes(grupos)

// Genera una pared rectangular en los puntos especificados
void build_wall(int x1, int y1, int x2, int y2);

int init_configurations();

void print_map();