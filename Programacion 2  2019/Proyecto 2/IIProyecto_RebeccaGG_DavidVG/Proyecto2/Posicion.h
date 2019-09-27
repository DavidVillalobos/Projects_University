#pragma once
#include"Ficha.h"
class Posicion {
private:
	Ficha *ptr;
	int fil, col;
public:
	Posicion(int = 0, int = 0);
	~Posicion();
	void setFicha(Posicion * ptr);
	void crearFicha(wchar_t);
	void eliminarFicha();
	int getFila();
	int getColumna();
	wchar_t getSimbolo();
};