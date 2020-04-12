#include"Simulation.h"

int main(int argc, char *argv[]){
    char* path = "config.ini";
    if(argc == 2 && compare(argv[1], "help")) show_help();
    if(argc == 2) path = argv[1];
    struct Simulation* simulation = initialize_simulation();
    if(argc == 3){
        simulation->modality = atoi(argv[2]);
        if(!(simulation->modality == 1 || simulation->modality == 2 || simulation->modality == 3)){
            printf("Error: The modality id must be a 1, 2 or 3\n");
            return 0;
        }
        printf("The modality id was established for %d ", simulation->modality);
        printf("according to the parameter received\n");
    }
    if(init_configurations(simulation, path)){
        printf("Configurations loaded correctly, press enter . . . ");
        while(getchar() != '\n'); //Wait enter
        run_simulation(simulation);
        stop_simulation(simulation);
    }
    return 0;
}
