#include"simulation.h"

// Genera una pared rectangular en los puntos especificados
void build_wall(int x1, int y1, int x2, int y2){
    int i,j;
    for (i = y1-1; i < y2; i++){ // Filas    Y
        for (j = x1-1; j < x2; j++){ // Columnas X
            map[i][j].state = 0;
        }
    }
}

int init_configurations(){
    // Configuracion del mapa
    char* path = "../test/map.ini";
    FILE *file = fopen(path, "r");
    if(!file) {
        printf("Map settings file does not exist in the path: %s\n", path);
        return 0;
    } 
    fscanf(file, "%d %d", &map_height, &map_weight); 
    map = (struct boxes_t**) malloc(map_height * sizeof(struct boxes_t*));
    int i,j;
    for(i = 0; i < map_height; i++){
       map[i] = (struct boxes_t*) malloc(map_weight * sizeof(struct boxes_t));
    }
    for (i = 0; i < map_height; i++){
        for (j = 0; j < map_weight; j++){
            map[i][j].cant = 0;
            map[i][j].state = -1;
            pthread_mutex_init(&map[i][j].id , NULL);
        }
    }
    int cant_walls;
    fscanf(file, "%d", &cant_walls);
    int x1, y1, x2, y2;
    for (i = 0; i < cant_walls; i++){
        fscanf(file, "%d %d %d %d", &x1, &y1, &x2, &y2);
        build_wall(x1, y1, x2, y2);
    }
    fclose(file);

    // Configuracion de los agentes
    path = "../test/agent.ini";
    file = fopen(path, "r");
    if(!file){
        printf("Agent settings file does not exist in the path: %s\n", path);
        return 0;
    }
    int tam, type, min, max;
    char state;
    fscanf(file, "%d", &tam);
    tam_groups = (int*) malloc( tam * sizeof(int));
    groups = (struct agent_t**) malloc( tam * sizeof(struct agent_t *));
    for(i = 0; i < tam; i++){
        fscanf(file, "%d", &tam_groups[i]);
        fscanf(file, "%d", &type);
        fscanf(file, "%d %d\n", &min, &max);
        fscanf(file, "%c", &state);
        groups[i] = (struct agent_t*) malloc(tam_groups[i] * sizeof(struct agent_t));
        for (j = 0; j < tam_groups[i]; j++){
            groups[i][j].type = type;
            groups[i][j].state = (state == 's')?1:2;
            groups[i][j].velocity = min + rand() % (max + 1 - min);
            groups[i][j].position[0] = rand() % (map_weight + 1); //X
            groups[i][j].position[1] = rand() % (map_height + 1); //Y
        }
    }
    fclose(file);
    // Configuracion de la enfermedad
    path = "../test/disease.ini";
    file = fopen(path, "r");
    if(!file) {
        printf("Disease settings file does not exist in the path: %s\n", path);
        return 0;
    }
    fscanf(file, "%f", &mortality);
    fscanf(file, "%d", &time_to_die);
    fscanf(file, "%d", &time_to_heal);
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            fscanf(file, "%f", &contagion_rate[i][j]);
        }
    }
    fscanf(file, "%d", &reinfection);
    fclose(file);
    return 0;
}

void print_map(){
    int i,j;
    printf("╔");
    for (i = 0; i < map_weight; i++){
        printf("═");
    }
    printf("╗\n");
    for (i = 0; i < map_height; i++){
        printf("║"); 
        for (j = 0; j < map_weight; j++){
            if(map[i][j].state == 0 || map[i][j].state == -1){
                printf("%s", (map[i][j].state == 0)?"║":" ");
            }else{// 1 Sano, 2 Enfermo, 3 Curado
                if(map[i][j].state == 1){
                    printf("\x1B[32m");    
                }else if(map[i][j].state == 2){
                    printf("\x1B[31m");
                }else{
                    printf("\x1B[34m");
                }
                printf("*\x1B[0m");
            }
        }
        printf("║\n");
    }
    printf("╚");
    for (i = 0; i < map_weight; i++){
        printf("═");
    }
    printf("╝\n"); 
}

//Calcula una recta dados dos puntos, el primer punto es 
//la posicion del agente y el segundo es la nueva posicion
int generarRecta(struct agent_t* agent){
    agent->position[2] = 0; //No es cuadratica
    float x2 = agent->route[0][0]; // Puntos aleatorios en 
    float y2 = agent->route[1][0]; // el borde de la matriz
    if(x2 - agent->position[0] != 0){ // Actualiza los valores M y  B siempre que no implique una recta vertical
        agent->coefficient[1] = (y2 - agent->position[1]) / (x2 - agent->position[0]);
        agent->coefficient[0] = agent->position[1] - agent->coefficient[1] * agent->position[0];
        return 1;
    }
    return 0;
}

