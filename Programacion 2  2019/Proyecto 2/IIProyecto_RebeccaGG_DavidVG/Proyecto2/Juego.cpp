#include "Juego.h"
Juego::Juego() { 
	tab = Tablero::tablero(); 
	m = new Movimiento();
}

void Juego::iniciar() {
	setTextUnicode(); // Activando texto en modo unicode
	wstring menuPrincipal[4] = { L" → Juego Nuevo ← ",L" → Cargar Partida ← ",L" → Modo Prueba ← ",L" → Salir ← " };
	wstring f[4] = { L"X",L"B",L"O",L"N" };
	wstring f1[2] = { L"O",L"N" };
	wstring f2[2] = { L"X",L"B" };
	imprimeTitulo(); pause(); cls();
	int resp;
	while (true) {
		while (true) {//Menu principal
			cls();
			imprimeSubtitulo();
			resp = menuSeleccion(17, 6, menuPrincipal, 4, 15, 63, true);
			if (resp == 4) { break; }// Salir
			switch (resp) {
				case 1: { //Aqui se crea un nuevo juego
					cls();
					wstring nom;
					imprimeNuevoJuego();
					imprimir(L"\t\t\tDigite su nombre: ");
					nom = leerwString();
					imprimir(L"\n\t\t\t¿Desea ir de primero?");
					bool turno = menuBinario(21, 10, 15, 63);
					tab->predeterminado();
					comenzarJuego(nom,turno);
					break;
				}
				case 2: {//Aqui se muestran los archivos de partidas creados previamente si existen
					cls();
					wifstream entrada(L"../partidas/nombres.txt");// Archivo donde se guarda el nombre de las partidas
					if (entrada.good()) {
						wstring nombre;
						imprimeCargarJuego();
						while (!entrada.eof()) {
							getline(entrada, nombre, L'\n');
							if (!nombre.empty()) {
								imprimir(L"\t\t--> " + nombre + L"\n");
							}
						}
						imprimir(L"\t\tPara cargar una partida guardada previamente\n");
						imprimir(L"\t\tDigite el nombre del archivo: ");
						wstring nom = leerwString();
						cls();
						bool turno = true;
						if (cargarPartida(nom, turno)) {  //Si se cargo corretamente
							comenzarJuego(nom,turno);
						}
					}
					else {
						imprimir(L"\n\t\tAún no se han guardado partidas, Juega una nueva\n",2);
					}
					entrada.close();
					break;
				}
				case 3: { //Aqui va el caso de prueba
					cls();
					int numNegras = 0;// O, N
					int numBlancas = 0;// X, B
					int opc;
					int x, y;
					bool bandera;
					bool  aux = false;
					while (true) {
						imprimeModoPrueba();
						tab->toString();
						if (numBlancas < 12 || numNegras < 12) {
							setCursor(78, 9); imprimir(L"Para agregar una ficha "); imprimir(L" Jugador: "); imprimir(numBlancas); imprimir(L" PC: "); imprimir(numNegras);
							setCursor(78, 10); imprimir(L"Digite la fila: ");
							x = leerInt() - 1;
							setCursor(78, 11); imprimir(L"Digite la columna: ");
							y = leerInt() - 1;
							Posicion *p = tab->getPosicion(x, y);
							if (p) {
								if ((x + y + 1) % 2 == 0){
									bandera = true;
									if (p->getSimbolo() != ' ') {
										setCursor(78, 12); imprimir(L"Lo sentimos, en esta posicion se encuentra la");
										setCursor(78, 13); imprimir(L"ficha "); imprimir(p->getSimbolo());
										setCursor(78, 14); imprimir(L"¿Desea remplazarla?");
										if (menuBinario(78, 16, 15, 63)) {
											p->eliminarFicha();
											cls();
											imprimeModoPrueba();
											tab->toString();
											bandera = true;
										}
										else { bandera = false; };
									}
									if (bandera) {
										setCursor(78, 12); imprimir(L"¿Cuál Ficha desea agregar?");
										wchar_t sim = ' ';
										if (numBlancas < 12 && numNegras < 12) {
											opc = menuSeleccion(80, 14, f, 4, 15, 63, false);
											switch (opc) {
											case 1: { sim = 'X'; numBlancas++; break; }
											case 2: { sim = 'B'; numBlancas++; break; }
											case 3: { sim = 'O'; numNegras++; break; }
											case 4: { sim = 'N'; numNegras++; break; }
											}
										}
										else {
											if (numBlancas > numNegras) { // si todavia puede poner mas X,N
												opc = menuSeleccion(80, 14, f1, 2, 15, 63, false);
												switch (opc) {
												case 1: { sim = 'O'; numNegras++; break; }
												case 2: { sim = 'N'; numNegras++; break; }
												}
											}
											else {
												if (numBlancas < numNegras) { // si todavia puede poner mas O,B
													opc = menuSeleccion(80, 14, f2, 2, 15, 63, false);
													switch (opc) {
													case 1: { sim = 'X'; numBlancas++; break; }
													case 2: { sim = 'B'; numBlancas++; break; }
													}
												}
												else {
													setCursor(78, 14); imprimir(L"Lo sentimos, no puedes colocar más fichas en el tablero");
													setCursor(78, 15); imprimir(L" Solamente es permitido un máximo de 12 fichas por jugador");
													break; // saliendo
												}
											}
										}
										tab->colocarFicha(sim, x, y);
										setCursor(81, 18); imprimir(L"¿Desea continuar agregando más fichas al tablero");
										if (!menuBinario(83, 20, 15, 63)) {
											if (numBlancas >= 1 && numNegras >= 1) { aux = true; break; }
											setCursor(70, 24); imprimir(L"Lo sentimos, para iniciar un juego, mínimo se requiere");
											setCursor(70,25); imprimir(L"una ficha de cada jugador", 2);
										}
									}
								}
								else {
									setCursor(81, 12); imprimir(L"Lo sentimos, no puedes colocar fichas");
									setCursor(81, 13); imprimir(L"en las casillas negras", 2);
								}
							}
							else {
								setCursor(81, 12); imprimir(L"Lo sentimos, esta posición no se encuentra en");
								setCursor(81, 13); imprimir(L"las dimensiones del tablero",2);
							}
						}
						else {
							setCursor(81, 12); imprimir(L"Lo sentimos, no puedes colocar más fichas en el tablero");
							setCursor(81, 13); imprimir(L" Solamente es permitido un máximo de 12 fichas por jugador",2);
							break;
						}
						cls();
					}
					if (aux) {
						cls();
						wstring nom;
						imprimir(L"\n\n\t El tablero está listo para comenzar el juego");
						imprimir(L"\n\t\tPor favor Digite su nombre: ");
						nom = leerwString();
						imprimir(L"\t\t¿Desea comenzar usted?");
						bool turno = menuBinario(21, 6, 15, 63);
						comenzarJuego(nom, turno);
					}
					break;
				}
			}
		}
		cls();
		imprimir(L"\n\n\n      ¿Seguro que desea salir?"); // Salir del programa
		if ((menuBinario(5, 5, 15, 63))){ // menu que verifica pregunta si o no
			break;
		}
	}
	setTextNormal();// Cambiando texto a modo normal
}

