#include "ficha.h"

ficha::ficha(string _letra, int val, int _total, int dispongo) :letra(_letra), valor(val), total(_total), disponibles(dispongo) {}

void ficha::setLetra(string letra) { this->letra = letra; }

void ficha::setValor(int val) { this->valor = valor; }

void ficha::setTotal(int total) { this->total = total; }

void ficha::setDisponibles(int dispongo) { disponibles = dispongo; }

string ficha::getLetra() { return letra; }

int ficha::getValor() { return valor; }

int ficha::getTotal() { return total; }

int ficha::getDisponibles() { return disponibles; }

string ficha::toString() {
	stringstream s;
	s << " " << letra << " ";
	return s.str();
}

ficha::~ficha() {}