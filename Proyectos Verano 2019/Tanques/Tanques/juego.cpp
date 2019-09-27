#include "juego.h"
juego::juego(){
/*
Metodo de huir IA
si el jugador dispara, mandarle las coordenadas al Enemigo 
si el se encuentra en un rango de 2X2 del jugador 
activar el metodo huir que lo que hace es alejarse de la bala no 
del jugador

En las esquinas detectara
si hay pared y si arriba hay disparo por huir no moverse
y si le dispara y esta en una esquina huir hacia el lado contrario
*/
}

void juego::cargar(){
	/* La interfaz del juego tendrá 3 modalidades de juego
Modo Clasico: lucha jugador vs jugador ó jugador vs maquina individual y para dos 
lucha normal

Modo Supervivencia: Armas tu fortaleza y te llegan enemigos  individual o en equipo 
este es hasta donde puede llegar sin ser derrotados (NO es pelear entre ustedes)

Modo BattleGround: Pelea en supervivencia contra otro jugador
o en equipo
es parecido a supervivencia excepto que es jugador contra jugador
*/
	listJugadores = new jugadores();
	listEquipos = new jugadores*[20];
	for (int i = 0; i < 20; i++) {
		listEquipos[i] = NULL;
	}
	ifstream f("../puntuaciones.txt");int i = 0;
	while (f.good()) {
		string nom, mod, punt;
		getline(f, nom, '*');
		while (nom != "#") {
			getline(f, punt, '*');
			getline(f, mod, '\n'); 
			if (!nom.empty() && !punt.empty() && !mod.empty()) {
				listJugadores->insertarPrimero(convertirInt(punt), nom, mod);
			}
			getline(f, nom, '*');
		}
		getline(f, nom, '\n'); getline(f, nom, '*');
		string puntAux,nomAux;
		while (nom != "#") {
			getline(f, nomAux, '*');
			getline(f, punt, '*');
			getline(f, puntAux, '\n');
			if (!nom.empty() && !punt.empty()&& !nomAux.empty() && !puntAux.empty()) {
				listEquipos[i] = new jugadores();
				listEquipos[i]->insertarPrimero(convertirInt(punt), nom, "SuperVivencia");
				listEquipos[i]->insertarPrimero(convertirInt(puntAux), nomAux, "SuperVivencia");
			}
			getline(f, nom, '*');i++;
		}
		getline(f, nom, '\n');
	}
	for (int a = i - 1; a < 20; a++) { listEquipos[a] = NULL; }
	jugadores *aux;
	for (int e = 0; e < 20; e++){
		for (int a = 0; a < 20;a++){
			if ((listEquipos[a] != NULL) && (listEquipos[e] != NULL)){
				if (listEquipos[e]->sumaPuntuaciones()> listEquipos[a]->sumaPuntuaciones()) {
					aux = listEquipos[e];
					listEquipos[e] = listEquipos[a];
					listEquipos[a] = aux;
				}
			}
		}
	}
	f.close();
}

