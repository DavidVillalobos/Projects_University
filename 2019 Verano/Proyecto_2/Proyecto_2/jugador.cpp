#include "jugador.h"

jugador::jugador(string nombre, int puntaje, int pG) :usuario(nombre), puntaje(puntaje), pGanadas(pG) {
	word = new palabra();
	lista = new listaPalabras();
}

void jugador::setPalabra(palabra* p) { word = p; }

palabra* jugador::getPalabra() { return word; }

string jugador::getUsuario() { return usuario; }

int jugador::getPuntaje() { return puntaje; }

int jugador::getPganadas() { return pGanadas; }

void jugador::setPganadas(int pG) { pGanadas = pG; }

void jugador::setPuntaje(int puntaje) { this->puntaje = puntaje; }

listaPalabras* jugador::getLista() { return lista; }

void jugador::setListaPalabras(listaPalabras* p) { lista = p; }

string jugador::toString() {
	stringstream s;
	s << "Usuario: " << usuario << "\tPuntaje: " << puntaje << endl;
	return s.str();
}

jugador::~jugador() { delete word; delete lista; }