#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

#include "listaDiccionario.h"

class diccionario {
private:
	listaDiccionario * lista;
public:
	diccionario();
	listaDiccionario* getLista();
	bool buscarPalabra(string);
	~diccionario();
};

#endif