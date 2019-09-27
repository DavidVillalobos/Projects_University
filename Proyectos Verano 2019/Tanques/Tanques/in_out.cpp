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
		imprimeMarco(x + espaciadoInterno+1, 1+y + espaciadoInterno / 2, ancho - espaciadoInterno-2, largo - 2 * espaciadoInterno-2, color);
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
void imprimeInt(int entero) {cout<<entero;}
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
			cerr << "Este valor es incorrecto, por favor digita un NUMERO" << endl;
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
void pantalla() {
	string a = "\333"; string b = "\334"; string c = "\337"; imprimeMarcoDoble(36, 5, 24, 82, 14, "\260", 4, 6); setColor(15); int x = 45, y = 10;
	y++; setCursor(x, y); imprimeString("                                               " + c + c + c + c + a + c + c + c + c); setColor(14);
	y++; setCursor(x, y); imprimeString("   " + c + c + a + c + c + " " + a + c + c + a + " " + a + b + "  " + a + " " + a + c + c + a + " " + a + "  " + a + " " + a + c + c + c + " " + a + c + c + c + a + "        "); setColor(15); imprimeString(b + c + a + c + c + a + "      " + b);
	y++; setColor(14); setCursor(x, y); imprimeString("     " + a + "   " + a + b + b + a + " " + a + " " + a + " " + a + " " + a + "  " + a + " " + a + "  " + a + " " + a + c + c + c + " " + c + c + c + b + b + "       "); setColor(15); imprimeString(a + b + b + a + b + b + a + a + a + a + a + a + c);
	y++; setColor(14); setCursor(x, y); imprimeString("     " + a + "   " + a + "  " + a + " " + a + "  " + c + a + " " + c + c + a + b + " " + c + b + b + c + " " + a + b + b + b + " " + a + b + b + b + a + "        "); setColor(15); imprimeString(c + c + a + c + c + c + a + c + c);
	y++; setCursor(x, y); imprimeString("                                                " + c + c + c + c + c + c + c);
	y = y + 2; setCursor(x, y); imprimeString(" " + b + b + b + "   " + a + "    " + b + "           " + b + b + b + "        " + b + "                      " + a + "    " + b);
	y++; setCursor(x, y); imprimeString(a + c + a + c + a + " " + a + c + a + "  " + a + c + a + " " + b + a + a + a + b + "   " + a + c + a + c + a + " " + a + c + a + "  " + a + c + a + " " + b + a + a + a + b + "    " + a + c + a + c + a + a + c + a + "  " + a + c + a + " " + b + a + a + a + b);
	y++; setCursor(x, y); imprimeString(a + c + a + c + a + " " + a + c + a + a + " " + a + c + a + " " + a + b + a + b + a + "   " + a + c + a + c + a + " " + a + c + a + a + " " + a + c + a + " " + a + b + a + b + a + "    " + a + c + a + c + a + a + c + a + a + " " + a + c + a + " " + a + b + a + b + a);
	y++; setCursor(x, y); imprimeString(a + c + a + c + a + " " + a + c + a + a + " " + a + c + a + " " + a + b + a + b + a + "   " + a + c + a + c + a + " " + a + c + a + a + " " + a + c + a + " " + a + b + a + b + a + "    " + a + c + a + c + a + a + c + a + a + " " + a + c + a + " " + a + b + a + b + a);
	y++; setCursor(x, y); imprimeString(a + c + a + c + a + " " + a + c + a + a + " " + a + c + a + " " + a + b + a + b + a + "   " + a + c + a + c + a + " " + a + c + a + a + " " + a + c + a + " " + a + b + a + b + a + "    " + a + c + a + c + a + a + c + a + a + " " + a + c + a + " " + a + b + a + b + a);
	y++; setCursor(x, y); imprimeString(a + c + a + c + a + " " + a + c + a + a + a + a + c + a + " " + a + b + a + b + a + "   " + a + c + a + c + a + " " + a + c + a + a + a + a + c + a + " " + a + b + a + b + a + "    " + a + c + a + c + a + a + c + a + a + " " + a + c + a + " " + a + b + a + b + a);
	y++; setCursor(x, y); for (int i = 0; i < 66; i++) { imprimeString(a); }
	y = y + 2; x = x + 14; setCursor(x, y); system("pause"); system("cls");
}
int menuSeleccionLista(int x, int y, string *opciones, int cant, int color, int colorSelec, bool direccion) {
	mostrarCursor(false);int seleccion = 1; int yAux = y, xAux = x;
	for (int i = 0; i < cant; i++) {
		if (seleccion != i + 1) { pintarSeleccion(xAux, yAux, opciones[i], color); }
		else { pintarSeleccion(xAux, yAux, opciones[i], colorSelec); }
		(direccion) ? yAux += 3 : xAux += opciones[i].length() + 10;
	}
	char tecla = '*';
	while (tecla != 13) {
		if (_kbhit()) {
			yAux = y; xAux = x; tecla = _getch();
			if (tecla == 72 || tecla == 80||tecla==75||tecla==77) {
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
					else { pintarSeleccion(xAux, yAux, opciones[i],colorSelec); }
					(direccion) ? yAux += 3 : xAux += opciones[i].length() + 10;
				}
			}
		}
	}
	return seleccion;
}
int menuSeleccionCuadrilatero(int x, int y,int columnas,int filas,string *opciones, int cant, int color, int colorSelec) {
	mostrarCursor(false);
	string **matriz;matriz = new string*[filas];int iAux = 0;
	for (int i = 0; i < filas;i++) {matriz[i]= new string[columnas];}
	for (int i = 0; i < filas; i++) {
		for (int a = 0; a < columnas;a++) {
			(cant>iAux)?matriz[i][a] = opciones[iAux]:matriz[i][a] = "*";
			iAux++;
		}
	}
	int yAux = y, xAux = x;
	int selecX = 1;int selecY = 1;
	for (int i = 0; i < filas; i++) {
		for (int a = 0; a < columnas;a++) {
			if (matriz[i][a] !="*") {
				if ((selecY == i + 1)&&(selecX == a + 1)) {
					pintarSeleccion(xAux, yAux, matriz[i][a], colorSelec);
				}
				else {
					pintarSeleccion(xAux, yAux, matriz[i][a], color);
				}
				xAux += matriz[i][a].length() + 10;
			}
		}
		yAux+=3;
		xAux = x;
	}
	char tecla = '*';
	while (tecla != 13) {
		if (_kbhit()) {
			yAux = y; xAux = x; tecla = _getch();
			if (tecla == 72 || tecla == 80||tecla==77||tecla==75) {
				switch (tecla) {
				case 72: {if (selecY != 1) {selecY--;}break; }// Arriba
				case 80: {if (selecY != filas) {if (matriz[selecY][selecX-1] != "*") {selecY++;}}break;}//Abajo
				case 77: {if (selecX != columnas) {if (matriz[selecY-1][selecX] != "*") {selecX++; }} break;}//Derecha
				case 75: {if (selecX != 1) {selecX--;}break;}//Izquierda
				}
				yAux = y, xAux = x;
				for (int i = 0; i < filas; i++) {
					for (int a = 0; a < columnas; a++) {
						if (matriz[i][a] != "*") {
							if ((selecY == i + 1)&&(selecX == a + 1)) {
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
	for (int i = 0; i < cant;i++) {
		if (matriz[selecY-1][selecX-1]==opciones[i]) {
			return i+1;
		}
	}
}
void pintarSeleccion(int x, int y ,string opcion,int color) {
	setColor(color); int can = opcion.length() + 2;
	setCursor(x, y); for (int i = 0; i < can+2; i++) { imprimeString("\334"); }
	y++; setCursor(x, y); imprimeString("\333 "); setColor(15); imprimeString(opcion); setColor(color); imprimeString(" \333");
	y++; setCursor(x, y); for (int i = 0; i < can+2; i++) { imprimeString("\337"); }
}