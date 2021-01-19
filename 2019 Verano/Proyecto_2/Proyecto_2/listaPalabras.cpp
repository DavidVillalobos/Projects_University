#include "listaPalabras.h"

listaPalabras::listaPalabras() {
	primero = NULL;
	actual = NULL;
}


void listaPalabras::insertarInicio(palabra* p) {
	primero = new nodoPalabra(p, primero);
}


string listaPalabras::toString() {
	actual = primero;
	stringstream s;
	while (actual != NULL)
	{
		s << actual->toStringNodo() << "     VALOR TOTAL: " << actual->getInfo()->getValorTotal();
		actual = actual->getSig();
	}

	return s.str();
}


int listaPalabras::cuentaNodos() {
	actual = primero;
	int can = 0;
	while (actual != NULL)
	{
		can++;
		actual = actual->getSig();
	}
	return can;
}

listaPalabras::~listaPalabras() {
	while (primero != NULL) {
		actual = primero;
		primero = primero->getSig();
		delete actual;
	}
}
//------------------------------------------------------------------------------//

nodoPalabra::nodoPalabra(palabra* p, nodoPalabra* s) {
	info = p;
	sig = s;
}

void nodoPalabra::setInfo(palabra* p) { info = p; }

palabra* nodoPalabra::getInfo() { return info; }

void nodoPalabra::setSig(nodoPalabra* s) { sig = s; }

nodoPalabra* nodoPalabra::getSig() { return sig; }

string nodoPalabra::toStringNodo() {
	return  info->toString();
}

nodoPalabra:: ~nodoPalabra() {
	delete info;
}