#ifndef FICHA_H
#define FICHA_H
#include "in_out.h"

class ficha {
private:
	string letra;
	int valor, total, disponibles;
public:
	ficha(string = "-", int = 0, int = 0, int = 0);
	void setLetra(string);
	void setValor(int);
	void setTotal(int);
	void setDisponibles(int);
	string getLetra();
	int getValor();
	int getTotal();
	int getDisponibles();
	string toString();
	~ficha();
};
#endif