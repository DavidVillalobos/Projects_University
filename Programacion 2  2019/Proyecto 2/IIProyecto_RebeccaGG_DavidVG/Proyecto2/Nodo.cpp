#include "Nodo.h"
#include"Tablero.h" 

Nodo::Nodo(Posicion *pos, wstring ruta,wchar_t simbM, Estrategia* e) {
	derechaAdelante = izquierdaAdelante = derechaAtras = izquierdaAtras = NULL;
	wchar_t simbO= L' '; // Simbolo de oponente
	wchar_t DamaO= L' '; //Dama de oponente
	wchar_t DamaM= L' '; //Dama de mi propiedad
	this->ruta = ruta; // Ruta por la que se llega a este nodo
	this->pos = pos; // posicion que representa en el tablero
	if (e) { // si existe alguna estrategia, entonces es turno de la PC
		if (pos->getSimbolo() == L' ') {
			this->valor = e->prioridad(pos,ruta,simbM);
		}
		else {
			this->valor = -1;
		}
		simbO = L'X';
		DamaO = L'B';
		DamaM = L'N';
	}
	else { //Sino es turno del Usuario
		simbO = L'O';
		DamaO = L'N';
		DamaM = L'B';
		if (pos->getSimbolo() == L' ') {
			this->valor = 1;
		}
		else {
			this->valor = -1;
		}
	}
	if (simbM == DamaO || simbM == DamaM) { // Si mi ficha es una Dama
		if (ruta.empty() && (pos->getSimbolo() == DamaO || pos->getSimbolo() == DamaM)) { // Es una dama y esta es la base
			caminosBaseDama(simbM, DamaM, simbO, DamaO, e);
		}
		else {
			if (pos->getSimbolo() == L' ' || (pos->getSimbolo() == simbO || pos->getSimbolo() == DamaO)) {
				caminosDiagonalesDama(simbM, DamaM, simbO, DamaO, e);
			}
		}
	}
	else { // Es un peon
		if (ruta.empty()) { // movimiento simple
			caminoSimpleFicha(simbM, DamaM, simbO, DamaO, e);
		}
		else {
			if (1 <= ruta.length()) { // Movimiento doble de la ficha
				caminosEspecialesFicha(simbM, DamaM, simbO, DamaO, e);
			}
		}
	}

}

Nodo::~Nodo() {
	if (derechaAdelante) {
		delete derechaAdelante;
	}
	if (izquierdaAdelante) {
		delete izquierdaAdelante;
	}
	if (derechaAtras) {
		delete derechaAtras;
	}
	if (izquierdaAtras) {
		delete izquierdaAtras;
	}
}

