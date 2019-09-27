#include "Gato.h"

Gato::Gato(){}

Gato::~Gato(){}

void Gato::jugar() {
	int opcion,x,y;
	int eleccion;
	int marca;
	int disponibles;
	bool turno = true;
	bool bandera = true;
	string marca_Mia;
	string marca_Oponente;
	int modalidad;
	string vector[3] = { "Juego Nuevo","Historial","Salir" };
	string seleccion[5] = { "MultiJugador","CPU-Facil","CPU-Normal","CPU-Dificil","Atras" };
	string marcas[2] = { "X","O" };
	do {
		do {
			x = 12, y = 5;
			system("cls");
			imprimeMarcoDoble(x, y, 17, 41, 15, "H", 14, 6);
			opcion = menuSeleccionLista(x + 12, y + 5, vector, 3, 14, 15, true);
			system("cls");
			disponibles = 9;
			switch (opcion) {
			case 1: {
				tab = new tablero();
				j1 = new jugador();
				j2 = new jugador();
				imprimeMarcoDoble(x, y, 17, 49, 15, "H", 14, 6);
				modalidad = menuSeleccionCuadrilatero(x + 12, y + 5, 2 , 3 , seleccion , 5 , 14 , 15 );
				system("cls");
				if (modalidad != 5) {
					imprimeMarcoDoble(x, y, 17, 41, 15, "H", 14, 6);
					marca = menuSeleccionLista(x + 12, y + 5, marcas, 2, 14, 15, true);
					(marca == 1) ? marca_Mia ="X": marca_Mia = "O";
					(marca == 1) ? marca_Oponente ="O": marca_Oponente = "X";
					system("cls");
					x += 4;
					imprimeMarcoDoble(x - 5, y - 4, 30, 49, 14, " ", 10, 6);
					while (!Ganador_Diagonal() && !Ganador_Horizontal() && !Ganador_Vertical() && disponibles > 0) {
						tab->toString(x + 5, y + 2);
						setCursor(10, 33); imprimeString("                                            ");
						if (turno) {
							while (bandera) {
								eleccion = seleccionGato(x + 8, y + 10);
								mostrarCursor(false);
								if (tab->getPos(eleccion) == " ") {
									tab->setPos(eleccion, marca_Oponente);
									bandera = false;
								}
								else {
									setCursor(10, 33); imprimeString("Este espacio ya esta ocupado selecciona otro");
								}
							}
							bandera = true;
						}
						else {
							switch (modalidad) {
							case 1: {
								while (bandera) {
									eleccion = seleccionGato(x + 8, y + 10);
									mostrarCursor(false);
									if (tab->getPos(eleccion) == " ") {
										tab->setPos(eleccion, marca_Mia);
										bandera = false;
									}
									else {
										setCursor(10, 33); imprimeString("Este espacio ya esta ocupado selecciona otro");
									}
								}
								bandera = true;
								break; }
							case 2: {jugar_IA_Facil(marca_Mia,marca_Oponente); break; }
							case 3: {jugar_IA_Normal(marca_Mia, marca_Oponente); break; }
							case 4: {jugar_IA_Dificil(marca_Mia, marca_Oponente); break; }
							}
						}
						disponibles--;
						turno = !turno;
					}
					tab->toString(x + 5, y + 2); setCursor(10, 33);
					if (disponibles == 0 && !(Ganador_Diagonal() || Ganador_Horizontal() || Ganador_Vertical())) {
						imprimeString("Ha sido un Empate");
					}
					else {
						(!turno) ? imprimeString("Felicidades has ganado\n") : imprimeString("Lastima, buen intento\n");
					}
					system("pause");
					system("cls");
					delete tab;
					delete j1;
					delete j2;
				}
				break; }
			case 2: {break; }
			case 3: {break; }
			}
		} while (opcion != 3);
		imprimeMarcoDoble(x, y, 17, 41, 15, "H", 14, 6);
		string opciones[3] = { "Cancelar","Confirmar" };
		opcion = menuSeleccionLista(x + 12, y + 5, opciones, 2, 14, 15, true);
	} while (opcion != 2);

}

