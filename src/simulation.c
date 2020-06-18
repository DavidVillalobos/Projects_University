#include"simulation.h"

void settings_map(){
    int cant_walls, i, j, k, x1, y1, x2, y2;
    FILE* out = fopen("../out/result.tex", "w"); // Crear archivo
    fprintf(out,"\\documentclass[12pt]{article}\n");
    fprintf(out,"\\usepackage[usenames,dvipsnames]{xcolor}\n");
    fprintf(out,"\\pagecolor{black!80}\n");
    fprintf(out,"\\usepackage{gnuplot-lua-tikz}\n");
    fprintf(out,"\\usepackage[active,tightpage]{preview}\n");
    fprintf(out,"\\PreviewEnvironment{tikzpicture}\n");
    fprintf(out,"\\usepackage[utf8]{inputenc}\n");
    fprintf(out,"\\usepackage{tikz}\n");
    fprintf(out,"\\newcommand{\\sizeball}{0.40}\n");  
    fprintf(out,"\\newcommand{\\paintMap}{\n");
    FILE *file = fopen("../config/map.ini", "r");
    fscanf(file, "%d %d", &map_height, &map_width);//Largo, Ancho
    map = (struct boxes_t**) malloc(map_height * sizeof(struct boxes_t*));
    for(i = 0; i < map_height; i++)
       map[i] = (struct boxes_t*) malloc(map_width * sizeof(struct boxes_t));
    for (i = 0; i < map_height; i++){
        for (j = 0; j < map_width; j++){ // Por cada casilla
            map[i][j].cant = 0; 
            map[i][j].state = -1; // free
            pthread_mutex_init(&map[i][j].lock_state , NULL);
            pthread_mutex_init(&map[i][j].lock_cant , NULL);
        }
    }
    fprintf(out, "\t\\draw[black!70] (0,0) grid (%d, %d);\n",map_width, map_height);
    fprintf(out, "\t\\draw[color=black] (0.1,0.1) rectangle (%2.f,%2.f);\n", map_width-0.1, map_height-0.1);
    fscanf(file, "%d", &cant_walls);// Configuracion paredes
    for (k = 0; k < cant_walls; k++){
        fscanf(file, "%d %d %d %d", &x1, &y1, &x2, &y2);
        if(0 <= x1 && x1 <= map_width && 0 <= x2 && x2 <= map_width && 0 <= y1 && y1 <= map_height && 0 <= y2 && y2 <= map_height){
            for (i = y1; i < y2; i++){ // Filas Y
                for (j = x1; j < x2; j++) // Columnas X
                    map[i][j].state = 0;
            }
            fprintf(out,"\t\\fill[black!86] (%d,%d) rectangle (%d,%d);\n", x1, y1, x2, y2);
        }
    }
    fclose(file);
    fprintf(out,"}\n\\begin{document}\n");
    fclose(out);
    cant_sick = 0;
    pthread_mutex_init(&lock_cant_sick, NULL);
    cant_healthy = 0;
    pthread_mutex_init(&lock_cant_healthy, NULL);
    cant_death = 0;
    pthread_mutex_init(&lock_cant_death, NULL);
    cant_recovered = 0;
    pthread_mutex_init(&lock_cant_recovered, NULL);
    out = fopen("../out/graficDeath.tex", "w");
    fprintf(out, "%%--------------Grafic Death -------------\n");
    fprintf(out, "\\draw[black]plot[smooth] coordinates{");
    fclose(out);
    out = fopen("../out/graficSick.tex", "w");
    fprintf(out, "%%--------------Grafic Sick -------------\n");
    fprintf(out, "\\draw[red]plot[smooth] coordinates{");
    fclose(out);
    out = fopen("../out/graficRecovered.tex", "w");
    fprintf(out, "%%--------------Grafic Recovered --------\n");
    fprintf(out, "\\draw[blue]plot[smooth] coordinates{");
    fclose(out);
    out = fopen("../out/graficHealhty.tex", "w");
    fprintf(out, "%%--------------Grafic Healhty ----------\n");
    fprintf(out, "\\draw[green]plot[smooth] coordinates{");
    fclose(out);
}