void Nodo::caminosBaseDama(wchar_t &simbM, wchar_t &DamaM, wchar_t &simbO, wchar_t &DamaO, Estrategia* e) {
	Tablero *tab = Tablero::tablero();
	// Derecha Hacia Adelante
	Posicion* derD = tab->puedoDerechaAdelante(pos);
	if (derD) {
		if (derD->getSimbolo() == L' ') {
			derechaAdelante = new Nodo(derD, ruta + L'1', simbM, e);
		}
		else {
			if (derD->getSimbolo() == simbO || derD->getSimbolo() == DamaO) {
				Posicion* derDX2 = tab->puedoDerechaAdelante(derD);
				if (derDX2) {
					if (derDX2->getSimbolo() == L' ') {
						derechaAdelante = new Nodo(derD, ruta + L'1', simbM, e);
					}
				}
			}
		}
	}
	// Izquierda Hacia Adelante
	Posicion* izqD = tab->puedoIzquierdaAdelante(pos);
	if (izqD) {
		if (izqD->getSimbolo() == L' ') {
			izquierdaAdelante = new Nodo(izqD, ruta + L'0', simbM, e);
		}
		else {
			if (izqD->getSimbolo() == simbO || izqD->getSimbolo() == DamaO) {
				Posicion* izqDX2 = tab->puedoIzquierdaAdelante(izqD);
				if (izqDX2) {
					if (izqDX2->getSimbolo() == L' ') {
						izquierdaAdelante = new Nodo(izqD, ruta + L'0', simbM, e);
					}
				}
			}
		}
	}
	// Derecha Hacia Atras
	Posicion* derA = tab->puedoDerechaAtras(pos);
	if (derA) {
		if (derA->getSimbolo() == L' ') {
			derechaAtras = new Nodo(derA, ruta + L'3', simbM, e);
		}
		else {
			if (derA->getSimbolo() == simbO || derA->getSimbolo() == DamaO) {
				Posicion* derAX2 = tab->puedoDerechaAtras(derA);
				if (derAX2) {
					if (derAX2->getSimbolo() == L' ') {
						derechaAtras = new Nodo(derA, ruta + L'3', simbM, e);
					}
				}
			}
		}
	}
	// Izquierda Hacia Atras
	Posicion* izqA = tab->puedoIzquierdaAtras(pos);
	if (izqA) {
		if (izqA->getSimbolo() == L' ') {
			izquierdaAtras = new Nodo(izqA, ruta + L'2', simbM, e);
		}
		else {
			if (izqA->getSimbolo() == simbO || izqA->getSimbolo() == DamaO) {
				Posicion* izqAX2 = tab->puedoIzquierdaAtras(izqA);
				if (izqAX2) {
					if (izqAX2->getSimbolo() == L' ') {
						izquierdaAtras = new Nodo(izqA, ruta + L'2', simbM, e);
					}
				}
			}
		}
	}
}