bool Juego::cargarPartida(wstring nomArchivo, bool& turno) {
	wifstream entrada(L"../partidas/" + nomArchivo + L".txt");
	if (entrada.good()) {//Si existe una partida con este nombre
		wstring prevista;
		imprimir(L"\t\t ¿ Desea cargar esta partida con el nombre [" + nomArchivo + L"] ?\n\n");
		wstring linea[8];
		for (int i = 0; i < 8; i++) {// Mostrando pre-vista(se lee al revez)
				getline(entrada, prevista, L'#');
				linea[i] = L"\t\t" + intToString(i+1) + prevista + L'\n';
				getline(entrada, prevista, L'\n');
		}
		for (int i = 7; i > -1; i--){//Se imprime correcto
			imprimir(linea[i]);
		}
		imprimir(L"\t\t  1 2 3 4 5 6 7 8\n");
		if (menuBinario(38, 3, 15, 63)) {
			entrada.seekg(0);//Puntero al inicio para volver a leer(cargar en el tablero)
			wstring ficha;
			getline(entrada, ficha, L'|');
			for (int i = 0; i < 8; i++) {//Por cada fila
				for (int j = 0; j < 9; j++) { //Por cada columna
					getline(entrada, ficha, L'|');
					if (ficha == L"#") { // llegue al final de la fila
						getline(entrada, ficha, L'|');
					}
					else {
						if (ficha != L" ") {//Si la posicion no esta en blanco
							tab->colocarFicha(wchar_t(ficha[0]), i, j);
						}
					}
				}
			}
			getline(entrada,ficha, L'|');
			if (ficha == L"X") {
				turno = true;
			}
			else {
				turno = false;
			}
			entrada.close();
			return true;
		}
	}
	else {
		imprimir(L"\t\tERROR: No existe un archivo con este nombre\n");
		Sleep(2000);
	}
	entrada.close();
	return false;
}