void juego::menus(){
	pantalla();
	int salida = 3, X=0,Y=0, menu=0, num;
	do {
		do {system("cls");mostrarCursor(false);
			if (menu != 7) {
				X = 35, Y = 5; imprimeMarcoDoble(X, Y, 19, 60, 14, "N", 9, 6); Y = Y + 5; X = X + 17 + 9; setColor(15);
				setCursor(X, Y); imprimeString("MENU PRINCIPAL"); Y = Y + 2; X = X + 7 - 9;
				string vector[5] = { "Clasico","Supervivencia","Batalla","Puntajes Altos","Salir" };
				menu = menuSeleccionCuadrilatero(X - 9, Y, 2, 3, vector, 5, 4, 15);
			}
			else { menu = 1; }
			switch (menu) {
			case 1: {system("cls"); X = 35, Y = 5; imprimeMarcoDoble(X,Y,21,60,14,"\333",2,6); Y = Y + 5; X = X + 17 + 9; setColor(15);
				setCursor(X, Y); imprimeString("MODO CLASICO"); Y = Y + 2; X = X + 7 - 9; 
				setCursor(X, Y); imprimeString(" Elija el contrincante"); Y = Y + 2;
				string opciones[3] = { "Jugador vs Maquina","Jugador vs Jugador","Volver" };
				switch (num = menuSeleccionLista(X, Y, opciones, 3, 12, 15, true)){
				case 1: {modo_CLS_PVM(); break;}
				case 2: {modo_CLS_PVP();break;}
				case 3: {break;}
				}
				break; }
			case 2: { break; }
			case 3: {/*MODO BATALLA*/break; }
			case 4: {
				cargar(); system("cls");
				X = 35, Y = 5; imprimeMarcoDoble(X, Y, 16, 60, 14, "+", 9, 6); Y = Y + 5; X = X + 21; setColor(15);
				setCursor(X, Y); imprimeString("PUNTAJES MAS ALTOS"); Y = Y + 2; X = X + 7 - 4;
				string vector[5] = { "Clasico","Supervivencia","Batalla","volver" };
				switch (num = menuSeleccionCuadrilatero(X - 9, Y, 2, 2, vector, 4, 9, 15)) {
				case 1: {
					system("cls");X = 35, Y = 5; imprimeMarcoDoble(X, Y, 19, 60, 14, "+", 9, 6); Y = Y + 5; X = X + 21; setColor(15);
					setCursor(X, Y); imprimeString("LISTA DE JUGADORES DISPONIBLES EN MODO CLASICO"); Y++;
					setCursor(X, Y); imprimeString(listJugadores->list_Puntuaciones("Clasico")->toString()+"\n\n");
					system("pause");
					break; 
				}
				case 2: {
					system("cls");
					X = 35, Y = 5; imprimeMarcoDoble(X, Y, 19, 60, 14, "+", 9, 6); Y = Y + 5; X = X + 15; setColor(15);
					setCursor(X, Y); imprimeString("MODO SUPERVIVENCIA"); Y++;
					string vector[5] = { "Equipo","Individual","volver" }; int aux;
					switch (aux = menuSeleccionCuadrilatero(X - 9, Y, 2, 2, vector, 4, 4, 15)) {
					case 1: {
						system("cls");
						X = 35, Y = 5; imprimeMarcoDoble(X, Y, 19, 60, 14, "N", 9, 6); Y = Y + 5; X = X + 17 + 9; setColor(15);
						setCursor(X, Y); imprimeString("LISTA DE PUNTUACIONES EN MODO SUPERVIVENCIA EN EQUIPO");
						for (int i = 0; i < 20;i++) {
							if (listEquipos[i]!=NULL) {
								Y++; setCursor(X, Y);imprimeString(listEquipos[i]->toString() + "\n\n");
							}
						}
						system("pause"); break; }
					case 2: {
						system("cls");
						X = 35, Y = 5; imprimeMarcoDoble(X, Y, 19, 60, 14, "+", 9, 6); Y = Y + 5; X = X + 17 + 9; setColor(15);
						setCursor(X, Y); imprimeString("LISTA DE PUNTUACIONES EN MODO SUPERVIVENCIA INDIVIDUAL");
						Y++; setCursor(X, Y); imprimeString(listJugadores->list_Puntuaciones("Supervivencia")->toString() + "\n\n");
						system("pause"); break; }
					case 3: {break; }
					}
					
					break;
					break; }
				case 3: {
					system("cls");
					X = 35, Y = 5; imprimeMarcoDoble(X, Y, 19, 60, 14, "N", 9, 6); Y = Y + 5; X = X + 17 + 9; setColor(15);
					setCursor(X, Y); imprimeString("            LISTA DE JUGADORES DISPONIBLES EN MODO BATALLA"); Y++;
					setCursor(X, Y); imprimeString(listJugadores->list_Puntuaciones("Batalla")->toString() + "\n\n");
					system("pause");
					break; }
				case 4: {break; }
				}
				delete listJugadores;
				for (int i = 0; i < 20; i++) {
					delete listEquipos[i];
				}
				delete[] listEquipos;
				break; }
			case 5: {break; }
			}
		} while (menu != 5);
		system("cls"); X = 35, Y = 5; imprimeMarcoDoble(X, Y, 12, 60, 14, "+", 12, 6); 
		Y = Y + 5; X = X + 17; setColor(15);
		setCursor(X, Y); imprimeString("\250Esta seguro que desea salir?");
		string vector[2] = {"Confirmar","Cancelar"};
		salida = menuSeleccionLista(X-1, Y+1, vector, 2, 1, 15, false);
	} while (salida != 1);
}

