#include"simulation.h"

int main(int argc , char* argv[]){
    srand(time(NULL));
    init_configurations();
    struct agent_t* agent = malloc(sizeof(struct agent_t));
    agent->type = 1;
    agent->state = 2;
    //Puntos iniciales
    generarPuntos(agent);
    agent->position[0] = rand() % (map_weight + 1);//Punto aleatorio de inicio
    agent->position[1] = rand() % (map_height + 1);
    if(generarRecta(agent)){
        visualizarRecta(agent);
    }
    agent->position[0] =  rand() % (map_weight + 1);;//Punto aleatorio de inicio
    agent->position[1] =  rand() % (map_height + 1);;
    agent->state = 1;
    generarPuntos(agent);
    if(generarCurva(agent)){
        visualizarCurva(agent);
    }
    // Star_Simulation
    print_map();
     /*
    // print matrix  
    if(argc == 2){
        printf("El programa durara: %s segundos", argv[1]);
        sleep(atoi(argv[1]));
    }//Initialize */
}