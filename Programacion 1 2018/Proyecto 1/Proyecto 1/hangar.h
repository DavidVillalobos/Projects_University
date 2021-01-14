#ifndef HANGAR_H
#define HANGAR_H

#include <iostream>
#include "in_out.h"
using namespace std;

#include "avion.h"

class hangar {
private:
	avion *_a[30];
	int cant;
public:
	hangar();
	int getCant();
	int buscarAvion(string);
	void muestraAvion(string);
	bool insertAvion(avion*);
	bool eliminarAvion(string);
	void toString();
	avion *getAvion(int);
	~hangar();
};

#endif