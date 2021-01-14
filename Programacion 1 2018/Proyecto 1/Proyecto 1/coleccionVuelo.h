#ifndef COLECCIONVUELO_H
#define COLECCIONVUELO_H

#include <iostream>
#include <string>
#include <sstream>
#include "tiquete.h"
#include "in_out.h"
#include "vuelo.h"
using namespace std;


class coleccionVuelo {
private:
	vuelo **v;
	int tam, cant;
public:
	coleccionVuelo();
	bool insertarVuelo(vuelo*);
	int buscarVuelo(string);
	void mostrarVuelo(string);
	bool eliminarVuelo(string);
	vuelo* getVuelo(int);
	void toString();
	~coleccionVuelo();
};
#endif