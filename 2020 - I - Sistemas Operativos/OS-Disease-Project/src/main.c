#include"simulation.h"

int main(int argc , char* argv[]){
    if(argc == 1){
        printf("A second argument is needed for the seconds the simulation will last\n");
        return 1;
    }
    init_configurations();
    start_simulation(atoi(argv[1]));
    return 0;
}