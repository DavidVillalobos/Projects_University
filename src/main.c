#include"simulation.c"

int main(int argc , char* argv[]){
    // Read files config
    // initializing threads 
    //start simulation
    // print matrix  
    if(argc == 2){
        printf("El programa durara: %s segundos", argv[1]);
        sleep(atoi(argv[1]));
    }
}