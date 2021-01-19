#ifndef LISTAPALABRAS_H
#define LISTAPALABRAS_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "palabra.h"

class nodoPalabra;

class listaPalabras
{
private:
	nodoPalabra * primero;
	nodoPalabra * actual;
public:
	listaPalabras();
	void insertarInicio(palabra*);
	string toString();
	int cuentaNodos();
	~listaPalabras();
};
//----------------------------------------------------------------

class nodoPalabra
{
private:
	palabra * info;
	nodoPalabra* sig;
public:
	nodoPalabra(palabra*, nodoPalabra*);
	void setInfo(palabra*);
	palabra* getInfo();
	void setSig(nodoPalabra*);
	nodoPalabra* getSig();
	string toStringNodo();
	~nodoPalabra();
};
#endif