int Gato::jugar_IA_Facil(string marca_Mia, string marca_Oponente) {
	int marca;
	marca = priorizar(marca_Mia); // Ganar
	if (marca == -1) {
		marca = priorizar(marca_Oponente); // Bloquear
		if (marca == -1) {
			marca = revisar_Centro(marca_Mia);
			if (marca != -1) {
				tab->setPos(marca, marca_Mia);
				return marca;
			}
			marca = revisar_Primero(marca_Mia);
			if (marca != -1) {
				tab->setPos(marca, marca_Mia);
				return marca;
			}
			marca = revisar_Ultimo(marca_Mia);
			if (marca != -1) {
				tab->setPos(marca, marca_Mia);
				return marca;
			}
			for (int i = 0; i < 9; i++) {
				if (tab->getPos(i) == " ") {
					tab->setPos(i, marca_Mia);
					return marca;
				}
			}
		}
		else {
			tab->setPos(marca, marca_Mia);
			return marca;
		}
	}
	else {
		tab->setPos(marca, marca_Mia);
		return marca;
	}
	return -1;
}

int Gato::jugar_IA_Normal(string marca_Mia, string marca_Oponente) {
	int marca;
	marca = priorizar(marca_Mia); // Ganar
	if (marca == -1) {
		marca = priorizar(marca_Oponente); // Bloquear
		if (marca == -1) {
			if (tab->getPos(4) == " ") {
				tab->setPos(4, marca_Mia);
				return 4;
			}
			if (tab->getPos(0) == marca_Oponente && tab->getPos(8) == " ") {
				tab->setPos(8, marca_Mia);
				return 8;
			}
			if (tab->getPos(8) == marca_Oponente && tab->getPos(0) == " ") {
				tab->setPos(0, marca_Mia);
				return 0;
			}
			if (tab->getPos(2) == marca_Oponente && tab->getPos(6) == " ") {
				tab->setPos(6, marca_Mia);
				return 6;
			}
			if (tab->getPos(6) == marca_Oponente && tab->getPos(2) == " ") {
				tab->setPos(2, marca_Mia);
				return 2;
			}
			marca = revisar_Centro(marca_Mia);
			if (marca != -1) {
				tab->setPos(marca, marca_Mia);
				return marca;
			}
			marca = revisar_Primero(marca_Mia);
			if (marca != -1) {
				tab->setPos(marca, marca_Mia);
				return marca;
			}
			marca = revisar_Ultimo(marca_Mia);
			if (marca != -1) {
				tab->setPos(marca, marca_Mia);
				return marca;
			}
			for (int i = 0; i < 9; i++) {
				if (tab->getPos(i) == " ") {
					tab->setPos(i, marca_Mia);
					return marca;
				}
			}
		}
		else {
			tab->setPos(marca, marca_Mia);
			return marca;
		}
	}
	else {
		tab->setPos(marca, marca_Mia);
		return marca;
	}
	return -1;
}

