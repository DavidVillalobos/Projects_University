#include "jugador.h"
#include <iostream>
jugador::jugador(int puntuacion, string nombre, string modalidad, jugador *sig) :puntuacion(puntuacion), nombre(nombre), modalidad(modalidad), sig(sig) {}
int jugador::getPuntuacion() { return puntuacion; }
string jugador::getNombre() { return nombre; }
string jugador::getModalidad() { return modalidad; }
jugador* jugador::getSig() { return sig; }
void jugador::setPuntuacion(int puntuacion) { this->puntuacion = puntuacion; }
void jugador::setNombre(string nombre) { this->nombre = nombre; }
void jugador::setModalidad(string modalidad) { this->modalidad = modalidad; }
void jugador::setSig(jugador *sig) { this->sig = sig; }
string jugador::toString() {
	stringstream s;
	s << nombre << "   " << puntuacion << "   " << modalidad << endl;
	return s.str();
}
jugador::~jugador() {}