void juego::modo_CLS_PVP() {
	system("cls");
	limArriba = 5, limAbajo = 30 + limArriba, limIzq = 5, limDer = 117 + limIzq;
	mostrarCursor(false);
	//Aqui se pregunta  los nombres y colores con los menuSeleccion
	/*
	   5 <--IZQ_________ARB-->5__________DER --> 122
			|___Datos 2___|____Datos 1____|
			|			  |(63)    		  |
			|	   2(34)  |		  1(92)	  |
	35<--ABJ|______(20)___|______(20)____|
	tanque *Jugador_1 = new tanque(92, 20, 1, 5, 35, 63, 122, "David", 4, 14);
	tanque *Jugador_2 = new tanque(34, 20, 2, 5, 35, 5, 62, "Andres", 2, 12);
	*/
	tanque *Jugador_1 = new tanque(92, 20, 1, 5, 35, 5, 122, "David", 4, 14);
	tanque *Jugador_2 = new tanque(34, 20, 2, 5, 35, 5, 122, "Andres", 2, 12);
	imprimeCuadrilatero(limIzq, limArriba, limAbajo - limArriba, limDer - limIzq, 14, " ", 0);
	setCursor(((limDer - limIzq) / 2) + limIzq, limIzq); imprimeString("\313");
	for (int i = 1; i < (limAbajo - limIzq + 1); i++) {
		setCursor(((limDer - limIzq) / 2) + limIzq, limIzq + i); imprimeString("\272");
	}
	setCursor(((limDer - limIzq) / 2) + limIzq, limIzq + (limAbajo - limArriba) + 1); imprimeString("\312");
	Jugador_1->imprimirTanque(); Jugador_2->imprimirTanque();
	//imprimeCuadrilatero(100,0,28,18,14,"\260",4); // marco de puntuaciones
	clock_t tmp_1 = clock() + 1000 * CLOCKS_PER_SEC; bool perm_1 = true;
	clock_t tmp_2 = clock() + 1000 * CLOCKS_PER_SEC; bool perm_2 = true;
	//int largo = limDer - limIzq; division
	//NECESITO CREAR LIMITES COMO ATRIBUTOS DE CADA JUGADOR (reducir codigo)
	bool gameOver = false; bala *disparo_1 = NULL, *disparo_2 = NULL; 
	while (!gameOver) {
		if (_kbhit()) {
			char tecla = _getch();
			if ((tecla == 75 || tecla == 80 || tecla == 77 || tecla == 72 || tecla == ' ') && Jugador_1->getVidas() > 0) {//Mando 1
				Jugador_1->borrarPosAnt();
				Jugador_1->movimiento(tecla);
				if (tecla == ' ') {
					if (disparo_1 == NULL && Jugador_1->getDisparos() > 0) {// si aun tiene balas
						disparo_1 = new bala(Jugador_1->getX(), Jugador_1->getY(), 5, 35, 5, 121);
						disparo_1->setDireccion(Jugador_1->getDireccion());
						if (!disparo_1->direccionar(Jugador_1)) {
							delete disparo_1; disparo_1 = NULL;
						}
						if (disparo_1 != NULL) { Jugador_1->setDisparos(Jugador_1->getDisparos() - 1); }
					}
				}
			}
			if ((tecla == 'a' || tecla == 's' || tecla == 'w' || tecla == 'd' || tecla == 'x') && Jugador_2->getVidas() > 0) {
				Jugador_2->borrarPosAnt();
				Jugador_2->movimiento(tecla);
				if (tecla == 'x') {
					if (disparo_2 == NULL && Jugador_2->getDisparos() > 0) {
						disparo_2 = new bala(Jugador_2->getX(), Jugador_2->getY(), 5, 35, 5, 121);
						disparo_2->setDireccion(Jugador_2->getDireccion());
						if (!disparo_2->direccionar(Jugador_2)) {
							delete disparo_2; disparo_2 = NULL;
						}
						if (disparo_2 != NULL) { Jugador_2->setDisparos(Jugador_2->getDisparos() - 1); }
					}
				}
			}
			Jugador_2->toString(102, 13); Jugador_2->imprimirTanque();
			Jugador_1->toString(102, 7); Jugador_1->imprimirTanque();
		}
		if (Jugador_1->getVidas() <= 0 || Jugador_2->getVidas() <= 0) { gameOver = true; }
		if (disparo_1 != NULL && disparo_2 != NULL) {
			if (disparo_1->getY() == disparo_2->getY()) {
				if (disparo_1->getX() == disparo_2->getX() || disparo_1->getX() == disparo_2->getX() + 1) {
					disparo_1->explosion();
					disparo_2->borrar();
					delete disparo_1, disparo_2;
					disparo_1 = disparo_2 = NULL;
				}
			}
		}
		if (disparo_1 != NULL) {
			if ((disparo(Jugador_1, Jugador_2, disparo_1) == true)) {
				imprimeCuadrilatero(limIzq, limArriba, limAbajo - limArriba, limDer - limIzq, 14, " ", 0);
				setCursor(((limDer - limIzq) / 2) + limIzq, limIzq); imprimeString("\313");
				for (int i = 1; i < (limAbajo - limIzq + 1); i++) {
					setCursor(((limDer - limIzq) / 2) + limIzq, limIzq + i); imprimeString("\272");
				}
				setCursor(((limDer - limIzq) / 2) + limIzq, limIzq + (limAbajo - limArriba) + 1); imprimeString("\312");
				delete disparo_1, disparo_1 = NULL;
			}
		}
		if (disparo_2 != NULL) {
			if (disparo(Jugador_2, Jugador_1, disparo_2) == true) {
				imprimeCuadrilatero(limIzq, limArriba, limAbajo - limArriba, limDer - limIzq, 14, " ", 0);
				setCursor(((limDer - limIzq) / 2) + limIzq, limIzq); imprimeString("\313");
				for (int i = 1; i < (limAbajo - limIzq + 1); i++) {
					setCursor(((limDer - limIzq) / 2) + limIzq, limIzq + i); imprimeString("\272");
				}
				setCursor(((limDer - limIzq) / 2) + limIzq, limIzq + (limAbajo - limArriba) + 1); imprimeString("\312");
				delete disparo_2, disparo_2 = NULL;
			}
		}
		if (Jugador_1->getDisparos() == 0) {
			if (perm_1) {
				tmp_1 = clock() + 10 * CLOCKS_PER_SEC;
				perm_1 = false;
			}
			else {
				if (clock() >= tmp_1) {
					Jugador_1->recargar(102, 7);
					perm_1 = true;
				}
			}
		}
		else { perm_2 = true; }
		if (Jugador_2->getDisparos() == 0) {
			if (perm_2) {
				tmp_2 = clock() + 10 * CLOCKS_PER_SEC;
				perm_2 = false;
			}
			else {
				if (clock() >= tmp_2) {
					Jugador_2->recargar(102, 13);
					perm_2 = true;
				}
			}
		}
		else { perm_2 = true; }
	}
}

