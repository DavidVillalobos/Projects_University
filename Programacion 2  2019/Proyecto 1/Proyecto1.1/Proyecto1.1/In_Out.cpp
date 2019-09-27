#include "In_Out.h"

void imprimeRellenoCuadrilatero(int x, int y, int ancho, int largo, int color, string relleno) {
	setCursor(x, y); setColor(color);
	for (int j = 0; j < ancho; j++) {
		for (int i = 0; i < largo; i++) {
			print(relleno);
		}
		y++; setCursor(x, y);
	}
}

void imprimeMarco(int x, int y, int ancho, int largo, int color) {
	setCursor(x, y); setColor(color);
	print("\311"); // esquina superior izquierda
	for (int i = 0; i < largo; i++) {
		print("\315"); // borde superior
	}
	print("\273"); // esquina superior derecha
	for (int j = 0; j < ancho; j++) {
		// columna izquierda y derecha
		y++; setCursor(x, y); print("\272"); setCursor(x + largo + 1, y); print("\272");
	}
	y++; setCursor(x, y); print("\310"); // esquina inferior derecha
	for (int i = 0; i < largo; i++) {
		print("\315"); // borde inferior
	}
	print("\274");// esquina inferior derecha
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

void print(int entero) { cout << entero; }

void print(float decimal) { cout << decimal; }

void print(string cadena) { cout << cadena; }

void print(char caracter) { cout << caracter; }

int readInt() {
	int n;
	while (true) {
		if (cin >> n) {
			return n;
		}
		else {
			cout << "Solamente se admiten datos numericos\n";
			cleanBuffer();
		}
	}
}

float readFloat(){
	float n;
	while (true) {
		if (cin >> n) {
			return n;
		}
		else {
			cout << "Por favor intrduzca datos numericos\n";
			cleanBuffer();
		}
	}
}

string readLine() {
	string cadena;
	while (true) {
		getline(cin, cadena);
		if (!cadena.empty()) {
			return cadena;
		}
	}
}

void cleanBuffer() {
	cin.clear();
	cin.ignore(1024, '\n');
}

int stringToInt(string s) {
	stringstream r(s);
	int v;
	r >> v;
	return v;
}

string charToString(char c) {
	return string(1, c);
}

string intToString(int entero) {
	stringstream s;
	s << entero;
	return s.str();
}

string floatToString(float decimal){
	stringstream s;
	s << decimal;
	return s.str();
}

void mostrarCursor(bool visibilidad) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = visibilidad; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int menuSeleccionLista(int x, int y, string *opciones,int cant, int color, int colorSelect) {
	string mayor = mayorPalabra(opciones, cant); // Retorna la palabra con mas letras
	int *posY = new int[cant];
	int *posX = new int[cant];
	int canLetras;
	int opcSelect = 1;
	int selecAnt = opcSelect;
	char tecla = '*';
	int pos_Simetrica = mayor.length() / 2;
	mostrarCursor(false); // Esconde el cursor
	for (int i = 0; i < cant; i++) { //Guarda las posiciones simetricas de cada opcion 
		canLetras = pos_Simetrica - opciones[i].length() / 2;//apartir de la palabra mas larga
		x += canLetras;
		y += 3;
		posX[i] = x;
		posY[i] = y;
		pintarSeleccion(x, y, opciones[i],color);
		x -= canLetras;
	}
	pintarSeleccion(posX[0], posY[0], opciones[0], colorSelect);
	while (tecla != 13) {
		if (_kbhit()) {
			tecla = _getch();
			if (tecla == 72 || tecla == 80) {
				switch (tecla) {
				case 72: {if (opcSelect != 1) { opcSelect--; }break; }//Tecla Arriba
				case 80: {if (opcSelect!= cant) { opcSelect++; }break; }//Tecla Abajo
				}
				if (opcSelect != 0 && opcSelect != cant+1) {
					pintarSeleccion(posX[selecAnt - 1], posY[selecAnt - 1], opciones[selecAnt - 1], color);
					pintarSeleccion(posX[opcSelect - 1], posY[opcSelect - 1], opciones[opcSelect - 1], colorSelect);
					selecAnt = opcSelect;
				}
			}
		}
	}
	delete[] posX;
	delete[] posY;
	return opcSelect;
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
							xAux += matriz[i][a].length();
							xAux += 10;
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
	setColor(15); int can = opcion.length(); can += 2;
	setCursor(x, y); print("\311"); for (int i = 0; i <can ; i++) { print("\315"); }print("\273");
	setCursor(x, y+1); print("\272 "); setColor(color); print(opcion); setColor(15); print(" \272");
	setCursor(x, y+2); print("\310"); for (int i = 0; i < can ; i++) { print("\315"); }print("\274");
}

string mayorPalabra(string *opciones, int cant) {
	string mayor = opciones[0];
	for (int a = 1; a < cant; a++) {
		if (opciones[a].length() > mayor.length()) {
			mayor = opciones[a];
		}
	}
	return mayor;
}

string fuente(string palabra){
	string nueva;
	for (int i = 0; i < palabra.length(); i++){
		nueva += superior(palabra[i]) + " ";
	}
	nueva += "\n";
	for (int i = 0; i < palabra.length(); i++) {
		nueva += medio(palabra[i]) + " ";
	}
	nueva += "\n";
	for (int i = 0; i < palabra.length(); i++) {
		nueva +=
			inferior(palabra[i]) + " ";
	}
	nueva += "\n";
	return nueva;
}

string superior(char letra) {
	switch (letra) {
	case 'A': return  "\333\337\337\333";
	case 'B': return  "\333\337\337\333";
	case 'C': return  "\333\337\337\333";
	case 'D': return  "\333\337\337\334";
	case 'E': return  "\333\337\337\337";
	case 'F': return  "\333\337\337\337";
	case 'G': return  "\333\337\337\333";
	case 'H': return  "\333  \333";
	case 'I': return  "\337\333\337";
	case 'J': return  "   \333";
	case 'K': return  "\333 \334\333";
	case 'L': return  "\333   ";
	case 'M': return  "\333\337\334\337\333";
	case 'N': return  "\333\334  \333";
	case 'O': return  "\333\337\337\337\333";
	case 'P': return  "\333\337\337\333";
	case 'Q': return  "\333\337\337\333";
	case 'R': return  "\333\337\337\333";
	case 'S': return  "\333\337\337\337\333";
	case 'T': return  "\337\337\333\337\337";
	case 'U': return  "\333  \333";
	case 'V': return  "\333   \333";
	case 'W': return  "\333   \333";
	case 'X': return "\337\334 \334\337";
	case 'Y': return "\333   \333";
	case 'Z': return "\333\337\337\337\333";
	case ' ': return "";
	default: return "INDEF";
	}
}

string medio(char letra) {
	switch(letra) {
	case 'A': return "\333\334\334\333";
	case 'B': return "\333\337\337\334";
	case 'C': return "\333   ";
	case 'D': return "\333  \333";
	case 'E': return "\333\337\337\337";
	case 'F': return "\333\337\337\337";
	case 'G': return "\333 \334\334";
	case 'H': return "\333\337\337\333";
	case 'I': return " \333 ";
	case 'J': return "\334  \333";
	case 'K': return "\333\337\334 ";
	case 'L': return "\333   ";
	case 'M': return "\333 \333 \333";
	case 'N': return "\333 \333 \333";
	case 'O': return "\333   \333";
	case 'P': return "\333\334\334\333";
	case 'Q': return "\333  \333";
	case 'R': return "\333\334\334\337";
	case 'S': return "\337\337\337\334\334";
	case 'T': return "  \333  ";
	case 'U': return "\333  \333";
	case 'V': return "\337   \337";
	case 'W': return "\333 \333 \333";
	case 'X': return "  \333  ";
	case 'Y': return "\333\334\334\334\333";
	case 'Z': return "\334\334\334\337\337";
	case ' ': return "";
	default : return "INDEF";
	}
}

string inferior(char letra){
	switch (letra) {
	case 'A': return "\333  \333";
	case 'B': return "\333\334\334\333";
	case 'C': return"\333\334\334\333";
	case 'D': return "\333\334\334\337";
	case 'E': return "\333\334\334\334";
	case 'F': return "\333   ";
	case 'G': return "\333\334\334\333";
	case 'H': return "\333  \333";
	case 'I': return "\334\333\334";
	case 'J': return "\333\334\334\333";
	case 'K': return"\333  \333";
	case 'L': return"\333\334\334\334";
	case 'M': return"\333   \333";
	case 'N': return"\333  \337\333";
	case 'O': return"\333\334\334\334\333";
	case 'P': return "\333   ";
	case 'Q': return "\337\337\333\334";
	case 'R': return"\333  \333";
	case 'S': return "\333\334\334\334\333";
	case 'T': return	"  \333  ";
	case 'U': return "\337\334\334\337";
	case 'V': return " \337\334\337 ";
	case 'W': return "\333\334\337\334\333";
	case 'X': return "\334\337 \337\334";
	case 'Y': return "  \333  ";
	case 'Z': return  "\333\334\334\334\333";
	case ' ': return  "";
	default: return "INDEF";
	}
}

char mayuscula(char letra) {
	switch (letra){
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
	case 'x': return 'X';
	case 'y': return 'Y';
	case 'z': return 'Z';
	default: return letra;
	}
}

string convertirMayuscula(string palabra) {
	for (int i = 0; i < palabra.length(); i++) {
		palabra[i] = mayuscula(palabra[i]);
	}
	return palabra;
}

bool menuBinario(int x, int y, int color, int colorSelect) {
	string vec[2] = { "NO","SI" };
	return (menuSeleccionLista(x, y, vec, 2, color, colorSelect) == 2);
}

void pause(){
	system("pause");
}

void cls(){
	system("cls");
}

void pedirFecha(int &dia, int &mes, int &anno){
	string meses[12] = { "Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre" };
	Fecha f;
	while (true) {
		print("A\244o(AAAA): "); anno = readInt();
		if (1950 < anno && anno <= f.getAnno()) {
			break;
		}
		print("Este a\244o aun no ha pasado o es muy antiguo, intentalo nuevamente\n");
	}
	while (true) {
		print("Mes(MM): "); mes = readInt();
		if (1 <= mes && mes <= 12){
			if (anno == f.getAnno()){
				if (mes <= f.getMes()) {
					break;
				}
				continue;
			}
			break;
		}
		print("Este mes aun no existe, intentalo nuevamente\n");
	}
	int diasfeb = 28;
	if (anno % 4 == 0) { //Verificacion de anno bisiesto
		diasfeb += 1;
	}
	int vecDias[12] = { 31,diasfeb,31,30,31,30,31,31,30,31,30,31 };
	while (true) {
		print("Dia: "); dia = readInt();
		if (1 <= dia && dia <= vecDias[mes - 1]){
			if (anno == f.getAnno() && mes == f.getMes() && dia > f.getDia()) {
				print("Esta fecha aun no ha pasado, i\n");
				continue;
			}
			break;
		}
		print("El mes de "); print(meses[mes - 1]); print(" no tiene un dia "); print(dia);
		print(" en el a\244o "); print(anno); print(", intentalo nuevamente\n");
	}
}
