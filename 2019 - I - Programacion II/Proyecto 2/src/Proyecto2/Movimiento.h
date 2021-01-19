#pragma once
#include"Estrategia.h"
#include"Arbol.h"
class Movimiento{
private:
	Estrategia* e;
public:
	Movimiento();
	bool jugadorJuega(int);
	bool pcJuega(int);
	void setEstrategia(Estrategia*);
	bool moverFicha(Posicion*,wstring);
	~Movimiento();
};