#include"Movimiento.h"

Movimiento::Movimiento(){ e = NULL; }

bool Movimiento::jugadorJuega(int tamano) { // Solicitar la posicion en forma de wstring y verificacion
	Tablero *tab = Tablero::tablero();
	wstring numeros = L"12345678";
	bool verifica, bandera;
	wstring movimiento, filActual, filNueva, colActual, colNueva;
	int y = 8, equis = 78, cantidad = 0, aux = 1;
	// Verificar bloqueos
	Arbol **Piezas = new Arbol*[tamano];
	Posicion *p = NULL;
	for (int i = 0; i < 8; i++) { // Recorrer cada posicion de la matriz
		for (int j = aux; j < 8; j += 2) {
			p = tab->getPosicion(i, j);
			if (p->getSimbolo() == 'X' || p->getSimbolo() == 'B') { // si hay una ficha del jugador
				if (cantidad < tamano) {
					Piezas[cantidad++] = new Arbol(p, NULL); 
				}
			}
		}
		(aux == 0) ? aux = 1 : aux = 0;
	}
	bandera = false;
	for (int i = 0; i < cantidad; i++){
		if (Piezas[i]->getMayor() != Piezas[i]->getRaiz()) {
			bandera = true;
			break;
		}
	}
	if (!bandera) {
		return false;
	}
	// Ingreso de datos
	while (true) {
		while (true) {
			setCursor(equis, y); imprimir(L"Digite el movimiento de la ficha"); y++;
			setCursor(equis, y); imprimir(L"con el siguiente formato [AA NN]"); y++;
			setCursor(equis, y); imprimir(L"A = Posición actual, N = Posición nueva"); y+=2;
			setCursor(equis, y); imprimir(L" Movimiento: "); y++; movimiento = leerwString();
			if (movimiento.length() == 5 && movimiento[2] == L' ') {
				for (int j = 0; j < movimiento.length(); j++) {
					verifica = false;
					if (j != 2) {
						for (int i = 0; i < numeros.length(); i++) {
							if (movimiento[j] == numeros[i]) {
								verifica = true;
								break;
							}
						}
						if (!verifica) {
							setCursor(equis, y); imprimir(L"ERROR: Debes ingresar únicamente números que estén en el tablero",2); y++;
							break;
						}
					}
				}
				if (verifica) {
					break;
				}
			}
			else {
				setCursor(equis, y); imprimir(L"ERROR: Al introducir los datos, el formato debe ser [AA NN]",2); y++;
			}
		}
		filActual = movimiento[0]; // FilaAColumnaA FilaNColumnaN
		colActual = movimiento[1];
		filNueva = movimiento[3];
		colNueva = movimiento[4];
		//Conversiones a enteros y disminuyendo en uno (1-8) -> (0-7)
		int fA, cA, fN, cN;
		fA = stringToInt(filActual) - 1;
		cA = stringToInt(colActual) - 1;
		fN = stringToInt(filNueva) - 1;
		cN = stringToInt(colNueva) - 1;
		// Validamos la casilla del movimiento
		if ((fA + cA + 1) % 2 == 0) { // En las posiciones blancas del tablero(0-7) al sumar la fila 
			if ((fN + cN + 1) % 2 == 0) { // y la columna da un numero impar por ejemplo 7 + 2 = 9
				//Ahora se vemos cuales movimientos son posibles
				Tablero* t = Tablero::tablero(); // Obtengo el tablero por medio del singleton 
				Posicion *posActual = t->getPosicion(fA, cA);
				if (posActual->getSimbolo() == 'O' || posActual->getSimbolo() == 'N') {
					setCursor(equis, y); imprimir(L"ERROR: Tus fichas son las (X,B) ", 2); y++;
					continue;
				}
				if (posActual->getSimbolo() == ' ') {
					setCursor(equis, y); imprimir(L"ERROR: No existe una ficha en la posición elegida", 2); y++;
					continue;
				}
				Posicion *posNueva = t->getPosicion(fN, cN);
				if (posNueva) { // la nueva posicion no esta en las dimensiones
					if (posNueva->getSimbolo() == ' ') {
						if (posActual) {
							if (posActual->getSimbolo() == 'X' || posActual->getSimbolo() == 'B') {// si esta ficha es mia
								Arbol *a = NULL;
								for (int i = 0; i < tamano; i++){
									if (Piezas[i]->getRaiz()->getPosicion() == posActual) {
										a = Piezas[i];
										break;
									}
								}
								Nodo* nodo = a->buscarNodo(posNueva);
								if (nodo) {
									moverFicha(posActual, nodo->getRuta());
									setCursor(equis, y); imprimir(L"Movimiento realizado con éxito",1); y++;
									cls();
									delete Piezas;
									return true;
								}
								setCursor(equis, y); imprimir(L"ERROR: Movimiento inválido no existe un camino hacia la posición nueva",2); y++;
								continue;
							}
						}
					}
					setCursor(equis, y); imprimir(L"ERROR: No puedes colocar una ficha encima de otra",2); y++;
					continue;
				}
			}
			setCursor(equis, y); imprimir(L"ERROR: No puedes colocar una ficha en las casillas Negras",2); y++;
			continue;
		}
		setCursor(equis, y); imprimir(L"ERROR: No existen fichas en las casillas negras",2); y++;
		continue;
	}
}

