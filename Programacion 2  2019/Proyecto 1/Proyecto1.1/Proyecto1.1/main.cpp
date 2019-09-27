/*		Universidad Nacional de Costa Rica
		Facultad de Ciencias Exactas y Naturales
		Escuela de Informatica
		Estudiante: Luis David Villalobos Gonzalez
		Fecha: 12/04/2019
		Ciclo: I-2019
*/
#include"Controlador.h"
int main(){
	Controlador* aplicacion = new Controlador();
	aplicacion->iniciarPrograma();
	delete aplicacion;
	return 0;
}
