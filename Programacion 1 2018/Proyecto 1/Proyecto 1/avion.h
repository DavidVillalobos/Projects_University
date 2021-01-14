#ifndef AVION_H
#define AVION_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class avion {
private:
	string id, modelo, marca;
	int anno, cantPasajeros, fila, col;
	char tam;
public:
	avion(string = "00000", string = "indef", string = "indef", int = 0, char = 'P');
	void setId(string);
	void setModelo(string);
	void setMarca(string);
	void setAnno(int);
	void setCantPasajeros(int);
	void setFila(int);
	void setCol(int);
	void setTam(char);
	string getId();
	string getModelo();
	string getMarca();
	int getAnno();
	int getCantPasajeros();
	int getFila();
	int getCol();
	char getTam();
	string toString();
	~avion();
};
#endif