bool Movimiento::pcJuega(int tamano) {
	Arbol **Piezas = new Arbol*[tamano];//Vector de arboles(fichas)
	Tablero* t = Tablero::tablero();
	Posicion *p;
	int cantidad = 0;
	bool terminado = false;
	setCursor(78, 8);
	imprimir(L" Moviendo");
	int aux = 1;
	for (int i = 0; i < 8; i++) { // Recorrer cada posicion de la matriz
		for (int j = aux; j < 8; j+=2) {
			p = t->getPosicion(i, j);
			if (p->getSimbolo() == 'O' || p->getSimbolo() == 'N') { // si hay una ficha del pc
				if (cantidad < tamano) {
					Piezas[cantidad++] = new Arbol(p, e); // construya un arbol de probabilidades y caminos con una estrategia
				}										// especifica para esa ficha i
			}
		}
		(aux == 0)? aux = 1 : aux = 0;
	}
	imprimir(L" .");
	Nodo** MejoresMovimientos = new Nodo*[tamano]; // Mejores movimientos de las fichas
	Nodo* MejorJugada = NULL; // Mejor movimiento de Nodes
	Arbol* MejorFicha = NULL;
	for (int i = 0; i < tamano; i++) {
		MejoresMovimientos[i] = Piezas[i]->getMayor();
		if (MejoresMovimientos[i] != Piezas[i]->getRaiz()) { // Si la mejor pos es diferente al movimiento inicial (quedarse quieto)
			if (MejorJugada) {// si existe un mejor movimiento previamente, comparamos
				if (MejorJugada->getValor() < MejoresMovimientos[i]->getValor()) {
					// Si el nodo mejor tiene menos valor que el nuevo
					MejorJugada = MejoresMovimientos[i]; // entonces hay nuevo mayor
					MejorFicha = Piezas[i];
				}// sino se conserva el mayor
			}
			else {// no hay camparacion
				MejorJugada = MejoresMovimientos[i];
				MejorFicha = Piezas[i];
			}
		}
	}
	imprimir(L" .");
	if (MejorJugada) {// puede que todas las fichas esten bloqueas
		//Envio los datos obtenidos del analisis para que el programa ejecute la jugada
		if (MejorFicha) {
			imprimir(L" .");
			Posicion *actual = MejorFicha->getRaiz()->getPosicion();
			Posicion *nueva = MejorJugada->getPosicion();
			setCursor(78, 9); imprimir(L" ["); imprimir(actual->getFila() + 1); imprimir(actual->getColumna() + 1);
			imprimir(L"] ←→ [");
			imprimir(nueva->getFila() + 1); imprimir(nueva->getColumna() + 1); imprimir(L"]", 3);
			terminado = this->moverFicha(actual,MejorJugada->getRuta());
		}
	}
	// Liberando memoria utilizada
	for (int i = 0; i < tamano; i++) {
		delete Piezas[i];
	}
	delete[] Piezas;
	delete[] MejoresMovimientos;
	return terminado;
}

void Movimiento::setEstrategia(Estrategia *nueva) {
	if (nueva) {
		if (this->e) {
			delete this->e;
		}
		this->e = nueva;
	}
	else {
		if (this->e) { 
			delete this->e;
		}
		this->e = NULL;
	}
}

bool Movimiento::moverFicha(Posicion* posInicial, wstring ruta){
	Tablero* tab = Tablero::tablero();

	for (int i = 0; i < ruta.length(); i++) { // verificar que la ruta sea correcta
		wchar_t simb = ruta[i];
		if (simb != '0' && simb != '1' && simb != '2' && simb != '3') {
			return false; // si hay algun ERROR, es muy poco probable
		}
	}

	Posicion *posActual = posInicial;
	Posicion *posNueva = NULL;
	
	for (int i = 0; i < ruta.length(); i++) {
		wchar_t simb = wchar_t(ruta[i]);
		switch (simb) {
			case '0': {// Izquierda
				posNueva = tab->puedoIzquierdaAdelante(posActual);
				break;
			}
			case '1': {// Derecha
				posNueva = tab->puedoDerechaAdelante(posActual);
				break; 
			}
			case '2': {// Izquierda atras
				posNueva = tab->puedoIzquierdaAtras(posActual);
				break;
			}
			case '3': {// Derecha atras
				posNueva = tab->puedoDerechaAtras(posActual);
				break;
			}
		}
		if(posNueva) {
			tab->moverFicha(posActual, posNueva);
			posActual = posNueva;
		}
		else {
			return false; // ERROR
		}
	}
	return true;
}

Movimiento::~Movimiento(){ if (e) { delete e; } }
