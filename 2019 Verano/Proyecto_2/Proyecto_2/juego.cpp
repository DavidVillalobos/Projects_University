#include "juego.h"

juego::juego() {
	d = new diccionario();
}

void juego::cargar() {
	int salida = 3;
	do {
		if (salida == 2 || salida == 3) { menuPrincipal(); }
		setColor(14); setCursor(17, 3); imprimeString("\311"); for (int i = 0; i < 58; i++) { imprimeString("\315"); }imprimeString("\273");
		setCursor(17, 4); imprimeString("\272"); setColor(2); for (int i = 0; i < 58; i++) { imprimeString("\260"); }setColor(14); imprimeString("\272");
		setCursor(17, 5); imprimeString("\272"); setColor(2); for (int i = 0; i < 3; i++) { imprimeString("\260"); }setColor(14); imprimeString("\311"); for (int i = 0; i < 50; i++) { imprimeString("\315"); }setColor(14);		imprimeString("\273"); setColor(2); for (int i = 0; i < 3; i++) { imprimeString("\260"); }setColor(14); imprimeString("\272");
		for (int i = 0; i < 7; i++) {
			setCursor(17, i + 6); imprimeString("\272"); setColor(2); for (int a = 0; a < 3; a++) { imprimeString("\260"); }setColor(14); imprimeString("\272"); setColor(2); for (int e = 0; e < 50; e++) { imprimeString(" "); }setColor(14); imprimeString("\272"); setColor(2); for (int o = 0; o < 3; o++) { imprimeString("\260"); }setColor(14); imprimeString("\272");
		}
		setCursor(17, 13); imprimeString("\272"); setColor(2); for (int i = 0; i < 3; i++) { imprimeString("\260"); }setColor(14); imprimeString("\310"); for (int i = 0; i < 50; i++) { imprimeString("\315"); }setColor(14); imprimeString("\274"); setColor(2); for (int i = 0; i < 3; i++) { imprimeString("\260"); }setColor(14); imprimeString("\272");
		setCursor(17, 14); imprimeString("\272"); setColor(2); for (int i = 0; i < 58; i++) { imprimeString("\260"); }setColor(14); imprimeString("\272");
		setCursor(17, 15); imprimeString("\310"); for (int i = 0; i < 58; i++) { imprimeString("\315"); }imprimeString("\274"); setColor(15);
		setCursor(32, 7); imprimeString("\250Est\240 seguro que desea salir?");
		setCursor(40, 9); imprimeString("1) Confirmar");
		setCursor(40, 11); imprimeString("2) Cancelar");
		setCursor(37, 17); imprimeString("Ingrese un numero: "); salida = leerInt();
		switch (salida) {
		case 1: {break; }
		case 2: {break; }
		default: {imprimeString(" Esta opci\242n no se encuentra en el men\243, por favor int\202ntelo de nuevo"); Sleep(2000); break; }
		}
		limpiaPantalla();
	} while (salida != 1);
}

ficha*juego::GETFICHA(string letra) {
	for (int i = 0; i < tamano; i++) {
		if (bolsita[i]->getLetra() == letra) {
			return bolsita[i];
		}
	}
	return NULL;
}