int Gato::jugar_IA_Dificil(string marca_Mia, string marca_Oponente){
	int marca;
	marca = priorizar(marca_Mia); // Ganar
	if (marca == -1) {
		marca = priorizar(marca_Oponente); // Bloquear
		if (marca == -1) {
			if (tab->getPos(1) == marca_Oponente && tab->getPos(6) == marca_Oponente && (tab->getPos(3) == " " || tab->getPos(5) == " ")) {
				if (tab->getPos(3) == " ") {
					tab->setPos(3, marca_Mia);
					return 3;
				}
				else {
					tab->setPos(5, marca_Mia);
					return 5;
				}
			}
			if (tab->getPos(3) == marca_Oponente && tab->getPos(2) == marca_Oponente && tab->getPos(0) == " ") {
				tab->setPos(0, marca_Mia);
				return 0;
			}
			if (tab->getPos(3) == marca_Oponente && tab->getPos(1) == marca_Oponente && (tab->getPos(6) == " " || tab->getPos(2) == " ")) {
				if (tab->getPos(6) == " ") {
					tab->setPos(6, marca_Mia);
					return 6;
				}
				else {
					tab->setPos(2, marca_Mia);
					return 2;
				}
			}
			if (tab->getPos(4) == " ") {
				tab->setPos(4, marca_Mia);
				return 4;
			}
			if (tab->getPos(4) == marca_Mia) {
				if ((tab->getPos(6) == marca_Oponente && tab->getPos(2) == marca_Oponente) || (tab->getPos(0) == marca_Oponente && tab->getPos(8) == marca_Oponente)) {
					//Revision Horizontal de 3,4,5
					if ((tab->getPos(3) == " " || tab->getPos(3) == marca_Mia) && (tab->getPos(4) == " " || tab->getPos(4) == marca_Mia) && (tab->getPos(5) == " " || tab->getPos(5) == marca_Mia)) {
						if ((tab->getPos(3) == marca_Mia || tab->getPos(4) == marca_Mia) && (tab->getPos(5) == " ")) {
							tab->setPos(5, marca_Mia);
							return 5; // [X][M][ ] //  [ ][M][X]
						}
						else {
							if (tab->getPos(5) == marca_Mia && tab->getPos(3) == " ") {
								tab->setPos(3, marca_Mia);
								return 3; // [M][X][ ]
							}
						}

					}// sino en algun lado hay un X
					// Comenzar //Revision Vertical de 1,4,7
					if ((tab->getPos(1) == " " || tab->getPos(1) == marca_Mia) && (tab->getPos(4) == " " || tab->getPos(4) == marca_Mia) && (tab->getPos(7) == " " || tab->getPos(7) == marca_Mia)) {
						if ((tab->getPos(1) == marca_Mia || tab->getPos(4) == marca_Mia) && (tab->getPos(7) == " ")) {
							tab->setPos(7, marca_Mia);
							return 7; // [X][M][ ] //  [ ][M][X]
						}
						else {
							if (tab->getPos(7) == marca_Mia && tab->getPos(1) == " ") {
								tab->setPos(1, marca_Mia);
								return 1; // [M][X][ ]
							}
						}

					}// sino en algun lado hay un X
				}
				marca = revisar_Centro(marca_Mia);
				if (marca != -1) {
					tab->setPos(marca, marca_Mia);
					return marca;
				}
			}
			else {
				int num = rand() % 4;
				switch (num) {
				case 0: {
					if (tab->getPos(0) == " " && (tab->getPos(6) != marca_Oponente || tab->getPos(2) != marca_Oponente)) {
						tab->setPos(0, marca_Mia);
						return 0;
					}
					if (tab->getPos(8) == " " && (tab->getPos(6) != marca_Oponente || tab->getPos(2) != marca_Oponente)) {
						tab->setPos(8, marca_Mia);
						return 8;
					}
					if (tab->getPos(6) == " " && (tab->getPos(0) != marca_Oponente || tab->getPos(8) != marca_Oponente)) {
						tab->setPos(6, marca_Mia);
						return 6;
					}
					if (tab->getPos(2) == " " && (tab->getPos(0) != marca_Oponente || tab->getPos(8) != marca_Oponente)) {
						tab->setPos(2, marca_Mia);
						return 2;
					}
					break; }
				case 1: {
					if (tab->getPos(8) == " " && (tab->getPos(6) != marca_Oponente || tab->getPos(2) != marca_Oponente)) {
						tab->setPos(8, marca_Mia);
						return 8;
					}
					if (tab->getPos(6) == " " && (tab->getPos(0) != marca_Oponente || tab->getPos(8) != marca_Oponente)) {
						tab->setPos(6, marca_Mia);
						return 6;
					}
					if (tab->getPos(2) == " " && (tab->getPos(0) != marca_Oponente || tab->getPos(8) != marca_Oponente)) {
						tab->setPos(2, marca_Mia);
						return 2;
					}
					if (tab->getPos(0) == " " && (tab->getPos(6) != marca_Oponente || tab->getPos(2) != marca_Oponente)) {
						tab->setPos(0, marca_Mia);
						return 0;
					}
					break; }
				case 2: {
					if (tab->getPos(6) == " " && (tab->getPos(0) != marca_Oponente || tab->getPos(8) != marca_Oponente)) {
						tab->setPos(6, marca_Mia);
						return 6;
					}
					if (tab->getPos(2) == " " && (tab->getPos(0) != marca_Oponente || tab->getPos(8) != marca_Oponente)) {
						tab->setPos(2, marca_Mia);
						return 2;
					}
					if (tab->getPos(0) == " " && (tab->getPos(6) != marca_Oponente || tab->getPos(2) != marca_Oponente)) {
						tab->setPos(0, marca_Mia);
						return 0;
					}
					if (tab->getPos(8) == " " && (tab->getPos(6) != marca_Oponente || tab->getPos(2) != marca_Oponente)) {
						tab->setPos(8, marca_Mia);
						return 8;
					}
					break; }
				case 3: {
					if (tab->getPos(2) == " " && (tab->getPos(0) != marca_Oponente || tab->getPos(8) != marca_Oponente)) {
						tab->setPos(2, marca_Mia);
						return 2;
					}
					if (tab->getPos(0) == " " && (tab->getPos(6) != marca_Oponente || tab->getPos(2) != marca_Oponente)) {
						tab->setPos(0, marca_Mia);
						return 0;
					}
					if (tab->getPos(8) == " " && (tab->getPos(6) != marca_Oponente || tab->getPos(2) != marca_Oponente)) {
						tab->setPos(8, marca_Mia);
						return 8;
					}
					if (tab->getPos(6) == " " && (tab->getPos(0) != marca_Oponente || tab->getPos(8) != marca_Oponente)) {
						tab->setPos(6, marca_Mia);
						return 6;
					}
					break; }
				}
			}
			if (tab->getPos(0) == marca_Oponente && tab->getPos(8) == " ") {
				tab->setPos(8, marca_Mia);
				return 8;
			}
			if (tab->getPos(8) == marca_Oponente && tab->getPos(0) == " ") {
				tab->setPos(0, marca_Mia);
				return 0;
			}
			if (tab->getPos(2) == marca_Oponente && tab->getPos(6) == " ") {
				tab->setPos(6, marca_Mia);
				return 6;
			}
			if (tab->getPos(6) == marca_Oponente && tab->getPos(2) == " ") {
				tab->setPos(2, marca_Mia);
				return 2;
			}
			marca = revisar_Centro(marca_Mia);
			if (marca != -1) {
				tab->setPos(marca, marca_Mia);
				return marca;
			}
			if (tab->getPos(4) == " ") {
				tab->setPos(4, marca_Mia);
				return 4;
			}
			marca = revisar_Primero(marca_Mia);
			if (marca != -1) {
				tab->setPos(marca, marca_Mia);
				return marca;
			}
			marca = revisar_Ultimo(marca_Mia);
			if (marca != -1) {
				tab->setPos(marca, marca_Mia);
				return marca;
			}
			for (int i = 0; i < 9; i++) {
				if (tab->getPos(i) == " ") {
					tab->setPos(i, marca_Mia);
					return marca;
				}
			}
		}
		else {
			tab->setPos(marca, marca_Mia);
			return marca;
		}
	}
	else {
		tab->setPos(marca, marca_Mia);
		return marca;
	}
	return -1;
}

