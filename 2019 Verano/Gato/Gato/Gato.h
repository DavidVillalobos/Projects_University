#ifndef GATO_H
#define GATO_H
#include "in_out.h"
#include "tablero.h"
#include "jugador.h"
class Gato{
	tablero *tab;
	jugador *j1;
	jugador *j2;
public:
	Gato();
	int revisar_Primero(string marca);
	int revisar_Centro(string marca);
	int revisar_Ultimo(string marca);
	bool Ganador_Horizontal();
	bool Ganador_Vertical();
	bool Ganador_Diagonal();
	int priorizar(string marca);
	~Gato();
	void jugar();
	int jugar_IA_Facil(string, string);
	int jugar_IA_Normal(string, string);
	int jugar_IA_Dificil(string, string);
};
#endif