void Nodo::caminosDiagonalesDama(wchar_t &simbM, wchar_t &DamaM, wchar_t &simbO, wchar_t &DamaO, Estrategia* e) {
	Tablero *tab = Tablero::tablero();
	wchar_t simbAux;
	switch (ruta[ruta.length() - 1]) { // Revisando la diagonal de la que provengo
	case '0': {
		Posicion *izq = tab->puedoIzquierdaAdelante(pos);
		if (izq) {
			if (pos->getSimbolo() == L' ') {
				if (izq->getSimbolo() == L' ') {
					simbAux = tab->puedoDerechaAtras(pos)->getSimbolo();
					if (simbAux != simbO && simbAux != DamaO) {
						izquierdaAdelante = new Nodo(izq, ruta + L'0', simbM, e);
					}
				}
				else {
					if (izq->getSimbolo() == simbO || izq->getSimbolo() == DamaO) {
						Posicion *izqX2 = tab->puedoIzquierdaAdelante(izq);
						if (izqX2 && izqX2->getSimbolo() == L' ') {
							izquierdaAdelante = new Nodo(izq, ruta + L'0', simbM, e);
						}
					}
				}
			}
			else {
				if (pos->getSimbolo() == simbO || pos->getSimbolo() == DamaO) {
					if (izq->getSimbolo() == L' ') {
						izquierdaAdelante = new Nodo(izq, ruta + L'0', simbM, e);
					}
				}
			}
		}
		break;
	}
	case '1': {
		Posicion *der = tab->puedoDerechaAdelante(pos);
		if (der) {
			if (pos->getSimbolo() == L' ') {
				if (der->getSimbolo() == L' ') {
					simbAux = tab->puedoIzquierdaAtras(pos)->getSimbolo();
					if (simbAux != simbO && simbAux != DamaO) {
						derechaAdelante = new Nodo(der, ruta + L'1', simbM, e);
					}
				}
				else {
					if (der->getSimbolo() == simbO || der->getSimbolo() == DamaO) {
						Posicion *derX2 = tab->puedoDerechaAdelante(der);
						if (derX2 && derX2->getSimbolo() == L' ') {
							derechaAdelante = new Nodo(der, ruta + L'1', simbM, e);
						}
					}
				}
			}
			else {
				if (pos->getSimbolo() == simbO || pos->getSimbolo() == DamaO) {
					if (der->getSimbolo() == L' ') {
						derechaAdelante = new Nodo(der, ruta + L'1', simbM, e);
					}
				}
			}
		}
		break;
	}
	case '2': {
		Posicion *izqA = tab->puedoIzquierdaAtras(pos);
		if (izqA) {
			if (pos->getSimbolo() == L' ') {
				if (izqA->getSimbolo() == L' ') {
					simbAux = tab->puedoDerechaAdelante(pos)->getSimbolo();
					if (simbAux != simbO && simbAux != DamaO) {
						izquierdaAtras = new Nodo(izqA, ruta + L'2', simbM, e);
					}
				}
				else {
					if (izqA->getSimbolo() == simbO || izqA->getSimbolo() == DamaO) {
						Posicion *izqAX2 = tab->puedoIzquierdaAtras(izqA);
						if (izqAX2 && izqAX2->getSimbolo() == L' ') {
							izquierdaAtras = new Nodo(izqA, ruta + L'2', simbM, e);
						}
					}
				}
			}
			else {
				if (pos->getSimbolo() == simbO || pos->getSimbolo() == DamaO) {
					if (izqA->getSimbolo() == L' ') {
						izquierdaAtras = new Nodo(izqA, ruta + L'2', simbM, e);
					}
				}
			}
		}
		break;
	}
	case '3': {
		Posicion *derA = tab->puedoDerechaAtras(pos);
		if (derA) {
			if (pos->getSimbolo() == L' ') {
				if (derA->getSimbolo() == L' ') {
					simbAux = tab->puedoIzquierdaAdelante(pos)->getSimbolo();
					if (simbAux != simbO && simbAux != DamaO) {
						derechaAtras = new Nodo(derA, ruta + L'3', simbM, e);
					}
				}
				else {
					if (derA->getSimbolo() == simbO || derA->getSimbolo() == DamaO) {
						Posicion *derAX2 = tab->puedoDerechaAtras(derA);
						if (derAX2 && derAX2->getSimbolo() == L' ') {
							derechaAtras = new Nodo(derA, ruta + L'3', simbM, e);
						}
					}
				}
			}
			else {
				if (pos->getSimbolo() == simbO || pos->getSimbolo() == DamaO) {
					if (derA->getSimbolo() == L' ') {
						derechaAtras = new Nodo(derA, ruta + L'3', simbM, e);
					}
				}
			}
		}
		break;
	}
	}
}

void Nodo::caminoSimpleFicha(wchar_t &simbM, wchar_t &DamaM, wchar_t &simbO, wchar_t &DamaO, Estrategia* e) {
	Tablero *tab = Tablero::tablero();
	if (pos->getSimbolo() == 'X') {
		Posicion *der = tab->puedoDerechaAdelante(pos);
		if (der) {
			if (der->getSimbolo() == simbO || der->getSimbolo() == DamaO) { // Si a la derecha esta mi enemigo
				Posicion *deX2 = tab->puedoDerechaAdelante(der);
				if (deX2) {
					if (deX2->getSimbolo() == L' ') {
						derechaAdelante = new Nodo(der, ruta + L'1', simbM, e);
					}
				}
			}
			else {
				if (der->getSimbolo() == ' ') {
					derechaAdelante = new Nodo(der, ruta + L'1', simbM, e);
				}
			}
		}
		Posicion *izq = tab->puedoIzquierdaAdelante(pos);
		if (izq) {
			if (izq->getSimbolo() == simbO || izq->getSimbolo() == DamaO) { // Si a la izquierda esta mi enemigo
				Posicion *izqX2 = tab->puedoIzquierdaAdelante(izq);
				if (izqX2) {
					if (izqX2->getSimbolo() == L' ') {
						izquierdaAdelante = new Nodo(izq, ruta + L'0', simbM, e);
					}
				}
			}
			else {
				if (izq->getSimbolo() == ' ') {
					izquierdaAdelante = new Nodo(izq, ruta + L'0', simbM, e);
				}
			}
		}
	}
	else {
		if (pos->getSimbolo() == 'O') {
			Posicion *derA = tab->puedoDerechaAtras(pos);
			if (derA) {
				if (derA->getSimbolo() == simbO || derA->getSimbolo() == DamaO) { // Si a la derecha atras esta mi enemigo
					Posicion *derAX2 = tab->puedoDerechaAtras(derA);
					if (derAX2) {
						if (derAX2->getSimbolo() == L' ') {
							derechaAtras = new Nodo(derA, ruta + L'3', simbM, e);
						}
					}
				}
				else {
					if (derA->getSimbolo() == ' ') {
						derechaAtras = new Nodo(derA, ruta + L'3', simbM, e);
					}
				}
			}
			Posicion *izqA = tab->puedoIzquierdaAtras(pos);
			if (izqA) {
				if (izqA->getSimbolo() == simbO || izqA->getSimbolo() == DamaO) { // Si a la izquierda atras esta mi enemigo
					Posicion *izqAX2 = tab->puedoIzquierdaAtras(izqA);
					if (izqAX2) {
						if (izqAX2->getSimbolo() == L' ') {
							izquierdaAtras = new Nodo(izqA, ruta + L'2', simbM, e);
						}
					}
				}
				else {
					if (izqA->getSimbolo() == ' ') {
						izquierdaAtras = new Nodo(izqA, ruta + L'2', simbM, e);
					}
				}
			}
		}
	}
}