void settings_disease(){
    int i, j;
    FILE* file = fopen("../config/disease.ini", "r");
    fscanf(file, "%f", &mortality); //Caracteristicas de la enfermedad
    fscanf(file, "%d", &time_to_die);
    fscanf(file, "%d", &time_to_heal);
    for( i = 0; i < 4; i++){
        for(j = 0; j < 4; j++)
            fscanf(file, "%f", &contagion_rate[i][j]);
    }
    fscanf(file, "%d", &reinfection);
    fclose(file);
}

void settings_agents(){
    int min, max, i, j, k, type;
    char state;
    FILE* file = fopen("../config/agent.ini", "r");
    fscanf(file, "%d", &cant_groups);
    tam_groups = (int*) malloc( cant_groups * sizeof(int)); //Vector que guarda el tamaño de cada grupo
    groups = (struct agent_t***) malloc( cant_groups * sizeof(struct agent_t **));
    for(i = 0; i < cant_groups; i++){
        fscanf(file, "%d", &tam_groups[i]); //Caracteristicas del grupo
        fscanf(file, "%d", &type);
        fscanf(file, "%d %d\n", &min, &max);
        fscanf(file, "%c", &state);
        switch (state){
            case 'm': cant_death +=  tam_groups[i]; k = 0; break;
            case 's': cant_healthy +=  tam_groups[i]; k = 1; break;
            case 'e': cant_sick += tam_groups[i]; k = 2; break;
            case 'r': cant_recovered += tam_groups[i]; k = 3; break;
            default: break;
        }
        groups[i] = (struct agent_t**) malloc(tam_groups[i] * sizeof(struct agent_t*));
        for (j = 0; j < tam_groups[i]; j++){ //Por cada integrante del grupo
            groups[i][j] = (struct agent_t*) malloc(sizeof(struct agent_t));
            groups[i][j]->type = type;
            groups[i][j]->state = k;
            if(max > 0) groups[i][j]->velocity = 20 / (min + rand() % (max + 1 - min)) ; // (rand between min-max)/ k_velocity 
            pthread_mutex_init(&groups[i][j]->lock_state, NULL);
            do{ // Verificar que este dentro del mapa
                groups[i][j]->pos[0] = rand() % map_width; //X
                groups[i][j]->pos[1] = rand() % map_height; //Y
            }while(map[groups[i][j]->pos[1]][groups[i][j]->pos[0]].state == 0);
            if(type == 2){ // Si es estacional, necesita 6 puntos para el recorrido
                groups[i][j]->route[0][i] = groups[i][j]->pos[0];// 1 es la posicion inicial
                groups[i][j]->route[1][i] = groups[i][j]->pos[1];
                // Se necesitan 3 puntos para generar una curva y se debe verificar si puede existir una curva entre ellos
                int aux = 0;
                for (k = 1; k < 7; k += 2){ // 0,1,2  -  2,3,4  -  4,5,6
                    groups[i][j]->r = k-1;
                    do{
                        groups[i][j]->route[0][k] = aux + rand() % (map_width + 1 - aux);
                        //aux++;
                        groups[i][j]->route[1][k] = rand() % map_height;
                        groups[i][j]->route[0][k+1] = aux + rand() % (map_width + 1 - aux);
                        //aux++;
                        groups[i][j]->route[1][k+1] = rand() % map_height;
                    }while(generate_curve(groups[i][j]));
                    map[groups[i][j]->route[1][k]][groups[i][j]->route[0][k]].state = 2;
                    map[groups[i][j]->route[1][k+1]][groups[i][j]->route[0][k+1]].state = 2;
                }
                groups[i][j]->r = 0;
                groups[i][j]->direction = 0;
                generate_curve(groups[i][j]);
            }else if(type == 3 || type ==  1){
                groups[i][j]->route[0][0] = rand() % map_width;
                groups[i][j]->route[1][0] = rand() % map_height;
                generate_straight(groups[i][j]);
            }
            if(k == 2){
                pthread_t timer;
                if(rand() % 101 <= mortality) //Se determina la probabilidad de mortalidad
                    pthread_create(&timer, NULL, death_timer, groups[i][j]); // Inicia el temporizador para morir
                else
                    pthread_create(&timer, NULL, sickness_timer, groups[i][j]); //Inicia el temporizador para sanar
            }           
        }
    }
    cant_agents = cant_death + cant_healthy + cant_sick + cant_recovered;
    fclose(file);
}

