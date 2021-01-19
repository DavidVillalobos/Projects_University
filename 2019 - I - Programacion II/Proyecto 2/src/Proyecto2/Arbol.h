#pragma once
#include"Nodo.h"
#include"Arbol.h"
class Arbol {
	Nodo *raiz;
public:
	Arbol(Posicion*,Estrategia*);
	wstring toString();
	Nodo* getMayor();
	Nodo* getRaiz();
	Nodo* buscarNodo(Posicion*);
	~Arbol();
};