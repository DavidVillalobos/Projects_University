#include <iostream>
using namespace std;
#include "Control.h"
int main() {
	Control *cargar = new Control;
	cargar->cargarArchivos();
	delete cargar;
}