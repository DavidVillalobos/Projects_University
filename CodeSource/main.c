#include"Simulation.h"

int main(int argc, char *argv[]){
    char* path = "config.ini";
    if(argc == 2 && compare(argv[1], "help")) show_help();
    if(argc == 2) path = argv[1];
    if(init_configurations(path)){
        if(argc == 3){
            simulation->modality = atoi(argv[2]);
            if(!(simulation->modality == 1 || simulation->modality == 2 || simulation->modality == 3)){
                printf("Error: The modality id must be a 1, 2 or 3\n");
                return 1;
            }
            printf("The modality id was update for %d ", simulation->modality);
            printf("according to the second parameter received\n");
        }else if(simulation->modality == -1){
            printf("Choose one mode of simulation\n");
            printf("\t1) FIFO\n");
            printf("\t2) Semaphores\n");
            printf("\t3) Transit officers \n");
            int value = 0;
            printf("Enter a value: ");
            scanf("%d", &value);
            simulation->modality = value;
            if(!(simulation->modality == 1 || simulation->modality == 2 || simulation->modality == 3)){
                printf("Error: The modality id must be a 1, 2 or 3\n");
                return 1;
            }
        }
        printf("Configurations loaded correctly, press enter . . . ");
        while ( getchar() != '\n'); //Wait enter
        play_simulation();
        stop_simulation();
    }
    
    return 0;
}