void init_configurations(){
    srand(time(NULL)); 
    settings_map(); // Configuracion del mapa
    settings_disease(); // Configuracion de la enfermedad
    settings_agents(); // Configuracion de los agentes
}

void move_agent(struct agent_t* agent){
    switch(agent->type){
        case 1 :  // Recto
            move_straight(agent);
            break;
        case 2 :  //No funciona ... es igual al recto
            move_straight(agent);
            break; 
        case 3 : // Aleatorio
            move_straight(agent); //Si necesita una recta o no puede avanzar, se genera un nuevo punto aleatorio
            if(agent->type == 3 && agent->pos[0] == agent->route[0][0] && agent->pos[1] == agent->route[1][0]){ 
                do{
                    agent->route[0][0] = rand() % map_width;
                    agent->route[1][0] = rand() % map_height;
                }while(generate_straight(agent));
            }
            break;
        default: break; // Estatico o cualquier otro no se mueve
    }
}

void* death_timer(void* arg){
    struct agent_t * agent = (struct agent_t*) arg; 
    sleep(time_to_die);
    pthread_mutex_lock(&agent->lock_state);
    agent->state = 0;
    pthread_mutex_unlock(&agent->lock_state);
    pthread_mutex_lock(&lock_cant_death);
    cant_death++;
    pthread_mutex_unlock(&lock_cant_death);
    pthread_exit(NULL);
}

void* sickness_timer(void* arg){
    struct agent_t * agent = (struct agent_t*) arg; 
    sleep(time_to_heal);
    pthread_mutex_lock(&agent->lock_state);
    agent->state = 3;
    pthread_mutex_unlock(&agent->lock_state);
    pthread_mutex_lock(&lock_cant_recovered);
    cant_recovered++;
    pthread_mutex_unlock(&lock_cant_recovered);
    pthread_exit(NULL);
}

