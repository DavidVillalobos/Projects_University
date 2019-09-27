#ifndef JUEGO_H
#define JUEGO_H
#include <string>
#include <sstream>
using namespace std;
#include "etiquetas.h"
class juego {
private:
	string nombre;
	string disponibilidad;
	etiquetas *listEtiquetas;
	string descripcion;
	juego *sig;
public:
	juego(string = "indef",string = "indef", etiquetas* = NULL, string ="indef", juego* = NULL);
	string getNombre();
	etiquetas* getListEtiquetas();
	string getDescripcion();
	string getDisponibilidad();
	void setSig(juego*);
	juego* getSig();
	string toStringCompatibles(etiquetas*);
	string toString();
	~juego();
};
#endif