#include"Simulation.h"

int main(int argc, char *argv[]){
    char* path = "config.ini";
    if(argc == 2) path = argv[1];
    //Inicializamos las configuraciones
    if(initConfigurations(path)){
        playSimulation();//Iniciamos Simulacion
        stopSimulation();//Detenemos Simulacion
    }else{
        printf("Ocurrio algun error al cargar las configuraciones\n");
    }
}