#include "Gane.h"

Gane::Gane():Estrategia() {}

int Gane::prioridad(Posicion* pos, wstring ruta, wchar_t simb){
	Tablero* tab = Tablero::tablero();
	if (simb == 'O') {// Si es ficha simple
		if (ruta.length() >= 2) {
			if (ruta.length() >= 4) {
				return 85;
			}
			return 70;
		}
	}
	else {
		if (simb == 'N') {
			Tablero *tab = Tablero::tablero();
			Posicion *aux = NULL;
			switch (ruta[0]) {
			case '0': {//Izquierda
				aux = tab->puedoDerechaAtras(pos);
				break;
			}
			case '1': {//Derecha
				aux = tab->puedoIzquierdaAtras(pos);
				break;
			}
			case '2': {//IzquierdaAtras
				aux = tab->puedoDerechaAdelante(pos);
				break;
			}
			case '3': {//DerechaAtras
				aux = tab->puedoIzquierdaAdelante(pos);
				break;
			}
			}
			if (aux) {
				if (aux->getSimbolo() == 'X' || aux->getSimbolo() == 'B') {
					return 100;// La dama tiene prioridad al capturar
				}
			}

		}

	}
	int suma = 40;
	// Si llega a este punto es por que no puede capturar
	if (pos->getFila() > 3 || pos->getFila() < 6) {  // Es mejor moverla a las del centro
		suma +=15;
	}
	if (3 < pos->getFila() && pos->getFila() < 5) {  // Es mejor moverla a las del centro
		suma += 25;
	}
	else {// si ya esta en las del centro es mejor no moverla
		suma += 5;
	}
	// Verificar amenazas
	Posicion* der = tab->puedoDerechaAdelante(pos);
	Posicion* izq = tab->puedoIzquierdaAdelante(pos);
	Posicion* derA = tab->puedoDerechaAtras(pos);
	Posicion* izqA = tab->puedoIzquierdaAtras(pos);
	if (der && der->getSimbolo() == 'B') {
		if (ruta[ruta.length() - 1] == '0') {
			suma -= 30;
		}
		else {
			if (izqA && izqA->getSimbolo() == ' ') {
				suma -= 30;
			}
		}
	}
	if (izq && izq->getSimbolo() == 'B') {
		if (ruta[ruta.length() - 1] == '3') {
			suma -= 30;
		}
		else {
			if (derA && derA->getSimbolo() == ' ') {
				suma -= 30;
			}
		}	
	}
	if (derA&& (derA->getSimbolo() == 'X' || derA->getSimbolo() == 'B')) {
		if (ruta[ruta.length() - 1] == '3') {
			suma -= 30;
		}
		else {
			if (izq && izq->getSimbolo() == ' ') {
				suma -= 30;
			}
		}
	}
	if (izqA && (izqA->getSimbolo() == 'X' || izqA->getSimbolo() == 'B')) {
		if (ruta[ruta.length() - 1] == '2') {
			suma -= 30;
		}
		else {
			if (der && der->getSimbolo() == ' ') {
				suma -= 30;
			}
		}
	}
	return suma;
}

Gane::~Gane() {}