void juego::menuPrincipal() {
	int menu = 4;
	do {
		imprimeMenu(); menu = leerInt(); limpiaPantalla();
		switch (menu) {
		case 1: {
			jugar();
			break;
		}
		case 2: {
			int historial = 7;
			do {
				imprimeString("\n\nMENU HISTORIAL\n\n\n");
				imprimeString("\n\n1) Puntajes\n");
				imprimeString("\n2) Diccionario\n");
				imprimeString("\n3) Fichas\n");
				imprimeString("\n4) Palabras buscadas\n");
				imprimeString("\n5) Palabras por jugador\n");
				imprimeString("\n6)Salir\n");
				imprimeString("Ingrese un n\243mero: "); historial = leerInt();
				pausa();
				limpiaPantalla();
				switch (historial) {
				case 1: {
					imprimeString("\n\nHISTORIAL DE PUNTAJES\n\n");
					ifstream inf("../HistorialPuntajes.txt");
					string leo;
					if (inf.fail()) {
						imprimeString("		EL FICHERO NO EXISTE\n\n");
					}
					else {
						while (!inf.eof()) {
							getline(inf, leo, '\n');
							imprimeString(leo); imprimeString("\n");
						}
						inf.clear();
					}
					inf.seekg(0);
					inf.close();
					pausa();
					limpiaPantalla();
					break; }
				case 2: {
					ifstream inf("../prueba.txt", ios::in);
					string leo;
					if (inf.fail()) {
						imprimeString("		EL FICHERO NO EXISTE\n\n");
					}
					else {
						while (!inf.eof()) {
							getline(inf, leo, '#');
							imprimeString(leo); imprimeString("\n");
						}
					}
					inf.seekg(0);
					inf.close();
					pausa();
					limpiaPantalla();
					break; }
				case 3: {
					ifstream inf("../fichas.txt", ios::in);
					string leo;
					getline(inf,leo,'*');
					if (inf.fail()) {
						imprimeString("		EL FICHERO NO EXISTE\n\n");
					}
					else {
						while (!inf.eof()) {
							getline(inf, leo, '\n');
							imprimeString(leo + "\n");
						}
					}
					inf.seekg(0);
					inf.close();
					pausa();
					limpiaPantalla();
					break; }
				case 4: {
					imprimeString("\n\nPALABBRAS BUSCADAS\n\n\n");
					juego::d->getLista()->toString();
					pausa();
					limpiaPantalla();
					break;
				}
				case 5: {
					string jugador;
					imprimeString("\n\nPALABRAS INSERTADAS POR JUGADOR\n\n");
					imprimeString(" Ingresa el nombre de usuario del jugador: "); jugador = leerString();
					if (jugador == j1->getUsuario()) {
						imprimeString("\n\n PALABRAS DEL JUGADOR: " + j1->getUsuario()); imprimeString("\n\n");
						j1->getLista()->toString();
					}
					else {
						imprimeString("\n\n PALABRAS DEL JUGADOR: " + j2->getUsuario()); imprimeString("\n\n");
						j2->getLista()->toString();
					}
					pausa();
					limpiaPantalla();
					break;
				}
				case 6: {break; }//salir
				default: { imprimeString(" Esta opci\242n no se encuentra en el men\243, por favor int\202ntelo de nuevo\n"); Sleep(2000); break; }
				}
			} while (historial != 6);
			pausa(); break;
		}
		case 3: {break; }//salir
		default: {imprimeString(" Esta opci\242n no se encuentra en el men\243, por favor int\202ntelo de nuevo\n"); Sleep(2000); break; }
		}
		limpiaPantalla();
	} while (menu != 3);
}

