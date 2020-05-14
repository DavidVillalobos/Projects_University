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
    pthread_mutex_t mutex;
    int position[2]; // [x, y]
    int velocity;
    pthread_t thread;
    float coefficient[3]; // a(x)^2 + b(x) + c
    int route[2][7]; // [x,y][7]  Vector 7 puntos, por donde pasa el Estacional
};

// Posicion de la matriz
struct boxes_t{
    int cant;
    int state; //* -1(Libre,sana) 0(Pared) 1, 2, 3, 4
    pthread_mutex_t id;
};

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
//Inicializar las configuraciones
int init_configurations();
//Pinta el mapa por consola
void print_map();

int generarRecta(struct agent_t* agent);
int generarCurva(struct agent_t* agent);
void visualizarRecta(struct agent_t* agent);
void visualizarCurva(struct agent_t* agent);
void generarPuntos(struct agent_t* agent);