#include <pthread.h> // for threads
#include <stdio.h> // for printf and scanf
#include <math.h> // for log
#include <stdlib.h> // for srand and malloc
#include <string.h> // for strlen
#include <unistd.h>

//Punto
struct point_t{
    int x, y;
};

// Agentes
struct agent_t{
    int type; //1 Recto, 2 Estacional, 3 Aleatorio, 4 Estatico
    int state; //* 0 Muerto, 1 Sano, 2 Enfermo, 3 Curado
    pthread_mutex_t mutex; //* Bloqueo para el cambio de estados
    struct point_t position;
    int velocity;
    pthread_t thread;
    float coefficient[3]; //~ a(x)^2 + b(x) + c
    struct point_t route[7]; // Vector de 7 puntos, por donde pasa el Estacional
};

// Posicion de la matriz
struct boxes_t{
    int cant;
    int state; //* -1 (Libre,sana) 0 (Pared) 1, 2, 3, 4
    pthread_mutex_t id; //* Bloqueo para el cambio de estados
};

// Enfermedad
char* name;
float mortality;
int time_to_die;
int time_to_heal;
float contagion_rate[4][4];
int reinfection; //Allow reinfection

// Mapa
int map_weight;
int map_height;
struct boxes_t** map;

//Simulation
int *tam_groups;//Vector con la cantidad de los grupos
struct agent_t** groups;//Vector de Vectores de agentes(grupos)

// Inicializar las configuraciones
int init_configurations();

// Iniciar el programa
void start_program();

// Genera una pared rectangular en los puntos especificados
void build_wall(struct point_t p1, struct point_t p2);

// Pinta el mapa por consola
void print_map();

// Calcula una recta dados dos puntos, el primer punto es 
// la posicion del agente y el segundo es la nueva posicion
int generate_straight(struct agent_t* agent);

// Calcula una curva dados tres puntos, el primer punto es la 
// posicion del agente y los otros son nuevas posiciones de la ruta
int generate_curve(struct agent_t* agent);

// Permite ver la recta generada
void view_straight(struct agent_t* agent);

// Permite ver la curva generada
void view_curve(struct agent_t* agent);

// Genera 7 Puntos por donde debe pasar un estacional
void generate_points(struct agent_t* agent);