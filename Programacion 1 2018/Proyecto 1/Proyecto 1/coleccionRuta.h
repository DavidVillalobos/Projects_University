#ifndef COLECCIONRUTA_H
#define COLECCIONRUTA_H
#include "ruta.h"
#include "in_out.h"
#include <sstream>
class coleccionRuta
{
private:
	ruta **_r;
	int cant, tam;
public:
	coleccionRuta();
	int getCant();
	bool insertarRuta(ruta*);
	bool eliminarRuta(string);
	void toString();
	int buscarRuta(string);
	void muestraRuta(string);
	ruta* getRuta(int);
	~coleccionRuta();
};
#endif