void juego::jugar() {
	cant = 0;
	int i = 0;
	ifstream f;
	f.open("../fichas.txt");
	string val, can, letra;
	ficha *aux = NULL;
	getline(f, letra, '*');
	while (f.good()) {
		getline(f, letra, '/');
		getline(f, val, '/');
		getline(f, can, '\n');
		if (!letra.empty() && !val.empty() && !can.empty()) {
			int valor = convertirInt(val);
			int cantidad = convertirInt(can);
			aux = new ficha(letra, valor, cantidad, cantidad);
			bolsita[i] = aux;
			i++;
			cant += cantidad;
		}
	}
	tamano = i++;
	f.close();
	bool  seguir = true;
	string u1, u2;
	int cont=1;
	imprimeString("\n\n\n			COMENCEMOS . . .\n\n\n");
	imprimeString("		Ingresa los nombres de usuario:\n");
	imprimeString("			J1: "); u1 = leerString();
	imprimeString("\n			J2: "); u2 = leerString();
	imprimeString("\n\n		Excelente " + u1 + " y " + u2+"\n\n");
	imprimeString("\n\n");
	pausa();
	limpiaPantalla();
	j1 = new  jugador(u1, 0, 0);
	j2 = new  jugador(u2, 0, 0);
	while (seguir) {
		ejecucion(j1, cont);
		if (cant > 0) {
			imprimeString("		\250Quieres continuar con la partida?(Digita 1 para s\241 o 0 para no)\n");
			seguir = leerInt();
		}
		if (seguir) {
			ejecucion(j2, cont);
		}
		if(cant > 0 && seguir){
			imprimeString("		\250Quieres continuar con la partida?(Digita 1 para s\241 o 0 para no)\n");
			seguir = leerInt();
		}
		if (j1->getPalabra()->getCant()==0 && j2->getPalabra()->getCant() == 0 && cant == 0) {
			seguir = false;
		}
		cont++;
	}
	setCursor(20, 11); imprimeString("USUARIO:"); setCursor(39, 11); imprimeString(j1->getUsuario()); setCursor(48, 11); imprimeString(j2->getUsuario());
	setCursor(20, 12); imprimeString("PUNTAJE:"); setCursor(39, 12); imprimeInt(j1->getPuntaje()); setCursor(48, 12); imprimeInt(j2->getPuntaje());
	setCursor(20, 13); imprimeString("FICHAS SOBRANTES:"); setCursor(39, 13); imprimeString(j1->getPalabra()->toString()); setCursor(48, 13); imprimeString(j2->getPalabra()->toString());
	setCursor(20, 14); imprimeString("PUNTOS A RESTAR:"); setCursor(39, 14); imprimeInt(j1->getPalabra()->sumaFichasRest()); setCursor(48, 14); imprimeInt(j2->getPalabra()->sumaFichasRest());
	j1->setPuntaje(j1->getPuntaje() - j1->getPalabra()->sumaFichasRest());
	j2->setPuntaje(j2->getPuntaje() - j2->getPalabra()->sumaFichasRest());
	setCursor(20, 15); imprimeString("PUNTAJE FINAL:"); setCursor(39, 15); imprimeInt(j1->getPuntaje()); setCursor(48, 15); imprimeInt(j2->getPuntaje());
	if (j1->getPuntaje() > j2->getPuntaje()) {
		j1->setPganadas(j1->getPganadas() + 1);
		setCursor(37, 15); imprimeString(" \255\255\255FELICIDADES " + j1->getUsuario() + " HAS GANADO ESTA PARTIDA!!!");
	}
	else {
		if (j1->getPuntaje() == j2->getPuntaje()) {
			j1->setPganadas(j1->getPganadas() + 1);
			j2->setPganadas(j2->getPganadas() + 1);
			setCursor(37, 15); imprimeString(" \255\255\255FELICIDADES " + j1->getUsuario() + " Y " + j2->getUsuario() + " HA SIDO UN EMPATE, AMBOS HAN GANADO ESTA PARTIDA!!!");
		}
		else {
			j2->setPganadas(j2->getPganadas() + 1);
			setCursor(37, 15); imprimeString(" \255\255\255FELICIDADES " + j2->getUsuario() + " HAS GANADO ESTA PARTIDA!!!");
		}
	}
	setCursor(27, 22); imprimeString("PALABRAS GANADORAS DE " + j1->getUsuario() + " Y " + j2->getUsuario());
	setCursor(22, 24); imprimeString(j1->getUsuario()); setCursor(32, 24); imprimeString(j2->getUsuario());
	setCursor(22, 26); j1->getLista()->toString(); setCursor(32, 26); j2->getLista()->toString();
	pausa();
	limpiaPantalla();
	delete j1;
	delete j2;
	for (int i = 0; i < tamano; i++) {
		delete bolsita[i];
	}
}