void Nodo::caminosEspecialesFicha(wchar_t &simbM, wchar_t &DamaM, wchar_t &simbO, wchar_t &DamaO, Estrategia* e) {
	Tablero *tab = Tablero::tablero();
	switch (ruta[0]) {
		case '0': {
			Posicion *izq = tab->puedoIzquierdaAdelante(pos);
			if (izq) {
				if (pos->getSimbolo() == simbO || pos->getSimbolo() == DamaO) {
					if (izq->getSimbolo() == ' ') {
						izquierdaAdelante = new Nodo(izq, ruta + L'0', simbM, e);
					}
				}
				else {
					if (pos->getSimbolo() == ' ' && 1 < ruta.length()) {
						if (izq->getSimbolo() == simbO || pos->getSimbolo() == DamaO) {
							Posicion *izqX2 = tab->puedoIzquierdaAdelante(izq);
							if (izqX2) {
								if (izqX2->getSimbolo() == ' ') {
									izquierdaAdelante = new Nodo(izq, ruta + L'0', simbM, e);
								}
							}
						}
					}
				}
			}
			break;
		}
		case '1': {
			Posicion *der = tab->puedoDerechaAdelante(pos);
			if (der) {
				if (pos->getSimbolo() == simbO || pos->getSimbolo() == DamaO) {
					if (der->getSimbolo() == ' ') {
						derechaAdelante = new Nodo(der, ruta + L'1', simbM, e);
					}
				}
				else {
					if (pos->getSimbolo() == ' ' && 1 < ruta.length()) {
						if (der->getSimbolo() == simbO || pos->getSimbolo() == DamaO) {
							Posicion *derX2= tab->puedoDerechaAdelante(der);
							if (derX2) {
								if (derX2->getSimbolo() == ' ') {
									derechaAdelante = new Nodo(der, ruta + L'1', simbM, e);
								}
							}
						}
					}
				}
			}
			break;
		}
		case '2': {
			Posicion *izqA = tab->puedoIzquierdaAtras(pos);
			if (izqA) {
				if (pos->getSimbolo() == simbO || pos->getSimbolo() == DamaO) {
					if (izqA->getSimbolo() == ' ') {
						izquierdaAtras = new Nodo(izqA, ruta + L'2', simbM, e);
					}
				}
				else {
					if (pos->getSimbolo() == ' ' && 1 < ruta.length()) {
						if (izqA->getSimbolo() == simbO || pos->getSimbolo() == DamaO) {
							Posicion *izqAX2 = tab->puedoIzquierdaAtras(izqA);
							if (izqAX2) {
								if (izqAX2->getSimbolo() == ' ') {
									izquierdaAtras = new Nodo(izqA, ruta + L'2', simbM, e);
								}
							}
						}
					}
				}
			}
			break;
		}
		case '3': {
			Posicion *derA = tab->puedoDerechaAtras(pos);
			if (derA) {
				if (pos->getSimbolo() == simbO || pos->getSimbolo() == DamaO) {
					if (derA->getSimbolo() == ' ') {
						derechaAtras = new Nodo(derA, ruta + L'3', simbM, e);
					}
				}
				else {
					if (pos->getSimbolo() == ' ' && 1 < ruta.length()) {
						if (derA->getSimbolo() == simbO || pos->getSimbolo() == DamaO) {
							Posicion *derAX2 = tab->puedoIzquierdaAtras(derA);
							if (derAX2) {
								if (derAX2->getSimbolo() == ' ') {
									derechaAtras = new Nodo(derA, ruta + L'3', simbM, e);
								}
							}
						}
					}
				}
			}
			break;
		}
	}
}

