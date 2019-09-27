#include "etiquetas.h"
using namespace std;
etiquetas::etiquetas(){primero = actual = NULL;}
void etiquetas::insertarEtiqueta(string info) {primero = new etiqueta(info, primero);}
int etiquetas::porcentajeCompatibles(etiquetas *listBusc) {
		int sum = 0, can = 0;
		actual = primero;
		while (actual != NULL) {
			can++;
			actual = actual->getSig();
		}
		actual = primero;
		etiqueta *auxiliar;
		while (actual != NULL) {
			auxiliar = actual;
			if (listBusc->buscarEtiqueta(actual->getInfo())) {
				sum++;
			}
			actual = auxiliar;
			actual = actual->getSig();
		}
		return sum * 100 / can;
}
string etiquetas::toString() {
	stringstream s;
	actual = primero;
	s << "|";
	while (actual!=NULL) {
		s<<actual->getInfo()<<"|";
		actual = actual->getSig();
	}
	return s.str();
}
bool etiquetas::buscarEtiqueta(string info) {
	actual = primero;
	while (actual != NULL) {
		if (actual->getInfo() == info) {
			return true;
		}
		actual = actual->getSig();
	}
	return false;
}

int etiquetas::cuentaEtiquetas() {
	actual = primero;
	int can = 0;
	while (actual != NULL) {
		can++;
		actual = actual->getSig();
	}
	return can;
}

etiquetas::~etiquetas(){
	while (primero != NULL) {
		actual = primero;
		primero = primero->getSig();
		delete actual;
	}
}
