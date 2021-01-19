#ifndef JUGADOR_H
#define JUGADOR_H
#include "in_out.h"
class jugador{
	string nombre;
	int ganada;
	int jugada;
public:
	jugador(string = "indef", int = 0,int = 0);
	string getNombre();
	int getGanada();
	int getJugada();
	~jugador();
};
#endif