int Gato::revisar_Primero(string marca){
	//Comenzar Revision Horizontal de 0,1,2
	if ((tab->getPos(0)!=" "|| tab->getPos(0) != marca) && (tab->getPos(1) != " " || tab->getPos(1) != marca) && (tab->getPos(2) != " " || tab->getPos(2) != marca)) {
		if (tab->getPos(0) == " " && tab->getPos(1) == " " && tab->getPos(2) == " ") {
			return 1;// [ ][M][ ]
		}
		else {
			if ((tab->getPos(0) == marca ||tab->getPos(2) == marca) && (tab->getPos(1) == " ")) {
				return 1; // [X][M][ ] //  [ ][M][X]
			}
			else {
				if (tab->getPos(1) == marca && tab->getPos(0)==" ") {
					return 0; // [M][X][ ]
				}
			}
		}
	}// sino en algun lado hay un X
	// Comenzar Revision Vertical de 0,3,6
	if ((tab->getPos(0) != " " || tab->getPos(0) != marca) && (tab->getPos(3) != " " || tab->getPos(3) != marca) && (tab->getPos(6) != " " || tab->getPos(6) != marca)) {
		if (tab->getPos(0) == " " && tab->getPos(3) == " " && tab->getPos(6) == " ") {	//[ ]
			return 3;																	//[M]
		}																				//[ ]
		else {
			if ((tab->getPos(0) == marca || tab->getPos(6) == marca) && (tab->getPos(3) == " ")) {	//[X]     [ ]  
				return 3;												//[M]  o  [M]
			}															//[ ]     [X]
			else {
				if (tab->getPos(3) == marca && tab->getPos(0) == " ") {	// [M]
					return 0;											// [X]
				}														// [ ]
			}
		}
	}// sino en algun lado hay un X
	return -1;// Lo mejor es marcar en otro sitio
}