bool juego::insertarPalabra(jugador *jug, int fila_Inicial, int columna_Inicial, bool direccion) {
	string palabra = jug->getPalabra()->getLaPalabra(), letra;
	int iterador_Palabra = 0, cantidad_Letras = palabra.length(), cantidad, a,posicion_Ficha;
	ficha **fichas = new ficha*[cantidad_Letras];
	for (iterador_Palabra = 0; iterador_Palabra < cantidad_Letras; iterador_Palabra++) {
		fichas[iterador_Palabra] = NULL;// vector que guarda las fichas
	}
	iterador_Palabra = 0;// Reiniciar el iterador
	if (direccion) {// Direccion Vertical
		cantidad = cantidad_Letras + fila_Inicial; //Extension de la palabra
		for (a = fila_Inicial; a < cantidad; a++) {//Iteran las filas, la columna es la misma
			letra = StringChar(palabra[iterador_Palabra]);// Conversion de Char --> string
			if (tab.getFicha(a, columna_Inicial) == NULL) {// En esa posicion no existe una ficha
				posicion_Ficha = jug->getPalabra()->buscarLetra(letra);//Busque la ficha en el atril del jugador
				if (posicion_Ficha == -1) {// No existe esa ficha?
					for (iterador_Palabra = 0 ; iterador_Palabra < cantidad_Letras; iterador_Palabra++) {
						// En caso de que falte una ficha debo devolverle todas al usuario
						if (fichas[iterador_Palabra] != NULL) {
							jug->getPalabra()->insertarFicha(fichas[iterador_Palabra]);
							fichas[iterador_Palabra] = NULL;
						}
						//-1 por que iterador_Palabra es cantidad
					}
					setCursor(86, 42); imprimeString("Lo sentimos no encontramos la ficha [ " + letra + " ] en su atril");
					setCursor(86, 43); imprimeString("Para la palabra [ " + palabra + " ]");
					Sleep(2000);
					return false;
				}
				//Si la ficha existe guardela en un vector
				fichas[iterador_Palabra] = jug->getPalabra()->getFicha(posicion_Ficha);
				jug->getPalabra()->eliminarFicha(posicion_Ficha);
				iterador_Palabra++;
			}
			else {// En esa posicion  existe ficha
				if (tab.getFicha(a, columna_Inicial)->getLetra() != letra) {//Esa ficha es diferente de la que deseo ingresar
					for (iterador_Palabra = 0; iterador_Palabra < cantidad_Letras; iterador_Palabra++) {
						// En caso de que falte una ficha debo devolverle todas al usuario
						if (fichas[iterador_Palabra] != NULL) {
							jug->getPalabra()->insertarFicha(fichas[iterador_Palabra]);
							fichas[iterador_Palabra] = NULL;
						}
						//-1 por que iterador_Palabra es cantidad
					}
					setCursor(86, 42); imprimeString("Lo sentimos su Palabra [ " + palabra + " ]");
					setCursor(86, 43); imprimeString("En la posicion de la Letra [ " + letra + " ] No es compatible");
					setCursor(86, 44); imprimeString("Con las fichas del tablero");
					Sleep(2000);
					return false;
				}
				//Si la ficha ya esta en el tablero no debo quitarla se queda ahi
				// solo continue
				iterador_Palabra++;//Si es la misma continue
			}
		}
		iterador_Palabra = 0;
		for (a = fila_Inicial; a < cantidad; a++, iterador_Palabra++) {
			if (tab.getFicha(a, columna_Inicial) == NULL) {
				tab.setFicha(a, columna_Inicial, fichas[iterador_Palabra]);
			}
		}
		setCursor(86, 42); imprimeString("TU PALABRA SE HA INSERTADO CORRECTAMENTE EN EL TABLERO");
		premio(jug, cantidad, fila_Inicial, columna_Inicial, direccion);
		Sleep(4000);
		return true;
	}
	else {
		{// Direccion Horizontal
			cantidad = cantidad_Letras + columna_Inicial; //Extension de la palabra
			for (a = columna_Inicial; a < cantidad; a++) {//Iteran las filas, la columna es la misma
				letra = StringChar(palabra[iterador_Palabra]);// Conversion de Char --> string
				if (tab.getFicha(fila_Inicial,a) == NULL) {// En esa posicion no existe una ficha
					posicion_Ficha = jug->getPalabra()->buscarLetra(letra);//Busque la ficha en el atril del jugador
					if (posicion_Ficha == -1) {// No existe esa ficha?
						for (iterador_Palabra = 0; iterador_Palabra < cantidad_Letras; iterador_Palabra++) {
							// En caso de que falte una ficha debo devolverle todas al usuario
							if (fichas[iterador_Palabra] != NULL) {
								jug->getPalabra()->insertarFicha(fichas[iterador_Palabra]);
								fichas[iterador_Palabra] = NULL;
							}
							//-1 por que iterador_Palabra es cantidad
						}
						setCursor(86, 42); imprimeString("Lo sentimos no encontramos la ficha [ " + letra + " ] en su atril");
						setCursor(86, 43); imprimeString("Para la palabra [ " + palabra + " ]");
						Sleep(2000);
						return false;
					}
					//Si la ficha existe guardela en un vector
					fichas[iterador_Palabra] = jug->getPalabra()->getFicha(posicion_Ficha);
					jug->getPalabra()->eliminarFicha(posicion_Ficha);
					iterador_Palabra++;
				}
				else {// En esa posicion  existe ficha
					if (tab.getFicha(fila_Inicial, a)->getLetra() != letra) {//Esa ficha es diferente de la que deseo ingresar
						for (iterador_Palabra = 0; iterador_Palabra < cantidad_Letras; iterador_Palabra++) {
							// En caso de que falte una ficha debo devolverle todas al usuario
							if (fichas[iterador_Palabra] != NULL) {
								jug->getPalabra()->insertarFicha(fichas[iterador_Palabra]);
								fichas[iterador_Palabra] = NULL;
							}
							//-1 por que iterador_Palabra es cantidad
						}
						setCursor(86, 42); imprimeString("Lo sentimos su Palabra [ " + palabra + " ]");
						setCursor(86, 43); imprimeString("En la posicion de la Letra [ " + letra + " ] No es compatible");
						setCursor(86, 44); imprimeString("Con las fichas del tablero");
						Sleep(2000);
						return false;
					}
					//Si la ficha ya esta en el tablero no debo quitarla se queda ahi
					// solo continue
					iterador_Palabra++;//Si es la misma continue
				}
			}
			iterador_Palabra = 0;
			for (a = columna_Inicial; a < cantidad; a++, iterador_Palabra++) {
				if (tab.getFicha(fila_Inicial, a) == NULL) {
					tab.setFicha(fila_Inicial, a, fichas[iterador_Palabra]);
				}
			}
			setCursor(86, 42); imprimeString("TU PALABRA SE HA INSERTADO CORRECTAMENTE EN EL TABLERO");
			premio(jug, cantidad, fila_Inicial, columna_Inicial, direccion);
			Sleep(4000);
			return true;
		}
	}
}

