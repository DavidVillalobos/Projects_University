#pragma once
#include"In_Out.h"
#include "Posicion.h"
class Tablero {
private:
	Posicion *tab[8][8];
	static Tablero* _tablero;
	Tablero();
	static void destruirTablero();
public:
	static Tablero* tablero();
	~Tablero();
	void moverFicha(Posicion*,Posicion*);
	void colocarFicha(wchar_t,int,int);
	wchar_t getSimbolo(int, int);
	Posicion* getPosicion(int, int);
	Posicion * puedoDerechaAdelante(Posicion*);
	Posicion * puedoIzquierdaAdelante(Posicion*);
	Posicion * puedoDerechaAtras(Posicion*);
	Posicion * puedoIzquierdaAtras(Posicion*);
	void toString();
	void predeterminado();
	void vaciarTablero();
};