void Juego::guardarPartida(wstring nomArchivo, bool &turno) {
	wstring nom = L"../partidas/" + nomArchivo + L".txt";
	wofstream salida;
	wifstream entrada(nom, ios::_Nocreate);// ya existe este archivo
	if (!entrada.good()) { // sino guarde el nombre
		wstring nom2 = L" [ " + nomArchivo + L" ] creado el (" + ahora() + L")\n";
		salida.open(L"../partidas/nombres.txt", ios::app); //Para guardar el nombre del archivo
		if (salida.good()) { salida << nom2; }
		salida.close();
	}
	entrada.close();
	// actualice o crea la partida
	salida.open(nom, ios::trunc);
	if (salida.good()) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				salida << L"|" << tab->getSimbolo(i, j);
			}
			salida << L"|#|\n";
		}
		if (turno) {
			salida << L"|X|";
		}
		else{
			salida << L"|O|";
		}
	}
	salida.close();
	imprimir(L"\n\n\n\n\n\n\n\n        La Partida ha sido guardada correctamente\n");
	imprimir(L"       La partida se ha guardado con el nombre " + nomArchivo,2);
}

void Juego::comenzarJuego(wstring nomJug, bool &turno) {
	cls();
	bool reiniciar = false;
	do{ //Inicializacion de variables
		if (reiniciar) {
			tab->predeterminado(); // Carga las fichas predeterminamente
		}
		wstring nomE[3] = { L" → Gane ← ",L" → Aleatoria ← ",L" → Ofensiva ← " };
		wstring opciones[4] = { L" → Continuar Jugando ← ",L" → Guardar y Salir ← ",L" → Reiniciar Juego ← ",L" → Salir Sin Guardar ← " };
		bool ganaJ = false, bandera = true, continuar = true, jugando = turno;
		int tipoE = 2;
		int opcion;
		revisarCoronas();
		while (continuar) {
			cls();
			if (jugando) { // EL jugador est'a jugando
				
				tab->toString();
				setCursor(78, 6); imprimir(L"Turno de " + nomJug + L" (X, N)");
				int b = 0; int cantJ = 0;
				cantFichas(cantJ,b);
				if (!m->jugadorJuega(cantJ)) { // Si no puedo efectuar movimientos 
					cls();
					imprimir(L" Te has quedado sin movimientos pues todas\n");
					imprimir(L" tus fichas se encuentran bloqueadas",2);
					ganaJ = false;
					break;
				}
			}
			else {// La PC está jugando
				imprimir(L"\n\t\t\t    ¿Cuál estrategia desea que la PC utilice?");
				tipoE = menuSeleccion(20, 3, nomE, 3, 15, 63, false);
				cambiarEstrategia(tipoE);
				cls();
				tab->toString();
				setCursor(78, 6); imprimir(L"  Turno de PC (O, B)");
				int cantPc = 0; int b = 0;
				cantFichas(b, cantPc);
				if (m->pcJuega(cantPc)) {
					cls();
					cambiarEstrategia(4);
				}
				else {
					cls();
					imprimir(L" La PC se ha quedado sin movimientos pues todas\n");
					imprimir(L" sus fichas se encuentran bloqueadas", 2);
					ganaJ = true;
					break;
				}
			}
			jugando = !jugando; // Cambio de turno
			revisarCoronas();
			tab->toString();
			Sleep(1000);
			cls();
			//Verificar si alguien gano
			if (ganador('X')) { ganaJ = true;  break; }
			if (ganador('O')) { ganaJ = false;  break; }
			imprimir(L"\n\n       Seleccione una opción: ");
			opcion = menuSeleccion(5, 4, opciones, 4, 15, 63, true);
			switch (opcion) {
				case 2: {
					guardarPartida(nomJug, jugando);
					bandera = false;
					continuar = false;
					break;
				}
				case 3: {
					reiniciar = true;
					continuar = false;
					bandera = false;
					break;
				}
				case 4: {
					reiniciar = false;
					bandera = false;
					continuar = false;
					break;
				}
				default: break;
			}
		}
		cls();
		if (bandera) { // Finalizo la partida sin guardar?
			(ganaJ) ? imprimirFelicidades() : imprimirPerdiste();
			imprimir(L"\n\n\t\t");
			pause();
		}
		cls();
		tab->vaciarTablero(); // Eliminando las fichas sobrantes del tablero
	} while (reiniciar);
}

