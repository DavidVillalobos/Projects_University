#include "listaDiccionario.h"

listaDiccionario::listaDiccionario() {
	primero = NULL;
	actual = NULL;
}

void listaDiccionario::insertarInicio(string palB) {
	primero = new nodoBuscada(palB, primero);
}


string listaDiccionario::toString() {
	actual = primero;
	stringstream s;
	while (actual != NULL)
	{
		s << actual->getInfo();
		s << endl;
		actual = actual->getSig();
	}
	return s.str();
}


int listaDiccionario::cuentaNodos() {
	actual = primero;
	int can = 0;
	while (actual != NULL)
	{
		can++;
		actual = actual->getSig();
	}
	return can;
}

listaDiccionario::~listaDiccionario() {
	while (primero != NULL) {
		actual = primero;
		primero = primero->getSig();
		delete actual;
	}
}



//------------------------------------------------------------------------------//

nodoBuscada::nodoBuscada(string palB, nodoBuscada* s) {
	info = palB;
	sig = s;
}

void nodoBuscada::setInfo(string pB) { info = pB; }

string nodoBuscada::getInfo() { return info; }

void nodoBuscada::setSig(nodoBuscada* s) { sig = s; }

nodoBuscada* nodoBuscada::getSig() { return sig; }

nodoBuscada:: ~nodoBuscada() {}