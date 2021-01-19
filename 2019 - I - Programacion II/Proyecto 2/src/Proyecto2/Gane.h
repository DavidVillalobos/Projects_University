#pragma once
#include "Estrategia.h"
class Gane: public Estrategia{
	public:
		Gane();
		int prioridad(Posicion*, wstring, wchar_t);
		~Gane();
};
