#include"simulation.h"

int init_configurations(){
    srand(time(NULL));
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
    struct point_t point1, point2;
    for (i = 0; i < cant_walls; i++){
        fscanf(file, "%d %d %d %d", &point1.x, &point1.y, &point2.x, &point2.y);
        build_wall(point1, point2);
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
            groups[i][j].position.x = rand() % (map_weight + 1); //X
            groups[i][j].position.y = rand() % (map_height + 1); //Y
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

void start_program(){
    struct agent_t* agent = malloc(sizeof(struct agent_t));
    agent->type = 1;
    agent->state = 2;
    generate_points(agent);
    agent->position.x = rand() % (map_weight + 1);
    agent->position.y = rand() % (map_height + 1);
    if(generate_straight(agent))
        view_straight(agent);
    agent->position.x =  rand() % (map_weight + 1);
    agent->position.y =  rand() % (map_height + 1);
    agent->state = 1;
    generate_points(agent);
    if(generate_curve(agent))
        view_curve(agent);
    print_map();
}

void build_wall(struct point_t p1, struct point_t p2){
    int i,j;
    for (i = p1.y-1; i < p2.y; i++){ // Filas Y
        for (j = p1.x-1; j < p2.x; j++){ // Columnas X
            map[i][j].state = 0;
        }
    }
}

void print_map(){
    int i,j;
    printf("╔");
    for (i = 0; i < map_weight; i++) printf("═");
    printf("╗\n");
    for (i = 0; i < map_height; i++){
        printf("║"); 
        for (j = 0; j < map_weight; j++){
            if(map[i][j].state == 0 || map[i][j].state == -1)
                printf("%s", (map[i][j].state == 0)?"║":" ");
            else
                if(map[i][j].state == 1) printf("\x1B[32m*\x1B[0m");    
                else if(map[i][j].state == 2) printf("\x1B[31m*\x1B[0m");
                else printf("\x1B[34m*\x1B[0m");
        }
        printf("║\n");
    }
    printf("╚");
    for (i = 0; i < map_weight; i++) printf("═");
    printf("╝\n"); 
}

int generate_straight(struct agent_t* agent){
    agent->coefficient[2] = 0; //No es cuadratica
    // Actualiza los valores M y B siempre que no implique una recta vertical
    if(agent->route[0].y - agent->position.x == 0) return 0;
    agent->coefficient[1] = (agent->route[0].y - agent->position.x) / (agent->route->x - agent->position.x);
    agent->coefficient[0] = agent->position.y - agent->coefficient[1] * agent->position.x;
    return 1;
}

int generate_curve(struct agent_t* agent){
    float p1x =  agent->route[0].x;
    float p1y =  agent->route[0].y;
    float p2x =  agent->route[1].x; 
    float p2y =  agent->route[1].y;
    float p3x =  agent->route[2].x; 
    float p3y =  agent->route[2].y;
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

void view_straight(struct agent_t* agent){
    printf("Forma:  f(x) = %0.1f * x + %0.1f\n", agent->coefficient[1] , agent->coefficient[0]);
    int x = agent->position.x;
    float yprev = agent->position.y;
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

void view_curve(struct agent_t* agent){
    printf("Forma:  f(x) = %0.1f * (x)^2 + %0.1f * x + %0.1f\n", agent->coefficient[2], agent->coefficient[1] , agent->coefficient[0]);
    int x = agent->position.x;
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

void generate_points(struct agent_t* agent){
    for (int i = 0; i < 7; i++){
        agent->route[i].x = rand() % (map_weight + 1);
        agent->route[i].y = rand() % (map_height + 1);
    }
    return;
}