int Gato::revisar_Centro(string marca) {
	//Revision Diagonal de 0,4,8
	if ((tab->getPos(0) == " " || tab->getPos(0) == marca) && (tab->getPos(4) == " " || tab->getPos(4) == marca) && (tab->getPos(8) == " " || tab->getPos(8) == marca)) {
		if ((tab->getPos(0) == marca || tab->getPos(4) == marca) && (tab->getPos(8) == " ")) {	//[X]         [ ]  
			return 8;																			//   [M]    o   [M]
		}																						//      [ ]       [X]
		else {
			if ((tab->getPos(4) == marca || tab->getPos(8) == marca) && tab->getPos(0) == " ") {	// [M]
				return 0;											//    [X]
			}														//       [ ]

		}
	}// sino en algun lado hay un X
	//Revision Diagonal de 6,4,2
	if ((tab->getPos(6) == " " || tab->getPos(6) == marca) && (tab->getPos(4) == " " || tab->getPos(4) == marca) && (tab->getPos(2) == " " || tab->getPos(2) == marca)) {
		if ((tab->getPos(6) == marca || tab->getPos(2) == marca) && (tab->getPos(4) == " ")) {	//[X]         [ ]  
				return 4;																			//  [M]    o   [M]
		}																						//    [ ]       [X]
		else {
			if ((tab->getPos(4) == marca || tab->getPos(2) == marca) && tab->getPos(6) == " ") {	// [ ]
				return 6;											//   [X]
			}														//    [M]
		}
	}// sino en algun lado hay un X
	//Revision Horizontal de 3,4,5
	if ((tab->getPos(3) == " " || tab->getPos(3) == marca) && (tab->getPos(4) == " " || tab->getPos(4) == marca) && (tab->getPos(5) == " " || tab->getPos(5) == marca)) {
		if (tab->getPos(3) == " " && tab->getPos(4) == " " && tab->getPos(5) == " ") {
			return 7;// [ ][ ][ ]
		}
		else {
			if ((tab->getPos(3) == marca || tab->getPos(4) == marca) && (tab->getPos(5) == " ")) {
				return 5; // [X][M][ ] //  [ ][M][X]
			}
			else {
				if (tab->getPos(5) == marca && tab->getPos(3) == " ") {
					return 3; // [M][X][ ]
				}
			}
		}
	}// sino en algun lado hay un X
	// Comenzar //Revision Vertical de 1,4,7
	if ((tab->getPos(1) == " " || tab->getPos(1) == marca) && (tab->getPos(4) == " " || tab->getPos(4) == marca) && (tab->getPos(7) == " " || tab->getPos(7) == marca)) {
		if (tab->getPos(1) == " " && tab->getPos(4) == " " && tab->getPos(7) == " ") {	//[ ]
			return 4;																	//[M]
		}																				//[ ]
		else {
			if ((tab->getPos(1) == marca || tab->getPos(7) == marca) && (tab->getPos(4) == " ")) {	//[X]     [ ]  
				return 4;																			//[M]  o  [M]
			}																						//[ ]     [X]
			else {
				if (tab->getPos(4) == marca && tab->getPos(1) == " ") {	// [M]
					return 1;											// [X]
				}														// [ ]
			}
		}
	}// sino en algun lado hay un X
	return -1;// Lo mejor es marcar en otro sitio
}

