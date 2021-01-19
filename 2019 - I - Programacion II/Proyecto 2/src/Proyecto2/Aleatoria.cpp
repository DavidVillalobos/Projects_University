#include "Aleatoria.h"

Aleatoria::Aleatoria():Estrategia() {}

int Aleatoria::prioridad(Posicion* pos, wstring ruta, wchar_t simb) { 
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
					return 100;// La dama tiene prioridad al capturar
				}
			}
		}

	}
	// Si no puede capturar otras fichas, su movimiento debe ser al azar
	std::srand(int(time(NULL)));
	return 1 + rand() % (70 + 1);
}

Aleatoria::~Aleatoria() {}