#include "Ofensiva.h"

Ofensiva::Ofensiva():Estrategia() {}

int Ofensiva::prioridad(Posicion *pos, wstring ruta, wchar_t simb){
	Tablero* tab = Tablero::tablero();
	// Verificar si puedo capturar
	if (simb == 'O') {// Si es ficha simple
		if (ruta.length() == 2) {
			return 80;
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
					return 100;
				}
			}
		}
	}
	// Si llega a este punto es porque no pudo comer
	// Verificar que las de atras no se muevan
	int suma = 0;
	if (pos->getFila() <= 5){  // Es mejor moverla a las del centro
		return suma += 45;
	}
	else {// si ya esta en las del centro es mejor no moverla
		return suma += 10;
	}
}

Ofensiva::~Ofensiva(){}
