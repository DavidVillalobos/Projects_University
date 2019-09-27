#pragma once
#include "Estrategia.h"
class Ofensiva : public Estrategia {
public:
	Ofensiva();
	int prioridad(Posicion*, wstring, wchar_t);
	~Ofensiva();
};