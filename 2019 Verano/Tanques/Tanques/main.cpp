#include <iostream>                         
#include <stdio.h>
#include "juego.h"
int main() {
	juego *tanques = new juego();
	tanques->menus();
	delete tanques;
}