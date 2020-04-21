#include"Simulation.h"

int main(int argc, char *argv[]){
    char* path = "../test/config.ini";
    if(argc == 2 && strstr(argv[1], "help")){
        show_help(); 
        return 0;
    }
    if(1 < argc) path = argv[1];
    if(init_configurations(path)){
        if(argc == 3){
            modality = atoi(argv[2]);
            if(!(modality == 1 || modality == 2 || modality == 3)){
                printf("Error: The modality id must be a 1, 2 or 3\n");
                show_help();
                return 0;
            }
            printf("The modality id was established for %d ", modality);
            printf("according to the parameter received\n");
        }
        printf("Configurations loaded correctly, press enter . . . ");
        while(getchar() != '\n'); //Wait enter
        run_simulation(); // Iniciar
    }
    return 0;
}
