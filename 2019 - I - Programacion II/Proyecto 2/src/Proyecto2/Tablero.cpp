#include "Tablero.h"

Tablero* Tablero::_tablero = NULL;

Tablero::Tablero() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			tab[i][j] = new Posicion(i,j);
		}
	}
}

Tablero::~Tablero() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete tab[i][j];
		}
	}
}

Tablero* Tablero::tablero(){
	if (!_tablero) {
		_tablero = new Tablero();
		atexit(destruirTablero); //una vez fuera del programa
	}
	return _tablero;
}

void Tablero::destruirTablero(){
	if (_tablero != NULL) {
		delete _tablero;
	}
}

void Tablero::moverFicha(Posicion* actual, Posicion* nueva) {
	nueva->setFicha(actual);
}

void Tablero::colocarFicha(wchar_t ficha, int i, int j) {
	tab[i][j]->crearFicha(ficha); // inicializamos el puntero a ficha
}

wchar_t Tablero::getSimbolo(int i, int j) {
	if (0 <= i && i <= 7) {
		if (0 <= j && j <= 7) {
			return tab[i][j]->getSimbolo();
		}
	}
	return ' ';
}

Posicion * Tablero::getPosicion(int i, int j){
	Posicion *p = NULL;
	if (0 <= i && i <= 7) {
		if (0 <= j && j <= 7) {
			p = tab[i][j];
		}
	}
	return p;
}

void Tablero::toString() {
	int n = 15, b = 240, aux;
	imprimir(L"╔═════════════════════════════════════════════════════════════════════════════╗\n");;
	imprimir(L"║    █  █  █  █▀▀▀  █▀▀█  █▀▀▀█   █▀▀▄  █▀▀▀   █▀▀▄  █▀▀█  █▀▄▀█  █▀▀█  █▀▀▀█ ║\n");;
	imprimir(L"║ ▄  █  █  █  █▀▀▀  █ ▄▄  █   █   █  █  █▀▀▀   █  █  █▄▄█  █ █ █  █▄▄█  ▀▀▀▄▄ ║\n");;
	imprimir(L"║ █▄▄█  ▀▄▄▀  █▄▄▄  █▄▄█  █▄▄▄█   █▄▄▀  █▄▄▄   █▄▄▀  █  █  █   █  █  █  █▄▄▄█ ║\n");;
	imprimir(L"╚══╦═══════╦═══════╦═══════╦═══════╦═══════╦═══════╦═══════╦═══════╦═══════╦══╝\n");;
	for (int i = 7; i > -1; i--) {
		setColor(15); imprimir(L"   ║       ");
		for (int j = 1; j < 9; j++) {
			setColor(15); imprimir(L"║");
			(j % 2 == 0) ? setColor(n) : setColor(b);
			imprimir(L"       ");
		}
		setColor(15); imprimir(L"║");
		imprimir(L"\n   ║   "); imprimir(i + 1); imprimir(L"   ");
		for (int j = 1; j < 9; j++) {
			setColor(15); imprimir(L"║");
			(j % 2 == 0) ? setColor(n) : setColor(b);
			imprimir(L"   "); imprimir(getSimbolo(i, j - 1)); imprimir(L"   ");
		}
		setColor(15); imprimir(L"║\n   ║       ");
		for (int j = 1; j < 9; j++) {
			setColor(15); imprimir(L"║");
			(j % 2 == 0) ? setColor(n) : setColor(b);
			imprimir(L"       ");
		}
		setColor(15); imprimir(L"║");
		imprimir(L"\n   ╠═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╣\n");
		aux = n;
		n = b;
		b = aux;
	}
	imprimir(L"   ║       ║       ║       ║       ║       ║       ║       ║       ║       ║\n");
	imprimir(L"   ║       ║   1   ║   2   ║   3   ║   4   ║   5   ║   6   ║   7   ║   8   ║\n");
	imprimir(L"   ║       ║       ║       ║       ║       ║       ║       ║       ║       ║\n");
	imprimir(L"   ╚═══════╩═══════╩═══════╩═══════╩═══════╩═══════╩═══════╩═══════╩═══════╝\n");
}

void Tablero::predeterminado(){ // Inicializa las fichas del Tablero en modo predeterminado
	int aux = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = aux; j < 8; j += 2) {
			tab[i][j]->crearFicha('X');
		}
		(aux == 0) ? aux = 1 : aux = 0;
	}
	aux = 0;
	for (int i = 5; i < 8; i++) {
		for (int j = aux; j < 8; j += 2) {
			tab[i][j]->crearFicha('O');
		}
		(aux == 0) ? aux = 1 : aux = 0;
	}
}

void Tablero::vaciarTablero() { //Este metodo elimina las fichas del tablero
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			tab[i][j]->eliminarFicha();
		}
	}
}

Posicion* Tablero::puedoDerechaAdelante(Posicion* p) {
	int columnaN = p->getColumna() + 1;
	int filaN = p->getFila() + 1;
	return getPosicion(filaN, columnaN);
};

Posicion* Tablero::puedoIzquierdaAdelante(Posicion* p) {
	int columnaN = p->getColumna() - 1;
	int filaN = p->getFila() + 1;
	return getPosicion(filaN, columnaN);
};

Posicion* Tablero::puedoDerechaAtras(Posicion* p) {
	int columnaN = p->getColumna() + 1;
	int filaN = p->getFila() - 1;
	return getPosicion(filaN, columnaN);
};

Posicion* Tablero::puedoIzquierdaAtras(Posicion* p) {
	int columnaN = p->getColumna() - 1;
	int filaN = p->getFila() - 1;
	return getPosicion(filaN, columnaN);
};