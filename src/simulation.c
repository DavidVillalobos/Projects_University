#include"simulation.h"

// Genera una pared rectangular en los puntos especificados
void build_wall(int x1, int y1, int x2, int y2){
    int j;
    for (int i = y1-1; i < y2; i++){ // Filas    Y
        for (j = x1-1; j < x2; j++){ // Columnas X
            map[i][j].wall = 1;
        }
    }
}

//Inicializar las configuraciones
int init_configurations(){
    // Read configuration files
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
            map[i][j].wall = map[i][j].cant = 0;
            map[i][j].type_agent_infect = -1;
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
            groups[i][j].position[0] = rand() % (map_weight + 1); //X,
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
    for (i = 0; i < 4; i++){
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
            printf("%s", (map[i][j].wall)?"║":" ");
        }
        printf("║\n");
    }
    printf("╚");
    for (i = 0; i < map_weight; i++){
        printf("═");
    }
    printf("╝\n"); 
}