void verify_contagion(struct agent_t* agent){
    if(agent->state ==  2){ // Si es un agente enfermo y la casilla esta sana
        if(pthread_mutex_trylock(&map[agent->pos[1]][agent->pos[0]].lock_state) == 0){
            map[agent->pos[1]][agent->pos[0]].state = agent->type;
            sleep(agent->velocity);
            map[agent->pos[1]][agent->pos[0]].state = -1;
            pthread_mutex_unlock(&map[agent->pos[1]][agent->pos[0]].lock_state);
        } else{//Si esta enfermo y la casilla ya esta infectada por otro enfermo
            for (int i = 0; i < agent->velocity; i++){ // Por cada segundo que estoy en una casilla verfica si ya fue desocupada para infectarla
                if(map[agent->pos[1]][agent->pos[0]].state == -1 && pthread_mutex_trylock(&map[agent->pos[1]][agent->pos[0]].lock_state) == 0){
                    map[agent->pos[1]][agent->pos[0]].state = agent->type; // infectar
                    sleep(agent->velocity - i); // Me espero en la casilla el tiempo que me faltaba
                    map[agent->pos[1]][agent->pos[0]].state = -1;
                    pthread_mutex_unlock(&map[agent->pos[1]][agent->pos[0]].lock_state);
                    break;
                }
                sleep(1);
            }
        }
    }else{ //Si no es un agente enfermo
        if(agent->state == 3 && !reinfection){ // si esta recuperado pero no se puede reinfectar
            sleep(agent->velocity); // Solo debe esperar
        }else{ // si esta sano o recuperado y se puede enfermar
            for (int i = 0; i < agent->velocity; i++){ // Por cada segundo que esta en la casilla
                if(map[agent->pos[1]][agent->pos[0]].state != -1 && map[agent->pos[1]][agent->pos[0]].state != 0){// Se verifica si la casilla no esta sana 
                    // Se obtiene la probabilidad de contagio y se compara con la tabla de contagio
                    float a = rand() % 101;
                    struct boxes_t casilla = map[agent->pos[1]][agent->pos[0]];
                    float b = contagion_rate[agent->type-1][casilla.state-1]; 
                    if (a <= b){
                        pthread_mutex_lock(&lock_cant_sick);
                        cant_sick++;  // Aumentan los enfermos
                        pthread_mutex_unlock(&lock_cant_sick);
                        if(agent->state == 1){ // Si el agente estaba sano
                            pthread_mutex_lock(&lock_cant_healthy);
                            cant_healthy--; //Disminuyen los sanos
                            pthread_mutex_unlock(&lock_cant_healthy);
                        } else if(agent->state == 3){ // Si estaba recuperado
                            pthread_mutex_lock(&lock_cant_recovered);
                            cant_recovered--; // Disminuyen los recuperados
                            pthread_mutex_unlock(&lock_cant_recovered);
                        }
                        agent->state = 2; // Se cambia su estado a enfermo
                        pthread_t timer;
                        float a = rand() % 101;
                        if(a <= mortality) //Se determina la probabilidad de mortalidad
                            pthread_create(&timer, NULL, death_timer, agent); // Inicia el temporizador para morir
                        else
                            pthread_create(&timer, NULL, sickness_timer, agent); //Inicia el temporizador para sanar
                        sleep(agent->velocity - i); // Me espero en la casilla el tiempo que me faltaba
                        break;
                    }
                }
                sleep(1);
            }
        }
    }
}

void* star_agent(void* arg){
    struct agent_t * agent = (struct agent_t*) arg;
    while(agent->state != 0){ // IM ALIVE?
        move_agent(agent); // Desplaza un espacio segun el tipo
        pthread_mutex_lock(&map[agent->pos[1]][agent->pos[0]].lock_cant);
        map[agent->pos[1]][agent->pos[0]].cant++;  //Entrando a la casilla
        pthread_mutex_unlock(&map[agent->pos[1]][agent->pos[0]].lock_cant);
        verify_contagion(agent); // Verifica el contagio segun el tipo
        pthread_mutex_lock(&map[agent->pos[1]][agent->pos[0]].lock_cant);
        map[agent->pos[1]][agent->pos[0]].cant--;  //Saliendo de la casilla
        pthread_mutex_unlock(&map[agent->pos[1]][agent->pos[0]].lock_cant);
    }
    pthread_exit(0);
}

void start_simulation(int sec){
    seconds = sec;
    int i, j;
    for (i = 0; i < cant_groups; i++){ // Inicia cada hilo del agente
        for(j = 0; j < tam_groups[i]; j++)
            pthread_create(&groups[i][j]->thread, NULL, star_agent, groups[i][j]);
    }
    for(i = 0; i < seconds; i++){
        printf("%d/%d\n", i, seconds);
        take_capture(i);
        sleep(1);
    }
    atexit(&free_memory);
}

