#include "Posicion.h"

Posicion::Posicion(int fil, int col): fil(fil), col(col){ ptr = NULL; }

Posicion::~Posicion() {
	if (ptr != NULL) {
		delete ptr; 
	}
}

void Posicion::setFicha(Posicion *puntero){
	if (ptr) { // si aqui habia otra ficha
		delete ptr; // esta es capturada
	}
	this->ptr = puntero->ptr;// mueve la ficha
	puntero->ptr = NULL;
}

//Este metodo inicializa la ficha
void Posicion::crearFicha(wchar_t simb){ ptr = new Ficha(simb); }

void Posicion::eliminarFicha(){	 
	if (ptr){
		delete ptr; 
		ptr = NULL;
	}
}

int Posicion::getFila(){ return fil; }

int Posicion::getColumna(){ return col; }

wchar_t Posicion::getSimbolo(){
	wchar_t simb = ' '; // si no hay ficha
	if (ptr) { simb = ptr->getSimbolo(); }
	return simb;
}