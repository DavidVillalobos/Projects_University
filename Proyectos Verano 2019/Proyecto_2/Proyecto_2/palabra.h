#ifndef PALABRA_H
#define PALABRA_H
#include "ficha.h"
class palabra {
private:
	string laPalabra;
	int valorSimple, valorTotal, bonos, cant, tamano;
	ficha* vFichas[13];
public:
	palabra();
	int sumaFichasRest();
	void setValorSimple(int);
	void setValorTotal(int);
	void setBonos(int);
	void setCant(int);
	void setLaPalabra(string);
	string getLaPalabra();
	int getValorSimple();
	int getValorTotal();
	int getBonos();
	int getCant();
	void insertarFicha(ficha*);
	int buscarLetra(string);
	ficha* getFicha(int);
	void eliminarFicha(int);
	string toString();
	~palabra();
};
#endif