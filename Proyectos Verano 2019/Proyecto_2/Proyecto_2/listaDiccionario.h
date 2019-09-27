#ifndef LISTADICCIONARIO_H
#define LISTADICCIONARIO_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class nodoBuscada;

class listaDiccionario
{
private:
	nodoBuscada * primero;
	nodoBuscada * actual;
public:
	listaDiccionario();
	void insertarInicio(string);
	string toString();
	int cuentaNodos();
	~listaDiccionario();
};
//----------------------------------------------------------------

class nodoBuscada
{
private:
	string info;
	nodoBuscada* sig;
public:
	nodoBuscada(string, nodoBuscada*);
	void setInfo(string);
	string getInfo();
	void setSig(nodoBuscada*);
	nodoBuscada* getSig();
	~nodoBuscada();
};
#endif