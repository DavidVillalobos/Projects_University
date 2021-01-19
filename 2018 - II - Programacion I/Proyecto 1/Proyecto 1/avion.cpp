#include "avion.h"

avion::avion(string _id, string model, string marc, int _anno, char _tam) :
	id(_id), modelo(model), marca(marc), anno(_anno), tam(_tam) {
	if (tam == 'G' || tam == 'g') {
		setFila(30);
		setCol(6);
		cantPasajeros = 180;
	}
	else {
		setFila(25);
		setCol(4);
		cantPasajeros = 100;
	}
}

void avion::setId(string id) { this->id = id; }

void avion::setModelo(string model) { modelo = model; }

void avion::setMarca(string marca) { this->marca = marca; }

void avion::setAnno(int anno) { this->anno = anno; }

void avion::setCantPasajeros(int cantP) { cantPasajeros = cantP; }

void avion::setFila(int fila) { this->fila = fila; }

void avion::setCol(int col) { this->col = col; }

void avion::setTam(char tam) { this->tam = tam; }

string avion::getId() { return id; }

string avion::getModelo() { return modelo; }

string avion::getMarca() { return marca; }

int avion::getAnno() { return anno; }

int avion::getCantPasajeros() { return cantPasajeros; }

int avion::getFila() { return fila; }

int avion::getCol() { return col; }

char avion::getTam() { return tam; }

string avion::toString() {
	stringstream s;
	s << endl;
	s << "   ID: " << getId() << endl;
	s << "   A\244o: " << getAnno() << endl;
	s << "   Modelo: " << getModelo() << endl;
	s << "   Marca: " << getMarca() << endl;
	s << "   Cantidad de Pasajeros: " << getCantPasajeros() << endl;
	s << "   Tama\244o: " << getTam() << endl;
	return s.str();
}

avion::~avion() {

}