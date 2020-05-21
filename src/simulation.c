#include"simulation.h"

int init_configurations(){
    srand(time(NULL)); // Configuracion del mapa
    int cant_walls, type, min, max, i,j,k;
    char state; // Creacion del archivo resultante
    FILE* out = fopen("../out/result.tex", "w"); // Crear archivo
    fprintf(out,"\\documentclass[12pt]{article}\n");
    fprintf(out,"\\usepackage[usenames,dvipsnames]{xcolor}\n");
    fprintf(out,"\\pagecolor{black}\n");
    fprintf(out,"\\usepackage[lmargin=0.1cm,rmargin=0cm,top=0.55cm,bottom=0cm]{geometry}\n");
    fprintf(out,"\\usepackage[utf8]{inputenc}\n");
    fprintf(out,"\\usepackage[T1]{fontenc}\n");
    fprintf(out,"\\usepackage{tikz}\n");
    fprintf(out,"\\newcommand{\\sizeball}{0.40}\n");  
    fprintf(out,"\\newcommand{\\paintMap}{\n");
    FILE *file = fopen("../config/map.ini", "r");
    fscanf(file, "%d %d", &map_height, &map_weight);//Largo, Ancho
    map = (struct boxes_t**) malloc(map_height * sizeof(struct boxes_t*));
    for(i = 0; i < map_height; i++)
       map[i] = (struct boxes_t*) malloc(map_weight * sizeof(struct boxes_t));
    for (i = 0; i < map_height; i++){
        for (j = 0; j < map_weight; j++){
            map[i][j].cant = 0; // Cada casilla
            map[i][j].state = -1;
            pthread_mutex_init(&map[i][j].id , NULL);
        }
    }
    fprintf(out, "\t\\draw[black!93] (0,0) grid (%d, %d);\n",map_weight, map_height);
    // Configuracion paredes
    fscanf(file, "%d", &cant_walls);
    int x1, y1, x2, y2;
    for (k = 0; k < cant_walls; k++){
        fscanf(file, "%d %d %d %d", &x1, &y1, &x2, &y2);
        if(0 <= x1 && x1 <= map_weight && 0 <= x2 && x2 <= map_weight && 0 <= y1 && y1 <= map_height && 0 <= y2 && y2 <= map_height){
            for (i = y1; i < y2; i++){ // Filas Y
                for (j = x1; j < x2; j++) // Columnas X
                    map[i][j].state = 0;
            }
            fprintf(out,"\t\\fill[Brown!70] (%d,%d) rectangle (%d,%d);\n", x1, y1, x2, y2);
        }
    }
    fclose(file);
    fprintf(out,"}\n\\begin{document}\n");
    fclose(out);
    // Configuracion de los agentes
    file = fopen("../config/agent.ini", "r");
    fscanf(file, "%d", &cant_groups);
    tam_groups = (int*) malloc( cant_groups * sizeof(int)); //Vector que guarda el tamaño de cada grupo
    groups = (struct agent_t**) malloc( cant_groups * sizeof(struct agent_t *));
    for(i = 0; i < cant_groups; i++){
        fscanf(file, "%d", &tam_groups[i]); //Caracteristicas del grupo
        fscanf(file, "%d", &type);
        fscanf(file, "%d %d\n", &min, &max);
        fscanf(file, "%c", &state);
        groups[i] = (struct agent_t*) malloc(tam_groups[i] * sizeof(struct agent_t));
        for (j = 0; j < tam_groups[i]; j++){ //Por cada integrante del grupo
            groups[i][j].type = type;
            groups[i][j].state = (state == 's')? 1 : 2;
            groups[i][j].velocity = min + rand() % (max + 1 - min);
            do{ // Dentro del cuadro
                groups[i][j].position[0] = rand() % map_weight; //X
                groups[i][j].position[1] = rand() % map_height; //Y
            }while(map[groups[i][j].position[1]][groups[i][j].position[0]].state == 0);
        }
    }
    fclose(file);
    // Configuracion de la enfermedad
    file = fopen("../config/disease.ini", "r");
    fscanf(file, "%f", &mortality); //Caracteristicas de la enfermedad
    fscanf(file, "%d", &time_to_die);
    fscanf(file, "%d", &time_to_heal);
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++)
            fscanf(file, "%f", &contagion_rate[i][j]);
    }
    fscanf(file, "%d", &reinfection);
    fclose(file);
    return 0;
}

