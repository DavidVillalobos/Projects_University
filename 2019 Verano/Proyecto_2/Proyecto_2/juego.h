#ifndef JUEGO_H
#define JUEGO_H

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

#include "diccionario.h"
#include "jugador.h"
#include "tablero.h"
#include "in_out.h"

class juego {
private:
	jugador * j1;
	jugador * j2;
	tablero tab;
	ficha* bolsita[27];
	int cant, tamano;
	diccionario* d;
public:
	juego();
	void cargar();
	ficha* GETFICHA(string);
	void menuPrincipal();
	void jugar();
	bool insertarPalabra(jugador*, int, int, bool);
	void premio(jugador*, int, int, int, bool);
	int numpremio(int, int, int &);
	void ejecucion(jugador*, int);
	bool fichasAleatorias(jugador*);
	bool cabe(string, int, int, bool);
	~juego();
};

#endif