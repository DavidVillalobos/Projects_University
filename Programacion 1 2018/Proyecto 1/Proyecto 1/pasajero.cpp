#include "pasajero.h"

pasajero::pasajero(string nomb, string _id) :nombre(nomb), id(_id) {}

string pasajero::getNombre() { return nombre; }

string pasajero::getId() { return id; }

string pasajero::toString() {
	stringstream s;
	s << "Nombre: " << nombre << "     ID: " << id << endl;
	return s.str();
}

pasajero::~pasajero() {}