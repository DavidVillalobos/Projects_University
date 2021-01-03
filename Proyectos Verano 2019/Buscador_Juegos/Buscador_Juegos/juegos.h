#ifndef JUEGOS_H
#define JUEGOS_H
#include"juego.h"
#include"etiquetas.h"

class juegos {
private:
	juego *primero;
	juego *actual;
public:
	juegos();
	void insertarJuego(string,string, etiquetas *, string );
	bool insertarJuegoOrdenado(juego*, etiquetas*);
	void limitarLista(int);
	bool eliminarFinal();
	juegos* lista_Juegos_Compatibles(etiquetas*);
	int cuentaJuegos();
	string toStringCompatibles(etiquetas*);
	string toString();
	juego * buscarJuego(string);
	~juegos();
};
#endif