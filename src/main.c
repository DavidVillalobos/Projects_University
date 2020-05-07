#include"simulation.h"

int main(int argc , char* argv[]){
    init_configurations();
    // initializing threads 
    //start simulation
    // print matrix  
    print_map();
    if(argc == 2){
        printf("El programa durara: %s segundos", argv[1]);
        sleep(atoi(argv[1]));
    }
}