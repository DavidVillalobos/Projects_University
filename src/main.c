#include"simulation.h"

int main(int argc , char* argv[]){
    if(argc == 2){
        init_configurations();
        start_program();
        //sleep(atoi(argv[1]));
        return 0;
    }
    printf("Needed argument for the seconds the simulation will last\n");
    return 1;
}