//Calcula una curva dados tres puntos, el primer punto es la 
//posicion del agente y los otros son nuevas posiciones de la ruta
int generarCurva(struct agent_t* agent){
    float p1x =  agent->route[0][0];
    float p1y =  agent->route[1][0];
    float p2x =  agent->route[0][1]; 
    float p2y =  agent->route[1][1];
    float p3x =  agent->route[0][2]; 
    float p3y =  agent->route[1][2];
    float r1[3], r2[3], det;
    //+ Generamos sistema de Ecuaciones Lineales
    //*r 1
    r1[0] = p1x*p1x - p2x*p2x; 
    r1[1] = p1x - p2x; 
    r1[2] = p1y - p2y; 
    //*r2
    r2[0] = p2x*p2x - p3x*p3x; 
    r2[1] = p2x - p3x; 
    r2[2] = p2y - p3y;
    //+ Solucion del Sistema de Ecuaciones Lineales
    det = (r1[0] * r2[1]) - (r2[0] * r1[1]);
    if(det == 0) return 0;
    //* a, b, c
    agent->coefficient[2] = ((r2[1] * r1[2]) - (r1[1] * r2[2])) / det;
    agent->coefficient[1] = ((r1[0] * r2[2]) - (r2[0] * r1[2])) / det;
    agent->coefficient[0] = p1y - agent->coefficient[2]*p1x*p1x - agent->coefficient[1]*p1x;
    return 1;
}

//Permite ver el camino generado con la funcion
// hasta n posiciones de un agente

void visualizarRecta(struct agent_t* agent){
    printf("Forma:  f(x) = %0.1f * x + %0.1f\n", agent->coefficient[1] , agent->coefficient[0]);
    int x = agent->position[0];
    float yprev = agent->position[1];
    float y;
    while(1){//seguir ejecutando mientras no choque con algo
        //printf("Funcion:f(%d) = %0.1f * %d + %0.1f\n", x, agent->coefficient[1] , x, agent->coefficient[0]);
        y = x * agent->coefficient[1] + agent->coefficient[0];
        //printf("Resultado Real: f(%d) = %0.1f\n", x, y);
        y = round(y);
        if(1 < fabs(fabs(yprev) - fabs((y)))){// 1 < | y - newY | ? (El salto es de mas de una posicion)
            y = yprev - 1;
            //printf("DOBLE SALTO: Nuevas Posiciones: (x,y) (%d, %0.0f)\n",x, y);
            printf("Posiciones: (x,y) (%d, %0.0f)\n",x, y);
            int auxy = y;
            if( 0 < auxy && auxy < map_height && 0 < x && x < map_weight)
               map[auxy][x].state = agent->state;
            else break;
        }else{
            printf("Posiciones: (x,y) (%d, %0.0f)\n",x, y);
            int auxy = y;
            if( 0 < auxy && auxy < map_height && 0 < x && x < map_weight)
                map[auxy][x].state = agent->state;
            else break;
            x++;
        }
        yprev = y;
    }
}

void visualizarCurva(struct agent_t* agent){
    printf("Forma:  f(x) = %0.1f * (x)^2 + %0.1f * x + %0.1f\n", agent->coefficient[2], agent->coefficient[1] , agent->coefficient[0]);
    int x = agent->position[0];
    //float yprev = agent->position[1];
    float y;
    while(1){//seguir ejecutando mientras no choque con algo
        //printf("Funcion:f(%d) = %0.1f(%d)^2 + %0.1f * %d + %0.1f\n",x, agent->coefficient[2], x, agent->coefficient[1] , x, agent->coefficient[0]);
        y = agent->coefficient[2] * x * x + agent->coefficient[1] * x + agent->coefficient[0];
        //printf("Resultado Real: f(%d) = %0.1f\n", x, y);
        int auxy = round(y);
        printf("Posiciones: (x,y) (%d, %d)\n",x, auxy);
        if( 0 < auxy && auxy < map_height && 0 < x && x < map_weight)
               map[auxy][x].state = agent->state;
        else break;
        //if(1 < fabs(fabs(yprev) - fabs((y)))){// 1 < | y - newY | ? (El salto es de mas de una posicion)
        //    y = yprev - 1;
            //printf("DOBLE SALTO: Nuevas Posiciones: (x,y) (%d, %0.0f)\n",x, y);
            //printf("Posiciones: (x,y) (%d, %0.0f)\n",x, y);
        //}else{
            //printf("Posiciones: (x,y) (%d, %0.0f)\n",x, y);
            x++;
        //}
        //yprev = y;
    }
}

//Genera 7 Puntos por donde debe pasar un estacional
void generarPuntos(struct agent_t* agent){
    for (int i = 0; i < 7; i++){
        agent->route[0][i] = rand() % (map_weight + 1);
        agent->route[1][i] = rand() % (map_height + 1);
    }
    return;
}