void start_program(){
    struct agent_t* agent = malloc(sizeof(struct agent_t));
    agent->type = 1;
    agent->state = 3;
    generate_points(agent);
    agent->position[0] = rand() % (map_weight + 1);
    agent->position[1] = rand() % (map_height + 1);
    if(generate_straight(agent))
        view_straight(agent);
    generate_points(agent);
    if(generate_curve(agent))
        view_curve(agent);
    print_map();// for console
    take_capture(); // for video

    FILE* out = fopen("../out/result.tex", "a"); // colocar al final del archivo
    fprintf(out, "\\end{document}");
    fclose(out);
    //create_video();
}

void print_map(){
    int i,j;
    struct agent_t a;
     for (i = 0; i < cant_groups; i++){
        for(j = 0; j < tam_groups[i]; j++){
            a = groups[i][j];
            if(a.state != 0) // 0 : Muerto
                map[a.position[1]][a.position[0]].state = a.state;
        }
    }
    printf("╔");
    for (i = 0; i < map_weight; i++) printf("═");
    printf("╗\n");
    for (i = map_height-1; 0 <= i ; i--){
        printf("║"); 
        for (j = 0; j < map_weight; j++){
            if(map[i][j].state == 0 || map[i][j].state == -1)
                printf("%s", (map[i][j].state == 0)?"X":" ");
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
    agent->coefficient[2] = 0; //Indica que no es cuadratica
    if(agent->route[0][0] - agent->position[0] == 0) return 0;
    agent->coefficient[1] = (agent->route[1][0] - agent->position[1]) / (agent->route[0][0] - agent->position[0]);
    agent->coefficient[0] = agent->position[1] - agent->coefficient[1] * agent->position[0];
    return 1;
}

int generate_curve(struct agent_t* agent){ 
    float p1x =  agent->route[0][0];
    float p1y =  agent->route[1][0];
    agent->position[0] = p1x;
    agent->position[1] = p1y;
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

void view_straight(struct agent_t* agent){
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

void view_curve(struct agent_t* agent){
    printf("Forma:  f(x) = %0.1f * (x)² + %0.1f * x + %0.1f\n", agent->coefficient[2], agent->coefficient[1] , agent->coefficient[0]);
    int x = agent->position[0];
    float yprev = agent->position[1];
    float y;
    while(1){//seguir ejecutando mientras no choque con algo
        //printf("Funcion:f(%d) = %0.1f * (%d)² +  %0.1f * %d + %0.1f\n", x, agent->coefficient[2], x, agent->coefficient[1] , x, agent->coefficient[0]);
        y = x * x * agent->coefficient[2] + x * agent->coefficient[1] + agent->coefficient[0];
        //printf("Resultado Real: f(%d) = %0.1f\n", x, y);
        y = round(y);
        if(1 < fabs(fabs(yprev) - fabs((y)))){// 1 < | y - newY | ? (El salto es de mas de una posicion)
            y = (yprev < y)? yprev + 1 : yprev - 1; 
            //Creciente? Aumente uno en altura : Disminuya uno en altura
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

void generate_points(struct agent_t* agent){
    for (int i = 0; i < 7; i++){
        agent->route[0][i] = rand() % (map_weight + 1);
        agent->route[1][i] = rand() % (map_height + 1);
    }
    return;
}

void take_capture(){
    FILE* out = fopen("../out/result.tex", "a"); // colocar al final del archivo
    fprintf(out, "\\resizebox{20.2cm}{27cm}{\n");
    fprintf(out, "\t\\begin{tikzpicture}\n");
    fprintf(out, "\t\\paintMap\n");
    struct agent_t a;
    int i,j;
    for (i = 0; i < cant_groups; i++)
    {
        for(j = 0; j < tam_groups[i]; j++)
        {
            a = groups[i][j];
            if(a.state != 0) // 0 : Muerto
                fprintf(out, "\t\\fill[%s] (%d.5,%d.5) circle (\\sizeball);\n", (a.state == 1)? "green":(a.state == 2)? "red" : "blue!80", a.position[0], a.position[1]);
        }
        
    }
    fprintf(out, "\t\\end{tikzpicture}\n}\n");
    fprintf(out, "\\clearpage\n");
    fclose(out);
}

/*
void create_video(){
    system("cd ../out/ && pdflatex result.tex"); // tex to pdf
    system("cd ../out/ && sudo sed -i 's#<policy domain=\"coder\" rights=\"none\" pattern=\"PDF\" />#<policy domain=\"coder\" rights=\"read|write\" pattern=\"PDF\" />#' /etc/ImageMagick-6/policy.xml"); // allow edit pdf
    system("cd ../out/ && convert -density 400 result.pdf picture.png"); // pdf to png's
    system("ffmpeg -r 1/2 -i picture-%01d.png -c:v libx264 -r 5 -pix_fmt yuv420p output.mp4"); // png's to mp4
    system("mplayer ../out/output.mp4"); // play mp4
}
*/