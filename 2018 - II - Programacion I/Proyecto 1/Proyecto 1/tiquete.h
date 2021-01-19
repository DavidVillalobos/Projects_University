#ifndef TIQUETE_H
#define TIQUETE_H
#include <string>
#include <sstream>
using namespace std;
#include "in_out.h"
#include "pasajero.h"
class tiquete {
private:
	string id, idVuelo, orig_dest, sal_Lleg;
	char col;
	int precio, fil;
	pasajero *pasaj;
public:
	tiquete(string = " ", string = " ", string = " ", string = " ", char = ' ', int = 0, int = 0, pasajero* = NULL);
	string getId();
	string getIdPers();
	string getIdVuelo();
	string getOrig_dest();
	string getSal_Lleg();
	pasajero* getPasajero();
	int getCol();
	int getPrecio();
	char getFil();
	string toString();
	~tiquete();
};
#endif