void free_memory(){
    int i, j;
    char c;
    FILE* out = fopen("../out/result.tex", "a");
    fprintf(out, "\\begin{tikzpicture}\n");
    fprintf(out, "\\draw[color=black!80] (0,0) rectangle (%d, %d);\n", seconds, cant_agents+2);
    fprintf(out, "\\draw[black!70] (2,2) grid (%d, %d);\n", seconds+2, cant_agents+2);
    fprintf(out, "\\gpsetlinewidth{15.00}\n");
    char* file_name[4] = {"../out/graficDeath.tex", "../out/graficSick.tex", "../out/graficRecovered.tex", "../out/graficHealhty.tex"};
    FILE* file;
    for (i = 0; i < 4; i++){
        file = fopen(file_name[i], "r");
        c = fgetc(file); 
        while (c != EOF) {
            fprintf (out, "%c", c); 
            c = fgetc(file); 
        } 
        fprintf(out, "};\n");
        fclose(file);
    }
    fprintf(out, "%%--------------Labels vertical-----------------\n");
    for (i = 0; i <= cant_agents; i++)
        fprintf(out, "\\node[white] at (1 , %d) {%d};\n", i+2, i);
    fprintf(out, "%%--------------Labels horizontal---------------\n");
    for (i = 0; i <= seconds; i++)
    fprintf(out, "\\node[white] at (%d, 1) {%d};\n", i+2, i);
    fprintf(out, "\\draw[color=black, ->] (2, 2)--(2, %f);\n", cant_agents + 2.5);
    fprintf(out, "\\draw[color=black, ->] (1.9, 2)--(%f, 2);\n", seconds + 2.5);
    fprintf(out, "\\gpsetlinewidth{2}\n");
    fprintf(out, "\\node[white, font=\\Large] at (%d, %d) {Distribución de la enfermedad};\n", (seconds+2)/2 + 1, cant_agents+2);
    fprintf(out, "\\node[white, font=\\Large] at (%d,0.1) {Tiempo en segundos};\n", seconds/2);
    fprintf(out, "\\node[white, font=\\Large, rotate=90] at (0, %d) {Cantidad de Agentes};\n", (cant_agents+2)/2);
    fprintf(out, "\\end{tikzpicture}\n");     
    fprintf(out, "\\end{document}\n");
    fclose(out);
    system("cd ../out/ && rm -f graficHealhty.tex graficRecovered.tex graficDeath.tex graficSick.tex");
    system("cd ../out/ && pdflatex result.tex && rm -f result.aux result.log"); // Imprimir en PDF
        for (i = 0; i < cant_groups; i++){
        for(j = 0; j < tam_groups[i]; j++){
            free(groups[i][j]);
        }
        free(groups[i]);
    }
    free(groups);
    free(tam_groups);
}

int generate_straight(struct agent_t* agent){
    if(agent->route[0][0] - agent->pos[0] == 0) return 1;
    agent->coefficient[1] = (float) (agent->route[1][0] - agent->pos[1]) / (agent->route[0][0] - agent->pos[0]);
    agent->coefficient[0] = (float) agent->pos[1] - agent->coefficient[1] * agent->pos[0];
    agent->direction = (agent->pos[0] == agent->route[0][0])? -1 : (agent->pos[0] < agent->route[0][0])? 1 : 0;
    return 0;
}

int generate_curve(struct agent_t* agent){ 
    float p1x =  agent->route[0][agent->r];
    float p1y =  agent->route[1][agent->r];
    float p2x =  agent->route[0][agent->r + 1]; 
    float p2y =  agent->route[1][agent->r + 1];
    float p3x =  agent->route[0][agent->r + 2]; 
    float p3y =  agent->route[1][agent->r + 2];
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
    if(det == 0) return 1;
    //* a, b, c
    agent->coefficient[2] = ((r2[1] * r1[2]) - (r1[1] * r2[2])) / det;
    agent->coefficient[1] = ((r1[0] * r2[2]) - (r2[0] * r1[2])) / det;
    agent->coefficient[0] = p1y - agent->coefficient[2]*p1x*p1x - agent->coefficient[1]*p1x;
    return 0;
}

