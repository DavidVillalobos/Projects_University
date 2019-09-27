#ifndef TABLERO_H
#define TABLERO_H
#include <string>
#include "in_out.h"
#include "ficha.h"

using namespace std;

class tablero {
private:
	ficha ***matriz;
public:
	tablero();
	ficha* getFicha(int,int);
	void setFicha(int, int, ficha*);
	void toString(ficha **);
	int casillaPremios(int a, int i);
	bool vacio(int, int);
	~tablero();
};
#endif