void juego::premio(jugador *jAux, int can, int filIni, int colIni, bool direccion) {
	int bonoPalabra = 1;
	int suma = 0;
	int _palabra = 0;
	if (direccion) {//Vertical
		for (int a = filIni; a < can; a++) {
			cout << "REVISANDO LA LETRA " << tab.getFicha(a, colIni)->getLetra() << "\n";
			cout << " Su valor es: " << tab.getFicha(a, colIni)->getValor() << "\n";
			suma += tab.getFicha(a, colIni)->getValor() * numpremio(a, colIni, bonoPalabra);
			cout << "LA SUMA VA EN " << suma << "\n";
			_palabra += tab.getFicha(a, colIni)->getValor();
			cout << "LA PALABRA VA EN " << _palabra << "\n";
		}
	}
	else {//Horizontal
		for (int a = colIni; a < can; a++) {
			cout << "REVISANDO LA LETRA " << tab.getFicha(filIni, a)->getLetra() << "\n";
			cout << " Su valor es: " << tab.getFicha(filIni, a)->getValor()<<"\n";
			suma += tab.getFicha(filIni, a)->getValor() * numpremio(filIni, a, bonoPalabra);
			cout << "LA SUMA VA EN " << suma<<"\n";
			_palabra += tab.getFicha(filIni, a)->getValor();
			cout << "LA PALABRA VA EN " << _palabra<<"\n";
		}
	}
	jAux->getPalabra()->setValorSimple(_palabra); setCursor(86, 43); 
	imprimeString("Puntos simples: "); imprimeInt(_palabra);

	 setCursor(86, 44);  jAux->getPalabra()->setBonos(suma * bonoPalabra - _palabra);
	 imprimeString("Bonos: "); imprimeInt(suma*bonoPalabra - _palabra);
	
	setCursor(86, 45); jAux->getPalabra()->setValorTotal(suma * bonoPalabra);
	imprimeString("Puntos Totales: "); imprimeInt(suma*bonoPalabra);

	if (jAux->getPalabra()->getCant() == 0) {
		jAux->getPalabra()->setBonos(jAux->getPalabra()->getBonos() + 100);
	}

	jAux->setPuntaje(jAux->getPuntaje() + jAux->getPalabra()->getValorTotal());
	pausa();
}

