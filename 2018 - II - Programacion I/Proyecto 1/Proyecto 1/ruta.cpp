#include "ruta.h"

ruta::ruta(string id, string origen, string destino, int hDura, int mDura, int escala) : id(id), origen(origen), destino(destino), hDuracion(hDura), mDuracion(mDura), escala(escala) {}

void ruta::setId(string id) { this->id = id; }

void ruta::setOrigen(string origen) { this->origen = origen; }

void ruta::setDestino(string destino) { this->destino = destino; }

void ruta::setHduracion(int h) { hDuracion = h; }

void ruta::setMduracion(int h) { mDuracion = h; }

void ruta::setEscala(int escala) { this->escala = escala; }

string ruta::getId() { return id; }

string ruta::getOrigen() { return origen; }

string ruta::getDestino() { return destino; }

int ruta::getHduracion() { return hDuracion; }

int ruta::getMduracion() { return mDuracion; }

int ruta::getEscala() { return escala; }

string ruta::toString() {
	stringstream a;
	a << endl;
	a << "ID:"<<id<<"   Ruta: " << origen << "-" << destino << "	Duracion: " << hDuracion << ":" << mDuracion << "	Escalas:" << escala << endl;
	return a.str();
}

ruta::~ruta() {}