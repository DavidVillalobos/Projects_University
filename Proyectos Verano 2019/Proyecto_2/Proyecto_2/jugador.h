#ifndef JUGADOR_H
#define JUGADOR_H

using namespace std;

#include "palabra.h"
#include "listaPalabras.h"

class jugador {
private:
	string usuario;
	int puntaje, pGanadas;
	palabra* word;
	listaPalabras* lista;
public:
	jugador(string = "-", int = 0, int = 0);
	void setPalabra(palabra*);
	palabra* getPalabra();
	string getUsuario();
	int getPuntaje();
	int getPganadas();
	void setPuntaje(int);
	void setPganadas(int);
	string toString();
	listaPalabras* getLista();
	void setListaPalabras(listaPalabras*);
	~jugador();
};
#endif