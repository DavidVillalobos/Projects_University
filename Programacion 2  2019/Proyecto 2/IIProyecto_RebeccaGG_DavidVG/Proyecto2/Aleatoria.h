#pragma once
#include "Estrategia.h"
class Aleatoria : public Estrategia{
	public:
		Aleatoria();
		int prioridad(Posicion*, wstring, wchar_t);
		~Aleatoria();
};