wstring Nodo::getRuta() { return ruta; }

Posicion * Nodo::getPosicion(){ return pos; }

void Nodo::setValor(int valor) { this->valor = valor; }

int Nodo::getValor(){ return valor; }

wstring Nodo::toString(){
	wstringstream s;
	if (derechaAtras) {
		s << derechaAtras->toString();
	}
	if (derechaAdelante) {
		s << derechaAdelante->toString();
	}
	for (int i = 0; i < int(ruta.length()); i++) {
		s << "   ";//Identacion
	}
	s << " (" << valor << ")" << getCasilla() << ruta << endl;
	if (izquierdaAdelante) {
		s << izquierdaAdelante->toString();
	}
	if (izquierdaAtras) {
		s << izquierdaAtras->toString();
	}
	return s.str();
}

Nodo* Nodo::getMayor() {
	Nodo* mayor = this;
	Nodo *aux;
	if (derechaAdelante) {
		aux = derechaAdelante->getMayor();
		if (mayor->getValor() < aux->getValor()) {
			mayor =aux;
		}
	}
	if (izquierdaAdelante) {
		aux = izquierdaAdelante->getMayor();
		if (mayor->getValor() < aux->getValor()) {
			mayor = aux;
		}
	}
	if (derechaAtras) {
		aux = derechaAtras->getMayor();
		if (mayor->getValor() < aux->getValor()) {
			mayor = aux;
		}
	}
	if (izquierdaAtras) {
		aux = izquierdaAtras->getMayor();
		if (mayor->getValor() < aux->getValor()) {
			mayor = aux;
		}
	}
	return mayor;
}

wstring Nodo::getCasilla() {
	wstringstream s;
	s << "[" << pos->getFila() + 1 << "][" << pos->getColumna() + 1 << "]";
	return s.str();
}

Nodo * Nodo::buscarNodo(Posicion *p) {
	if (this->pos == p) {//Si mi pos es la que busca
		return this;
	}
	Nodo *aux;
	if (derechaAdelante) {// Si tengo nodo derecho
		aux = derechaAdelante->buscarNodo(p);
		if (aux) {// si lo encontro
			return aux;
		}
	}
	if (izquierdaAdelante) {// Si tengo nodo izquierdo
		aux = izquierdaAdelante->buscarNodo(p);
		if (aux) {// si lo encontro
			return aux;
		}
	}
	if (derechaAtras) {// Si tengo nodo derecho atras
		aux = derechaAtras->buscarNodo(p);
		if (aux) {// si lo encontro
			return aux;
		}
	}
	if (izquierdaAtras) {// Si tengo nodo izquierdo atras
		aux = izquierdaAtras->buscarNodo(p);
		if (aux) {// si lo encontro
			return aux;
		}
	}
	return NULL;// si no lo encontro
}
