#include "jugador.h"

jugador::jugador(string nombre, int ganada, int jugada): nombre(nombre),ganada(ganada), jugada(jugada){}

string jugador::getNombre(){ return nombre; }

int jugador::getGanada(){ return ganada; }

int jugador::getJugada() { return jugada; }

jugador::~jugador(){}