int juego::numpremio(int i, int a, int &bonoPalabra) {
	switch (tab.casillaPremios(i,a)) {
	case 8: {return 1; break; }//Gris NADA
	case 9: { bonoPalabra*= 3; return 1; break; }// Azul Brillante 3 X VALOR PALABRA
	case 10: {bonoPalabra*= 2; return 1; break; }// Verde Brillante 2 X VALOR PALABRA
	case 13: {return 2; break; }// Morado brillante 2 X VALOR LETRA
	case 14: {return 3; break; }// Amarillo Brillante 3 X VALOR DE LETRA
	case 15: {return 1; break; }// blanco NADA
	default: {return 1; break; }
	}
}

bool juego::fichasAleatorias(jugador* j) {
	/**A/1/12
B/3/2
C/3/4
D/2/5
E/2/12
F/4/1
G/2/2
H/4/2
I/1/6
J/8/1
K/8/1
L/6/4
M/3/2
N/2/5
O/1/9
P/3/2
Q/5/1
R/1/5
S/1/6
T/1/4
U/1/5
V/4/1
W/8/1
X/8/1
Y/4/1
Z/9/1
 /0/2*/
	bool bandera=true;
	int numero;
	int cantidad;
	if (cant>=7) {
		while (bandera) {
			cantidad = j->getPalabra()->getCant();
			if (cantidad < 7) {
				numero = rand() % tamano;
				if (0 <= numero && numero <= tamano) {
					if (bolsita[numero]->getDisponibles() > 0) {
						bolsita[numero]->setDisponibles(bolsita[numero]->getDisponibles() - 1);
						j->getPalabra()->insertarFicha(bolsita[numero]);
						cantidad++;
						cant--;
						j->getPalabra()->setCant(cantidad);
					}
				}
			}
			else { bandera = false; }
		}
	}
	else {
		if (cant >= 0) {
			for (int i = 0; i < tamano; i++) {
				cantidad = j->getPalabra()->getCant();
				if (cantidad < 7) {
					while (bolsita[i]->getDisponibles() > 0) {
						bolsita[i]->setDisponibles(bolsita[i]->getDisponibles() - 1);
						j->getPalabra()->insertarFicha(bolsita[i]);
						cantidad++;
						j->getPalabra()->setCant(cantidad);
						cant--;
					}
				}
				else {
					return true;
				}
			}
		}
		else {
			return false;
		}
	}
	return true;
}