void juego::modo_CLS_PVM() {
	system("cls");
	limArriba = 5, limAbajo = 30 + limArriba, limIzq = 5, limDer = 117 + limIzq;
	mostrarCursor(false);
	//tanque *Jugador_1 = new tanque(92, 20, 1, 5, 35, 63, 122, "David", 4, 14);
	//tanque *enemigo_1 = new tanque(34, 20, 2, 5, 35, 5, 62, "Maquina", 2, 15);

	tanque *Jugador_1 = new tanque(92, 20, 1, 5, 35, 5, 122, "David", 4, 14);
	tanque *enemigo_1 = new tanque(34, 20, 0, 5, 35, 5, 122, "Maquina", 2, 15);
	imprimeCuadrilatero(limIzq, limArriba, limAbajo - limArriba, limDer - limIzq, 14, " ", 0);
	setCursor(((limDer - limIzq) / 2) + limIzq, limIzq); imprimeString("\313");
	for (int i = 1; i < (limAbajo - limIzq + 1); i++) {
		setCursor(((limDer - limIzq) / 2) + limIzq, limIzq + i); imprimeString("\272");
	}
	setCursor(((limDer - limIzq) / 2) + limIzq, limIzq + (limAbajo - limArriba) + 1); imprimeString("\312");
	Jugador_1->imprimirTanque(); enemigo_1->imprimirTanque();
	//imprimeCuadrilatero(100,0,28,18,14,"\260",4); // marco de puntuaciones
	clock_t tmp_1 = clock() + 1000 * CLOCKS_PER_SEC; bool perm_1 = true;
	clock_t tmp_ene1 = clock() + 1000 * CLOCKS_PER_SEC; bool perm_ene1 = true; int dificultad; cin >> dificultad;
	bool gameOver = false; bala *disparo_1 = NULL, *disparo_ene1 = NULL; int eneMove = 0;
	while (!gameOver) {
		if (_kbhit()) {
			char tecla = _getch();
			if ((tecla == 75 || tecla == 80 || tecla == 77 || tecla == 72 || tecla == ' ') && Jugador_1->getVidas() > 0) {//Mando 1
				Jugador_1->borrarPosAnt();
				Jugador_1->movimiento(tecla);
				if (tecla == ' ') {
					if (disparo_1 == NULL && Jugador_1->getDisparos() > 0) {// si aun tiene balas
						disparo_1 = new bala(Jugador_1->getX(), Jugador_1->getY(), 5, 35, 5, 121);
						disparo_1->setDireccion(Jugador_1->getDireccion());
					if (!disparo_1->direccionar(Jugador_1)) {
							delete disparo_1; disparo_1 = NULL;
						}
						if (disparo_1 != NULL) { Jugador_1->setDisparos(Jugador_1->getDisparos() - 1); }
					}
				}
			}
			Jugador_1->toString(102, 7); Jugador_1->imprimirTanque();
		}
		if (Jugador_1->getVidas() <= 0 || enemigo_1->getVidas() <= 0) { gameOver = true; }
		else {
			if (eneMove >= dificultad) {
				enemigo_1->borrarPosAnt();
				if(disparo_1 != NULL || enemigo_1->getDisparos() == 0 || (enemigo_1->getSalud() == 1 && enemigo_1->getVidas() == 1 && disparo_1 != NULL)|| enemigo_1->getX() + 7 == enemigo_1->getLimDer()){
				enemigo_1->setJugador(-1);
				}
				if (enemigo_1->moverIA(Jugador_1->getX(),Jugador_1->getY(),disparo_1)) {
					if (disparo_ene1 == NULL && enemigo_1->getDisparos()>0) {
						disparo_ene1 = new bala(enemigo_1->getX(), enemigo_1->getY(), 5, 35, 5, 121);
						disparo_ene1->setDireccion(enemigo_1->getDireccion());
						if (!disparo_ene1->direccionar(enemigo_1)) {
							delete disparo_ene1; disparo_ene1 = NULL;
						}
						if (disparo_ene1 != NULL) { enemigo_1->setDisparos(enemigo_1->getDisparos() - 1); }
					}
				}
				eneMove = 0;
				enemigo_1->toString(102, 13); enemigo_1->imprimirTanque();
			}
			eneMove++;
		}
		if (disparo_1 != NULL && disparo_ene1 != NULL) {
			if (disparo_1->getY() == disparo_ene1->getY()) {
				if (disparo_1->getX() == disparo_ene1->getX() || disparo_1->getX() == disparo_ene1->getX() + 1) {
					disparo_1->explosion();
					disparo_ene1->borrar();
					delete disparo_1, disparo_ene1;
					disparo_1 = disparo_ene1 = NULL;
				}
			}
		}
		if (disparo_1 != NULL) {
			if ((disparo(Jugador_1, enemigo_1, disparo_1) == true)) {
				delete disparo_1, disparo_1 = NULL;
			}
		}
		if (disparo_ene1 != NULL) {
			if (disparo(enemigo_1, Jugador_1, disparo_ene1) == true) {
				delete disparo_ene1, disparo_ene1 = NULL;
			}
		}
		if (Jugador_1->getDisparos() == 0) {
			if (perm_1) {
				tmp_1 = clock() + 10 * CLOCKS_PER_SEC;
				perm_1 = false;
			}
			else {
				if (clock() >= tmp_1) {
					Jugador_1->recargar(102, 7);
					perm_1 = true;
				}
			}

		}else{ perm_1 = true; }
		if (enemigo_1->getDisparos() == 0) {
			if (perm_ene1) {
				tmp_ene1 = clock() + 10 * CLOCKS_PER_SEC;
				perm_ene1 = false;
			}
			else {
				if (clock() >= tmp_ene1) {
					enemigo_1->recargar(102, 13);
					perm_ene1 = true;
				}
			}

		}else { perm_ene1 = true; }
	}
}

void juego::modo_SPV_INDV(){
// este modo es algo asi como apocalipsis zombie
}

void juego::modo_SPV_EQU(){}

void juego::modo_BTTL() {
	//La batalla es entre dos jugadores unicamente 
}

bool juego::disparo(tanque *J1, tanque *J2, bala *d) {
	if (d->getX() > limIzq + 1 && d->getY() < limAbajo && d->getX() < limDer && d->getY() > limArriba) {
		(d->getDireccion() == 2 || d->getDireccion() == 4) ? Sleep(15) : Sleep(20);
		setColor(J1->getColor());
		d->mover();
		int vidaAux = J2->getVidas();
		if (vidaAux > 0) {
			if (d->colision(J1,J2)) {
				if (vidaAux != J2->getVidas()) {
					(J2->getJugador()==1)?J2->revivir(92, 20):J2->revivir(34, 20);
				}
				return true;
			}
		}
	}
	else {
		if (d->getY() <= limArriba) { setColor(14); setCursor(d->getX(), d->getY()); imprimeString("\315"); }
		else { d->borrar(); }
		return true;
	}
	return false;
}

juego::~juego(){}