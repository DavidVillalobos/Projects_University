#pragma once
#include"Tablero.h"
#include"Movimiento.h"
#include"Aleatoria.h"
#include"Ofensiva.h"
#include"Gane.h"

using namespace std;
class Juego {
private:
	Tablero* tab;
	Movimiento* m;
public:
	Juego();
	void iniciar();
	void comenzarJuego(wstring, bool&);
	void cambiarEstrategia(int);
	bool cargarPartida(wstring, bool&);
	void guardarPartida(wstring, bool&);
	void revisarCoronas();
	void cantFichas(int&, int&);
	bool ganador(wchar_t);
	~Juego();
};