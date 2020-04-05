#include<pthread.h>
#include<stdlib.h>

//Oficial de Transito, {k, ki}
struct Officer{
    //Numero K de carros que pasan en cada sentido
    int number_cars_pass, number;
    pthread_t tid;
};

struct Officer* initialize_officer();