int Gato::revisar_Ultimo(string marca){
	//Revision Horizontal de 6,7,8
	if ((tab->getPos(6) != " " || tab->getPos(6) != marca) && (tab->getPos(7) != " " || tab->getPos(7) != marca) && (tab->getPos(8) != " " || tab->getPos(8) != marca)) {
		if (tab->getPos(6) == " " && tab->getPos(7) == " " && tab->getPos(8) == " ") {
			return 7;// [ ][ ][ ]
		}
		else {
			if ((tab->getPos(6) == marca || tab->getPos(8) == marca) && (tab->getPos(7) == " ")) {
				return 7; // [X][M][ ] //  [ ][M][X]
			}
			else {
				if (tab->getPos(7) == marca && tab->getPos(6) == " ") {
					return 6; // [M][X][ ]
				}
			}
		}
	}// sino en algun lado hay un X
	// Comenzar //Revision Vertical de 2,5,8
	if ((tab->getPos(2) != " " || tab->getPos(2) != marca) && (tab->getPos(5) != " " || tab->getPos(5) != marca) && (tab->getPos(8) != " " || tab->getPos(8) != marca)) {
		if (tab->getPos(2) == " " && tab->getPos(5) == " " && tab->getPos(8) == " ") {	//[ ]
			return 5;																	//[M]
		}																				//[ ]
		else {
			if ((tab->getPos(2) == marca || tab->getPos(8) == marca) && (tab->getPos(5) == " ")) {	//[X]     [ ]  
				return 5;																			//[M]  o  [M]
			}																						//[ ]     [X]
			else {
				if (tab->getPos(5) == marca && tab->getPos(2) == " ") {	// [M]
					return 2;											// [X]
				}														// [ ]
			}
		}
	}// sino en algun lado hay un X
	return -1;// Lo mejor es marcar en otro sitio
}

bool Gato::Ganador_Horizontal() {
	if (tab->getPos(0) == "X" && tab->getPos(1) == "X" && tab->getPos(2) == "X") { return true; }
	if (tab->getPos(3) == "X" && tab->getPos(4) == "X" && tab->getPos(5) == "X") { return true; }
	if (tab->getPos(6) == "X" && tab->getPos(7) == "X" && tab->getPos(8) == "X") { return true; }
	if (tab->getPos(0) == "O" && tab->getPos(1) == "O" && tab->getPos(2) == "O") { return true; }
	if (tab->getPos(3) == "O" && tab->getPos(4) == "O" && tab->getPos(5) == "O") { return true; }
	if (tab->getPos(6) == "O" && tab->getPos(7) == "O" && tab->getPos(8) == "O") { return true; }
	return false;
}

bool Gato::Ganador_Vertical() {
	if (tab->getPos(0) == "X" && tab->getPos(3) == "X" && tab->getPos(6) == "X") { return true; }
	if (tab->getPos(1) == "X" && tab->getPos(4) == "X" && tab->getPos(7) == "X") { return true; }
	if (tab->getPos(2) == "X" && tab->getPos(5) == "X" && tab->getPos(8) == "X") { return true; }
	if (tab->getPos(0) == "O" && tab->getPos(3) == "O" && tab->getPos(6) == "O") { return true; }
	if (tab->getPos(1) == "O" && tab->getPos(4) == "O" && tab->getPos(7) == "O") { return true; }
	if (tab->getPos(2) == "O" && tab->getPos(5) == "O" && tab->getPos(8) == "O") { return true; }
	return false;
}