void move_straight(struct agent_t* agent){
    int x = agent->pos[0];
    (agent->direction)? x++ : x--;
    int y = round(x * agent->coefficient[1] + agent->coefficient[0]);
    if(1 < fabs(fabs(agent->pos[1]) - fabs(y))){ // Si salta dos en y
        // Se mueve un espacio a partir del y anterior segun pendiente
        x = agent->pos[0]; // No avanza en x
        y = agent->pos[1]; 
        (agent->coefficient[1] > 0)? y++ : (agent->coefficient[1] < 0)? y-- : (y = agent->coefficient[0]);
    }
    if(y < 0 || map_height <= y || x < 0 || map_height <= x){
        if(y <= 0 || map_height <= y){
            agent->coefficient[1] = -1/agent->coefficient[1]; 
        }else{
            agent->direction = !(agent->direction); 
        }
    }else{
        agent->pos[0] = x;// Actualizamos la nueva posicion
        agent->pos[1] = y;
    }
}

int move_curve(struct agent_t* agent){
    int x = agent->pos[0];
    int y = agent->pos[1];
     if((x == agent->route[0][6] && y == agent->route[1][6] && !agent->direction)){
        agent->direction = 1;
        return 2; // Si llego al punto final, debe devolverse
    }
    if(x == agent->route[0][0] && y == agent->route[1][0] && agent->direction){
        agent->direction = 0;
        return 2; // Si llego al punto inicial, debe devolverse
    }
    (agent->direction)? x++ : x--;
    y = round(x * x * agent->coefficient[2] + x * agent->coefficient[1] + agent->coefficient[0]);
    if(1 < fabs(fabs(agent->pos[1]) - fabs((y)))){//(El salto es de mas de una posicion)
        y = (agent->pos[1] < y)? agent->pos[1] + 1 : agent->pos[1] - 1;
        x = agent->pos[0];
    }
    if(0 > y || y >= map_height || 0 > x || x >= map_width){ 
        agent->direction = !(agent->direction); // Cambia de direccion 
        return 2;//Si colisiono contra los bordes necesita devolverse
    }
    if(map[y][x].state == 0){
        agent->direction = !(agent->direction); // Cambia de direccion 
        return 2;//Si colisiono contra una pared necesita devolverse
    }
    if(agent->r != 0 && x == agent->route[0][agent->r] && y == agent->route[1][agent->r])
        return 0; // Si llego a un punto, necesita una nueva curva, no debe devolverse
    agent->pos[0] = x;// Actualizamos la nueva posicion
    agent->pos[1] = y;
    return 2; //Si todo esta bien solo avanza
}

void take_capture(int second){
    FILE* out = fopen("../out/result.tex", "a"); // colocar al final del archivo
    fprintf(out, "%%--------------Second %d ---------------------\n", second);
    fprintf(out, "\t\\begin{tikzpicture}\n");
    fprintf(out, "\t\\paintMap\n");
    struct agent_t* a;
    int i,j;
    for (i = 0; i < cant_groups; i++){
        for(j = 0; j < tam_groups[i]; j++){
            a = groups[i][j];
            if(a->state != 0){ // 0 : Muerto
                fprintf(out, "\t\\fill[%s] (%d.5,%d.5) circle (\\sizeball);\n", (a->state == 1)? "green":(a->state == 2)? "red" : "blue!80", a->pos[0], a->pos[1]);
                //map[a->pos[1]][a->pos[0]].state = 1;
            }
        }
    }
    fprintf(out, "\t\\end{tikzpicture}\n");
    fprintf(out, "\\clearpage\n");
    fclose(out);
    // Se guardan los datos para la grafica
    out = fopen("../out/graficDeath.tex", "a");
    fprintf(out, "(%d,%d)", second+2, cant_death+2);
    fclose(out);
    out = fopen("../out/graficSick.tex", "a");
    fprintf(out, "(%d,%d)", second+2, cant_sick+2);
    fclose(out);
    out = fopen("../out/graficRecovered.tex", "a");
    fprintf(out, "(%d,%d)", second+2, cant_recovered+2);
    fclose(out);
    out = fopen("../out/graficHealhty.tex", "a");
    fprintf(out, "(%d,%d)", second+2, cant_healthy+2);
    fclose(out);
}