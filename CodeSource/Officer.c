#include"Officer.h"

struct Officer* initialize_officer(){
    struct Officer* police = malloc(sizeof(struct Officer));
    police->number = 0;
    police->number_cars_pass = 0;
    return police;
}