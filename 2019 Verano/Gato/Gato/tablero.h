#ifndef TABLERO_H
#define TABLERO_H
#include "in_out.h"
class tablero {
	string **tab;
public:
	tablero();
	~tablero();
	string getPos(int);
	void setPos(int, string);
	void toString(int,int);
};
#endif
