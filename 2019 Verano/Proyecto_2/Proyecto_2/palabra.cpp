#include "palabra.h"

palabra::palabra() {
	cant = 0, tamano = 7, valorSimple = 0, valorTotal = 0, bonos = 0;
	for (int i = 0; i < tamano; i++) {
		vFichas[i] = NULL;
	}
}

int palabra::sumaFichasRest() {
	int suma = 0;
	for (int i = 0; i < cant; i++) {
		suma = suma + vFichas[i]->getValor();
	}
	return suma;
}

void palabra::setLaPalabra(string p) { laPalabra = p; }

void palabra::setValorSimple(int vS) { valorSimple = vS; }

void palabra::setValorTotal(int vT) { valorTotal = vT; }

void palabra::setBonos(int b) { bonos = b; }

void palabra::setCant(int cant) { this->cant = cant; }

string palabra::getLaPalabra() { return laPalabra; }

int palabra::getValorSimple() { return valorSimple; }

int palabra::getValorTotal() { return valorTotal; }

int palabra::getBonos() { return bonos; }

int palabra::getCant() { return cant; }

void palabra::insertarFicha(ficha* f) {
	if (cant < tamano) {
		vFichas[cant] = f;
		cant++;
	}
}

int palabra::buscarLetra(string l) {
	for (int i = 0; i < cant; i++) {
		if (vFichas[i]->getLetra() == l) {
			return i;
		}
	}
	return -1;
}

ficha* palabra::getFicha(int pos) {
	return vFichas[pos];
}

void palabra::eliminarFicha(int pos) {
	for (int i = pos; i < cant; i++) {
		vFichas[i] = vFichas[i + 1];
	}
	vFichas[cant] = NULL;
	cant--;
}

string palabra::toString() {
	stringstream s;
	for (int i = 0; i < cant; i++) {
		if (vFichas[i] != NULL) {
			s << "[" << vFichas[i]->getLetra() << "] ";
		}
	}
	return s.str();
}

palabra::~palabra() {}