#pragma once
#include"Tablero.h"
class Estrategia {
public:
	Estrategia();
	virtual int prioridad(Posicion*, wstring, wchar_t) = 0;
	virtual ~Estrategia();
};