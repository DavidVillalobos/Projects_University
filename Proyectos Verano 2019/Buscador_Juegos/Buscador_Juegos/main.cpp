#include <iostream>
using namespace std;
#include "Control.h"
void main() {
	Control *cargar = new Control;
	cargar->cargarArchivos();
	delete cargar;
}