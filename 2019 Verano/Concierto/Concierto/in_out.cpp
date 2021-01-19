#include "in_out.h"

void imprimeCuadrilatero(int x, int y, int ancho, int largo, int color, string relleno, int colorRelleno) {
	if (color != 0) { setColor(color); }setCursor(x, y); imprimeString("\311"); for (int i = 0; i < largo; i++) { imprimeString("\315"); }imprimeString("\273");
	setCursor(x + 1, y + 1); if (relleno != " ") { setColor(colorRelleno); imprimeRellenoCuadrilatero(x + 1, y + 1, ancho, largo, colorRelleno, relleno); }
	setColor(color); for (int a = 0; a < ancho; a++) { y++; setCursor(x, y); imprimeString("\272"); setCursor(x + largo + 1, y); imprimeString("\272"); }
	y++; setCursor(x, y); imprimeString("\310"); for (int i = 0; i < largo; i++) { imprimeString("\315"); }imprimeString("\274");
}
void imprimeRellenoCuadrilatero(int x, int y, int ancho, int largo, int color, string relleno) {
	if (relleno != " ") {
		setCursor(x, y);
		for (int j = 0; j < ancho; j++) {
			for (int i = 0; i < largo; i++) { setColor(color); imprimeString(relleno); }y++; setCursor(x, y);
		}
	}
}
void imprimeMarco(int x, int y, int ancho, int largo, int color) {
	if (color != 0) { setColor(color); } setCursor(x, y); imprimeString("\311"); for (int i = 0; i < largo; i++) { imprimeString("\315"); }imprimeString("\273");
	for (int j = 0; j < ancho; j++) {
		y++; setCursor(x, y); imprimeString("\272"); for (int i = 0; i < largo; i++) { imprimeString(" "); }if (color != 0) { setColor(color); } imprimeString("\272");
	}
	y++; setCursor(x, y); imprimeString("\310"); for (int i = 0; i < largo; i++) { imprimeString("\315"); }imprimeString("\274");
}
void imprimeMarcoDoble(int x, int y, int ancho, int largo, int color, string relleno, int colorRelleno, int espaciadoInterno) {
	/* Antes de utilizar este metodo tomar en cuenta las siguientes condiciones:
	Debido a que se quiere insertar un  Marco dentro de otro y este debe quedar alineado al centro solo se pueden introducir valores
	pares para el ancho, largo y espacio interno.
	Como el largo es mas amplio que el ancho, el espacio interno es tomado por la mitad para el largo y normal para el ancho, por ello
	si el espacio interno es de 2 al dividirlo entre 2 dá como resultado 1 y este numero no es par, entonces no quedara centrado, por ello
	el valor minimo que debera tomar el espaciado interno, será de 4 pues 3 no es par y si haces los calculos, para que quede el interlineado
	alineado con la figura, los valores minimo tomados por cada dimension deberan de ser:  6 Ancho y 8 Largo con espacio Interno de 4
	Tip *Trata de que el largo sea dos veces el ancho para que quede cuadrado
	*/
	imprimeMarco(x, y, ancho, largo, color);//Borde exterior
	if ((largo > 7 && ancho > 5 && espaciadoInterno > 3) && (ancho != 0 || largo != 0 || espaciadoInterno != 0 || ancho % 2 != 0 || largo % 2 != 0 || espaciadoInterno % 2 != 0)) {
		//si alguno no es par, quedara desalineada
		if (relleno != " ") {// si quiere que el relleno quede vacio, simplemente no invoco a los metodos de relleno
			imprimeRellenoCuadrilatero(x + 1, y + 1, espaciadoInterno / 2, largo, colorRelleno, relleno);//Relleno Arriba   |
			imprimeRellenoCuadrilatero(x + 1, y + ancho + 1 - espaciadoInterno / 2, espaciadoInterno / 2, largo, colorRelleno, relleno);//Relleno Abajo
			imprimeRellenoCuadrilatero(x + 1, y + espaciadoInterno / 2, ancho - espaciadoInterno + 2, espaciadoInterno, colorRelleno, relleno);//Relleno Izquierdo
			imprimeRellenoCuadrilatero(x + largo - espaciadoInterno + 1, y + espaciadoInterno / 2, ancho - espaciadoInterno + 2, espaciadoInterno, colorRelleno, relleno);// Relleno Derecho
		}
		imprimeMarco(x + espaciadoInterno + 1, 1 + y + espaciadoInterno / 2, ancho - espaciadoInterno - 2, largo - 2 * espaciadoInterno - 2, color);
	}
}
void cargando(int x, int y, int ancho, int largo, int segundos, int color, string relleno, int colorRelleno) {
	/* Antes de utilizar este metodo tomar en cuenta que solo funciona si la division entre el largo
	y los segundos es una division entera, Porque, como el cargando se divide en partes por segundo para cargar lo si no es exacta siempre faltara una parte del final*/
	if (largo%segundos == 0) {
		imprimeMarco(x, y, ancho, largo, color);
		int aux = largo / segundos;
		int auxLargo = aux;
		setColor(color);
		for (int i = 0; i < segundos; i++) {
			imprimeRellenoCuadrilatero(x + 1, y + 1, ancho, auxLargo, colorRelleno, "\333");
			auxLargo = auxLargo + aux;
			Sleep(1000);
		}
	}
}
void setColor(int col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
	//Azul Oscuro (1) Verde Oscuro (2) Cian Oscuro (3) Rojo Oscuro (4) Morado Oscuro (5)
	//Amarillo Oscuro (6) Blanco (7) Gris (8) Azul brillante (9) Verde brillante (10) Cian brillante (11)
	//Rojo brillante (12) Morado brillante (13) Amarillo brillante (14) Blanco Brillante (15)
	//BACKGROUND_GREEN    BACKGROUND_GREEN    BACKGROUND_RED
}
void setCursor(int x, int y) {
	HANDLE hcon; //Variable de ventanas
	hcon = GetStdHandle(STD_OUTPUT_HANDLE); //obtener Ventana actual
	COORD dwPos; //Variable de coordenadas
	dwPos.X = x; //guarde la x
	dwPos.Y = y; // guarde la y
	SetConsoleCursorPosition(hcon, dwPos);
	// Este método recibe una ventana y pone el cursor en la coordenada
}
void imprimeInt(int entero) { cout << entero; }
void imprimeString(string cadena) {
	cout << cadena;
}
void imprimeChar(char caract) {
	cout << caract;
}
int leerInt() {
	int n;
	while (true) {
		if (cin >> n) {
			return n;
		}
		else {
			cout << "Este valor es incorrecto, por favor digita un NUMERO\n";
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}

}
string leerString() {
	string cad;
	getline(cin, cad);
	return cad;
}
char leerChar() {
	char ch;
	cin >> ch;
	return ch;
}
void limpiarBuffer() {
	cin.clear();
	cin.ignore(1024, '\n');
}
int convertirInt(string s) {
	stringstream r(s);
	int v;
	r >> v;
	return v;
}
string StringChar(char c) {
	return string(1, c);
}
string convertirString(int cadena) {
	stringstream s;
	s << cadena;
	return s.str();
}
void mostrarCursor(bool visibilidad) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = visibilidad; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
int menuSeleccionLista(int x, int y, string *opciones, int cant, int color, int colorSelec, bool direccion) {
	mostrarCursor(false); int seleccion = 1; int yAux = y, xAux = x;
	for (int i = 0; i < cant; i++) {
		if (seleccion != i + 1) { pintarSeleccion(xAux, yAux, opciones[i], color); }
		else { pintarSeleccion(xAux, yAux, opciones[i], colorSelec); }
		(direccion) ? yAux += 3 : xAux += opciones[i].length() + 10;
	}
	char tecla = '*';
	while (tecla != 13) {
		if (_kbhit()) {
			yAux = y; xAux = x; tecla = _getch();
			if (tecla == 72 || tecla == 80 || tecla == 75 || tecla == 77) {
				if (direccion) {
					switch (tecla) {
					case 72: {if (seleccion != 1) { seleccion--; }break; }//Arriba
					case 80: {if (seleccion != cant) { seleccion++; }break; }// Abajo
					}
				}
				else {
					switch (tecla) {
					case 75: {if (seleccion != 1) { seleccion--; }break; }// Izquierda
					case 77: {if (seleccion != cant) { seleccion++; }break; }//Derecha
					}
				}
				for (int i = 0; i < cant; i++) {
					if (seleccion != i + 1) { pintarSeleccion(xAux, yAux, opciones[i], color); }
					else { pintarSeleccion(xAux, yAux, opciones[i], colorSelec); }
					(direccion) ? yAux += 3 : xAux += opciones[i].length() + 10;
				}
			}
		}
	}
	return seleccion;
}
int menuSeleccionCuadrilatero(int x, int y, int columnas, int filas, string *opciones, int cant, int color, int colorSelec) {
	mostrarCursor(false);
	string **matriz; matriz = new string*[filas]; int iAux = 0;
	for (int i = 0; i < filas; i++) { matriz[i] = new string[columnas]; }
	for (int i = 0; i < filas; i++) {
		for (int a = 0; a < columnas; a++) {
			(cant > iAux) ? matriz[i][a] = opciones[iAux] : matriz[i][a] = "*";
			iAux++;
		}
	}
	int yAux = y, xAux = x;
	int selecX = 1; int selecY = 1;
	for (int i = 0; i < filas; i++) {
		for (int a = 0; a < columnas; a++) {
			if (matriz[i][a] != "*") {
				if ((selecY == i + 1) && (selecX == a + 1)) {
					pintarSeleccion(xAux, yAux, matriz[i][a], colorSelec);
				}
				else {
					pintarSeleccion(xAux, yAux, matriz[i][a], color);
				}
				xAux += matriz[i][a].length() + 10;
			}
		}
		yAux += 3;
		xAux = x;
	}
	char tecla = '*';
	while (tecla != 13) {
		if (_kbhit()) {
			yAux = y; xAux = x; tecla = _getch();
			if (tecla == 72 || tecla == 80 || tecla == 77 || tecla == 75) {
				switch (tecla) {
				case 72: {if (selecY != 1) { selecY--; }break; }// Arriba
				case 80: {if (selecY != filas) { if (matriz[selecY][selecX - 1] != "*") { selecY++; } }break; }//Abajo
				case 77: {if (selecX != columnas) { if (matriz[selecY - 1][selecX] != "*") { selecX++; } } break; }//Derecha
				case 75: {if (selecX != 1) { selecX--; }break; }//Izquierda
				}
				yAux = y, xAux = x;
				for (int i = 0; i < filas; i++) {
					for (int a = 0; a < columnas; a++) {
						if (matriz[i][a] != "*") {
							if ((selecY == i + 1) && (selecX == a + 1)) {
								pintarSeleccion(xAux, yAux, matriz[i][a], colorSelec);
							}
							else {
								pintarSeleccion(xAux, yAux, matriz[i][a], color);
							}
							xAux += matriz[i][a].length() + 10;
						}
					}
					yAux += 3;
					xAux = x;
				}
			}
		}
	}
	for (int i = 0; i < cant; i++) {
		if (matriz[selecY - 1][selecX - 1] == opciones[i]) {
			return i + 1;
		}
	}
	return -1;
}
void pintarSeleccion(int x, int y, string opcion, int color) {
	setColor(color); int can = opcion.length() + 2;
	setCursor(x, y); for (int i = 0; i < can + 2; i++) { imprimeString("\334"); }
	y++; setCursor(x, y); imprimeString("\333 "); setColor(15); imprimeString(opcion); setColor(color); imprimeString(" \333");
	y++; setCursor(x, y); for (int i = 0; i < can + 2; i++) { imprimeString("\337"); }
}
int convertirLetra(char letra) {
	switch (letra) {
	case 'a': return 0;
	case 'A': return 0;
	case 'b': return 1;
	case 'B': return 1;
	case 'c': return 2;
	case 'C': return 2;
	case 'd': return 3;
	case 'D': return 3;
	case 'e': return 4;
	case 'E': return 4;
	case 'f': return 5;
	case 'F': return 5;
	case 'g': return 6;
	case 'G': return 6;
	case 'h': return 7;
	case 'H': return 7;
	case 'i': return 8;
	case 'I': return 8;
	case 'j': return 9;
	case 'J': return 9;
	case 'k': return 10;
	case 'K': return 10;
	case 'l': return 11;
	case 'L': return 11;
	case 'm': return 12;
	case 'M': return 12;
	case 'n': return 13;
	case 'N': return 13;
	case 'o': return 14;
	case 'O': return 14;
	case 'p': return 15;
	case 'P': return 15;
	case 'q': return 16;
	case 'Q': return 16;
	case 'r': return 17;
	case 'R': return 17;
	case 's': return 18;
	case 'S': return 18;
	case 't': return 19;
	case 'T': return 19;
	case 'u': return 20;
	case 'U': return 20;
	case 'v': return 21;
	case 'V': return 21;
	case 'w': return 22;
	case 'W': return 22;
	case 'x': return 23;
	case 'X': return 23;
	case 'y': return 24;
	case 'Y': return 24;
	case 'z': return 25;
	case 'Z': return 25;
	default: return -1;
	}
}
char LetraMayuscula(char letra) {
	switch (letra) {
	case 'a': return 'A';
	case 'b': return 'B';
	case 'c': return 'C';
	case 'd': return 'D';
	case 'e': return 'E';
	case 'f': return 'F';
	case 'g': return 'G';
	case 'h': return 'H';
	case 'i': return 'I';
	case 'j': return 'J';
	case 'k': return 'K';
	case 'l': return 'L';
	case 'm': return 'M';
	case 'n': return 'N';
	case 'o': return 'O';
	case 'p': return 'P';
	case 'q': return 'Q';
	case 'r': return 'R';
	case 's': return 'S';
	case 't': return 'T';
	case 'u': return 'U';
	case 'v': return 'V';
	case 'w': return 'W';
	case 'x': return 'X';
	case 'y': return 'Y';
	case 'z': return 'Z';
	default: return letra;
	}
}
void menuSeleccionAsiento(int x, int y, int &filas, int &columnas) {
	mostrarCursor(false);int seleccionX = 1; int seleccionY = 1;setColor(15);
	setCursor(x+2, y); imprimeString("\255"); char tecla = ' ';
	while (tecla != 13) {
		if (_kbhit()) {
			tecla = _getch();
			setCursor((x + seleccionX * 3) - 1, (y + seleccionY )-1); imprimeString(" ");// eliminar posicion
			if (tecla == 72 || tecla == 80 || tecla == 77 || tecla == 75) {
				switch (tecla) {
					case 72: { if (seleccionY > 1) {  seleccionY--; }  break; }// Arriba
					case 80: { if (seleccionY < filas) { seleccionY++; } break; }//Abajo
					case 77: { if (seleccionX < columnas) { seleccionX++; } break; }//Derecha
					case 75: { if (seleccionX > 1) { seleccionX--; } break; }//Izquierda
				}
			}
			setCursor((x + seleccionX * 3) - 1, (y + seleccionY)-1); imprimeString("\255");// imprimir posicion
		}
	}
	filas=seleccionY;
	columnas=seleccionX ;
}
string conLetraNum(int num) {
	switch (num) {
	case 0: return "A";
	case 1: return "B";
	case 2: return "C";
	case 3: return "D";
	case 4: return "E";
	case 5: return "F";
	case 6: return "G";
	case 7: return "H";
	case 8: return "I";
	case 9: return "J";
	case 10: return "K";
	case 11: return "L";
	case 12: return "M";
	case 13: return "N";
	case 14: return "O";
	case 15: return "P";
	case 16: return "Q";
	case 17: return "R";
	case 18: return "S";
	case 19: return "T";
	case 20: return "U";
	case 21: return "V";
	case 22: return "W";
	case 23: return "X";
	case 24: return "Y";
	case 25: return "Z";
	case 26: return "AA";
	case 27: return "AB";
	case 28: return "AC";
	case 29: return "AD";
	case 30: return "AE";
	case 31: return "AF";
	case 32: return "AG";
	case 33: return "AH";
	case 34: return "AI";
	case 35: return "AJ";
	case 36: return "AK";
	case 37: return "AL";
	case 38: return "AM";
	case 39: return "AN";
	case 40: return "AO";
	case 41: return "AP";
	case 42: return "AQ";
	case 43: return "AR";
	case 44: return "AS";
	case 45: return "AT";
	case 46: return "AU";
	case 47: return "AV";
	case 48: return "AW";
	case 49: return "AX";
	default: return " ";
	}
}
string palabraMayuscula(string palabra) {
	int can = palabra.length();
	for (int i = 0;i < can;i++) {
		palabra[i]=LetraMayuscula(palabra[i]);
	}
	return palabra;
}
void Regalo(int X, int Y, int colorCaja, int colorLazo) {
	setCursor(X, Y); setColor(colorLazo); cout << " \333\337\337\337\333  \333\337\337\337\333"; Y++;
	setCursor(X, Y); cout << " \333\334  \333\334\334\333  \334\333"; Y++;
	setCursor(X, Y); cout << "  \333\334\334\334\333\333\334\334\334\333"; setColor(colorCaja); Y++;
	setCursor(X, Y); cout << "\333\333\333\333\333\333"; setColor(colorLazo); cout << "\333\333"; setColor(colorCaja); cout << "\333\333\333\333\333\333"; Y++;
	setCursor(X, Y); cout << "\333\333\333\333\333\333"; setColor(colorLazo); cout << "\333\333"; setColor(colorCaja); cout << "\333\333\333\333\333\333"; setColor(colorLazo); Y++;
	setCursor(X, Y); cout << "\333\333\333\333\333\333"; cout << "\333\333"; cout << "\333\333\333\333\333\333"; setColor(colorCaja); Y++;
	setCursor(X, Y); cout << "\333\333\333\333\333\333"; setColor(colorLazo); cout << "\333\333"; setColor(colorCaja); cout << "\333\333\333\333\333\333"; Y++;
	setCursor(X, Y); cout << "\333\333\333\333\333\333"; setColor(colorLazo); cout << "\333\333"; setColor(colorCaja); cout << "\333\333\333\333\333\333"; Y++; setColor(8);
}