bool Gato::Ganador_Diagonal() {
	if (tab->getPos(0) == "X" && tab->getPos(4) == "X" && tab->getPos(8) == "X") { return true; }
	if (tab->getPos(6) == "X" && tab->getPos(4) == "X" && tab->getPos(2) == "X") { return true; }
	if (tab->getPos(0) == "O" && tab->getPos(4) == "O" && tab->getPos(8) == "O") { return true; }
	if (tab->getPos(6) == "O" && tab->getPos(4) == "O" && tab->getPos(2) == "O") { return true; }
	return false;
}

int Gato::priorizar(string marca){
	//Diagonales
	if (tab->getPos(4) == marca || tab->getPos(4) == " ") {
		if (tab->getPos(0) == " " && tab->getPos(4) == marca && tab->getPos(8) == marca) {
			return 0;
		}
		if (tab->getPos(0) == marca && tab->getPos(4) == " " && tab->getPos(8) == marca) {
			return 4;
		}
		if (tab->getPos(0) == marca && tab->getPos(4) == marca && tab->getPos(8) == " ") {
			return 8;
		}
		if (tab->getPos(2) == " " && tab->getPos(4) == marca && tab->getPos(6) == marca) {
			return 2;
		}
		if (tab->getPos(2) == marca && tab->getPos(4) == " " && tab->getPos(6) == marca) {
			return 4;
		}
		if (tab->getPos(2) == marca && tab->getPos(4) == marca && tab->getPos(6) == " ") {
			return 6;
		}
	}
	// Horizontales
		if (tab->getPos(0) == " " && tab->getPos(1) == marca && tab->getPos(2) == marca){
			return 0;
		}
		if (tab->getPos(0) == marca && tab->getPos(1) == " " && tab->getPos(2) == marca) {
			return 1;
		}
		if (tab->getPos(0) == marca && tab->getPos(1) == marca && tab->getPos(2) == " ") {
			return 2;
		}
		if (tab->getPos(3) == " " && tab->getPos(4) == marca && tab->getPos(5) == marca) {
			return 3;
		}
		if (tab->getPos(3) == marca && tab->getPos(4) == " " && tab->getPos(5) == marca) {
			return 4;
		}
		if (tab->getPos(3) == marca && tab->getPos(4) == marca && tab->getPos(5) == " ") {
			return 5;
		}
		if (tab->getPos(6) == " " && tab->getPos(7) == marca && tab->getPos(8) == marca) {
			return 6;
		}
		if (tab->getPos(6) == marca && tab->getPos(7) == " " && tab->getPos(8) == marca) {
			return 7;
		}
		if (tab->getPos(6) == marca && tab->getPos(7) == marca && tab->getPos(8) == " ") {
			return 8;
		}
	// Verticales
		//Arriba
		if (tab->getPos(0) == marca && tab->getPos(3) == marca && tab->getPos(6) == " ") {
			return 6;
		}
		if (tab->getPos(0) == marca && tab->getPos(3) == " " && tab->getPos(6) == marca) {
			return 3;
		}
		if (tab->getPos(0) == " " && tab->getPos(3) == marca && tab->getPos(6) == marca) {
			return 0;
		}
		//Centro
		if (tab->getPos(1) == marca && tab->getPos(4) == marca && tab->getPos(7) == " ") {
			return 7;
		}
		if (tab->getPos(1) == marca && tab->getPos(4) == " " && tab->getPos(7) == marca) {
			return 4;
		}
		if (tab->getPos(1) == " " && tab->getPos(4) == marca && tab->getPos(7) == marca) {
			return 1;
		}
		//Abajo
		if (tab->getPos(2) == marca && tab->getPos(5) == marca && tab->getPos(8) == " ") {
			return 8;
		}
		if (tab->getPos(2) == marca && tab->getPos(5) == " " && tab->getPos(8) == marca) {
			return 5;
		}
		if (tab->getPos(2) == " " && tab->getPos(5) == marca && tab->getPos(8) == " ") {
			return 2;
		}

	return -1;// No puedo ganar ni bloquear
}