void juego::ejecucion(jugador* j, int turno) {
	tab.toString(bolsita);
	bool bandera = true;
	string pFormada;
	int columna, fila;
	char col; bool dir;
	fichasAleatorias(j);
	if (j->getPalabra()->getCant()>0) {
		int menu = 4;
		bool pasar = true;
		do {
			setCursor(83, 29); imprimeString("  TURNO DE " + j->getUsuario());
			setCursor(83, 31); imprimeString("Estas son tus fichas ");
			setCursor(83, 32); imprimeString(j->getPalabra()->toString());
			setCursor(83, 34); imprimeString("TIENES ESTAS OPCIONES");
			setCursor(83, 35); imprimeString("1) Insertar una palabra");
			setCursor(83, 36); imprimeString("2) Cambiar tus fichas (Pierdes un turno y NO ganar\240s puntos)");
			setCursor(83, 37); imprimeString("3) Pasar turno (NO ganar\240s puntos)");
			setCursor(83, 38); imprimeString("CU\265L ELEG\326S?: "); setCursor(83, 40); menu = leerInt();
			switch (menu) {
			case 1: {
				limpiaPantalla(); tab.toString(bolsita);
				setCursor(83, 29); imprimeString("  TURNO DE " + j->getUsuario());
				setCursor(83, 31); imprimeString("Estas son tus fichas ");
				setCursor(83, 32); imprimeString(j->getPalabra()->toString());
				setCursor(83, 33); imprimeString("Ahora a formar una palabra, buena suerte :D");
				setCursor(83, 34); imprimeString("\377 PALABRA: "); pFormada = leerString();
				//if (d->buscarPalabra(pFormada)) {
				setCursor(83, 35); imprimeString("\377 POSICION INICIAL ");
				setCursor(83, 36); imprimeString("   FILA (n\243mero): ");
				while (bandera) {
					fila = leerInt();
					fila = fila - 1;
					if (fila >= 0 && fila <= 13) {
						bandera = false;
					}
					else {
						limpiarBuffer(); setCursor(83, 37); imprimeString("Este valor es incorrecto, por favor");
						setCursor(83, 38); 	imprimeString("   digita un NUMERO de 1 a 13");
					}
				}
				bandera = true;
				setCursor(83, 38); imprimeString("   COLUMNA (letra): ");
				while (bandera) {
					col = leerChar();
					columna = convertirLetra(col);
					if (columna != -1) {
						bandera = false;
					}
					else {
						setCursor(83, 39); imprimeString("Este valor es incorrecto, por favor");
						setCursor(83, 40); imprimeString("   digita una LETRA de A a M");
						limpiarBuffer();
					}
				}
				bandera = true;
				setCursor(83, 39); imprimeString("	  DIRECCION DE LA PALABRA ");
				setCursor(83, 40); imprimeString("(Digita H para HORIZONTAL y V para VERTICAL) : ");
				while (bandera) {
					char direccion = leerChar();
					if (direccion == 'h' || direccion == 'H' || direccion == 'v' || direccion == 'V') {
						if (direccion == 'h' || direccion == 'H') {
							dir = false;
						}
						else {
							dir = true;
						}
						bandera = false;
					}
					else {
						setCursor(83, 41); imprimeString("Este valor es incorrecto, por favor digita");
						setCursor(83, 42); imprimeString("una LETRA H para horizontal o una V para vertical");
						limpiarBuffer();
					}
				}
				bandera = true;
				if (cabe(pFormada, fila, columna, dir)) {
					j->getPalabra()->setLaPalabra(pFormada);
					insertarPalabra(j, fila, columna, dir); 
				}
				else {
					setCursor(83, 43); imprimeString("LO SENTIMOS LA PALABRA NO ESTA EN LAS DIMENSIONES");
					setCursor(83, 44); imprimeString("DEL TABLERO, NO GANASTE PUNTOS."); Sleep(2000);
				}
				/*}
				else {
					setCursor(83, 35); imprimeString("LO SENTIMOS LA PALABRA NO EXISTE EN EL");
					setCursor(83, 36); imprimeString(" DICCIONARIO NO GANASTE PUNTOS."); Sleep(2000);
				}*/
				limpiaPantalla();
				tab.toString(bolsita);
				setCursor(83, 29); imprimeString("PUNTAJE DEL TURNO ("); imprimeInt(turno); imprimeString(") de " + j->getUsuario());
				setCursor(83, 30); imprimeString("		PUNTAJE: "); imprimeInt(j->getPuntaje());
				if (j->getPalabra()->getCant()>0) {
					setCursor(83, 31); imprimeString("TE QUEDAN ESTAS FICHAS EN TU ATRIL: ");
					setCursor(83, 32); imprimeString(j->getPalabra()->toString());
				}else{ setCursor(83, 31); imprimeString("Ya no hay fichas en tu atril"); }
				pasar = false;
				break; }
			case 2: {
				while (j->getPalabra()->getCant() > 0) {
					string letra = j->getPalabra()->getFicha(0)->getLetra();
					ficha*aux = GETFICHA(letra);
					int cantidad = aux->getDisponibles();
					j->getPalabra()->eliminarFicha(0);
					aux->setDisponibles(cantidad + 1);
					cant++;
				}
				fichasAleatorias(j);
				setCursor(83, 40); imprimeString("Estas son tus NUEVAS fichas ");
				setCursor(83, 41); imprimeString(j->getPalabra()->toString());
				pasar = false;
				break;
			}
			case 3: {pasar = false; break; }
			default: {setCursor(83, 39); imprimeString(" Esta opci\242n no se encuentra en el men\243, por favor");
				setCursor(83, 40); imprimeString("       int\202ntelo de nuevo\n"); Sleep(2000); break; }
			}
		} while (menu != 3 && pasar);
	}
	pausa();
	limpiaPantalla();
}

bool juego::cabe(string p, int filIni, int colIni, bool direccion) {
	int can = p.length();
	if (direccion) {
		if (can + filIni <= 13) {
			return true;
		}
	}
	else {
		if (can + colIni <= 13) {
			return true;
		}
	}
	return false;
}

juego::~juego() {
	delete d;
	delete j1;
	delete j2;
	for (int i = 0; i < tamano; i++) {
		delete bolsita[i];
	}
}