#ifndef JUGADORES_H
#define JUGADORES_H
#include <string>
#include <sstream>
using namespace std;
#include "jugador.h"
class jugadores{
private:
	jugador* primero;
	jugador* actual;
public:
	jugadores();
	void insertarPrimero(int, string,string);
	void insertarFinal(int, string,string);
	bool ordenar();
	bool insertarOrdenado(int, string,string);
	int sumaPuntuaciones();
	jugador* buscarEspecifico(string);
	string toString();
	int cuentaNodos();
	jugadores* mejores(int);
	jugadores * list_Puntuaciones(string);
	bool eliminaInicio();
	~jugadores();
};
#endif