void Juego::cambiarEstrategia(int tipoE){
	switch (tipoE) {
	case 1: { // Gane
		m->setEstrategia(new Gane());
		break; }
	case 2: { // Aletoria
		m->setEstrategia(new Aleatoria());
		break; }
	case 3: { // ofensiva
		m->setEstrategia(new Ofensiva());
		break; }
	case 4: { // jugador
		m->setEstrategia(NULL);// Si recibe NULL elimina estrategia
		break; }
	default:
		break;
	}
};

void Juego:: revisarCoronas(){
	Posicion* p = NULL;
	for (int i = 0; i < 8; i += 2) {
		p = tab->getPosicion(7, i);
		if (p->getSimbolo() == L'X') {
			p->eliminarFicha();
			p->crearFicha(L'B'); // Coronar
		}
	}
	for (int i = 1; i < 8; i += 2) {
		p = tab->getPosicion(0, i);
		if (p->getSimbolo() == L'O') {
			p->eliminarFicha();
			p->crearFicha(L'N');// Coronar
		}
	}
};

void Juego::cantFichas(int &cantJ, int &cantPc){
	wchar_t aux;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			aux = tab->getSimbolo(i, j);
			if (aux == 'X' || aux == 'B') {
				cantJ++;
			}
			if (aux == 'O' || aux == 'N') {
				cantPc++;
			}
		}
	}
};

bool Juego::ganador(wchar_t simp){
	int cant1 = 0, cant2 = 0;
	cantFichas(cant1, cant2); // cuenta las fichas
	if (simp == 'X') {
		if (cant1 == 0) {
			return false;
		}
		else {
			if (cant2 == 0) {
				return true;
			}
			return false;
		}
	}
	else {
		if (simp == 'O') {
			if (cant2 == 0) {
				return false;
			}
			else {
				if (cant1 == 0) {
					return true;
				}
				return false;
			}
		}
	}
	return false;
};

Juego::~Juego() {  delete m;  }