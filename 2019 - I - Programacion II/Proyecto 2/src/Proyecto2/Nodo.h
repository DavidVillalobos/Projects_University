#pragma once
#include"Posicion.h"
#include "Estrategia.h"
class Estrategia;
class Nodo {
	Nodo* derechaAdelante;
	Nodo* izquierdaAdelante;
	Nodo* derechaAtras;
	Nodo* izquierdaAtras;
	Posicion* pos;
	int valor;
	wstring ruta;
public:
	Nodo(Posicion*, wstring, wchar_t, Estrategia*);
	~Nodo();
	wstring toString();
	int getValor();
	Nodo* getMayor();
	wstring getRuta();
	Posicion* getPosicion();
	wstring getCasilla();
	Nodo* buscarNodo(Posicion*);
	void setValor(int);
	void caminosBaseDama(wchar_t&, wchar_t&, wchar_t&, wchar_t&, Estrategia*);
	void caminosDiagonalesDama(wchar_t&, wchar_t&, wchar_t&, wchar_t&, Estrategia*);
	void caminoSimpleFicha(wchar_t&, wchar_t&, wchar_t&, wchar_t&, Estrategia*);
	void caminosEspecialesFicha(wchar_t&, wchar_t&, wchar_t&, wchar_t&, Estrategia*);
};