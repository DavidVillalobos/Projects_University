#include "in_out.h"

void imprimeInt(int entero) {
	cout << entero;
}

void imprimeChar(char caract) {
	cout << caract;
}

void imprimeString(string cadena) {
	cout << cadena;
}

int leerInt() {
	int n;
	while (true) {
		if (cin >> n) {
			cin.clear();
			cin.ignore(1024, '\n');
			return n;
		}
		else {
			cerr << "Este valor es incorrecto, por favor digita un NUMERO" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}

}

char leerChar() {
	char ch;
	cin >> ch;
	return ch;
}

string leerString() {
	string cad;
	getline(cin, cad);
	return cad;
}

void limpiaPantalla() {
	system("cls");
}

void limpiarBuffer() {
	cin.clear();
	cin.ignore(1024, '\n');
}

void setColor(int col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
	//Azul Oscuro (1) Verde Oscuro (2) Cian Oscuro (3) Rojo Oscuro (4) Morado Oscuro (5)
	//Amarillo Oscuro (6) Blanco (7) Gris (8) Azul brillante (9) Verde brillante (10) Cian brillante (11) 
	//Rojo brillante (12) Morado brillante (13) Amarillo brillante (14) Blanco Brillante (15)
}

void pausa() {
	system("pause");
}

void setCursor(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

int convertirInt(string s) {
	stringstream r(s);
	int v;
	r >> v;
	return v;
}

double convertirDouble(string s) {
	stringstream r(s);
	double v;
	r >> v;
	return v;
}

string StringChar(char c){
	return string(1, c);
}

int convertirLetra(char c) {
	switch (c) {
	case 'a': {return 0; }
	case 'A': {return 0; }
	case 'b': {return 1; }
	case 'B': {return 1; }
	case 'c': {return 2; }
	case 'C': {return 2; }
	case 'd': {return 3; }
	case 'D': {return 3; }
	case 'e': {return 4; }
	case 'E': {return 4; }
	case 'f': {return 5; }
	case 'F': {return 5; }
	case 'g': {return 6; }
	case 'G': {return 6; }
	case 'h': {return 7; }
	case 'H': {return 7; }
	case 'i': {return 8; }
	case 'I': {return 8; }
	case 'j': {return 9; }
	case 'J': {return 9; }
	case 'k': {return 10; }
	case 'K': {return 10; }
	case 'l': {return 11; }
	case 'L': {return 11; }
	case 'm': {return 12; }
	case 'M': {return 12; }
	default: return -1;
	}
}

void imprimeMenu() {
	string a1 = "\311", a2 = "\315", a3 = "\273", a4 = "\272", a5 = "\310", a6 = "\274", a7 = "\260"; int c = 14, d = 10;
	setColor(c); setCursor(17, 3); imprimeString(a1); for (int i = 0; i < 58; i++) { imprimeString(a2); }imprimeString(a3);
	setCursor(17, 4); imprimeString(a4); setColor(d); for (int i = 0; i < 58; i++) { imprimeString(a7); }setColor(c); imprimeString(a4);
	setCursor(17, 5); imprimeString(a4); setColor(d); for (int i = 0; i < 3; i++) { imprimeString(a7); }setColor(c); imprimeString(a1); for (int i = 0; i < 50; i++) { imprimeString(a2); }setColor(c);	 imprimeString(a3); setColor(d); for (int i = 0; i < 3; i++) { imprimeString(a7); }setColor(c); imprimeString(a4);
	for (int i = 0; i < 11; i++) {
		setCursor(17, i + 6); imprimeString(a4); setColor(d); for (int a = 0; a < 3; a++) { imprimeString(a7); }setColor(c); imprimeString(a4); setColor(d); for (int e = 0; e < 50; e++) { imprimeString(" "); }setColor(c); imprimeString(a4); setColor(d); for (int o = 0; o < 3; o++) { imprimeString(a7); }setColor(c); imprimeString(a4);
	}
	setCursor(17, 17); imprimeString(a4); setColor(d); for (int i = 0; i < 3; i++) { imprimeString(a7); }setColor(c); imprimeString(a5); for (int i = 0; i < 50; i++) { imprimeString(a2); }setColor(c);	imprimeString(a6); setColor(d); for (int i = 0; i < 3; i++) { imprimeString(a7); }setColor(c); imprimeString(a4);
	setCursor(17, 18); imprimeString(a4); setColor(d); for (int i = 0; i < 58; i++) { imprimeString(a7); }setColor(c); imprimeString(a4);
	setCursor(17, 19); imprimeString(a5); for (int i = 0; i < 58; i++) { imprimeString(a2); }imprimeString(a6);
	string a17 = "\337", a18 = "\333", a19 = "\334"; setColor(15);
	setCursor(27, 7); imprimeString(a18 + a17 + a17 + a17 + a18 + " " + a18 + a17 + a17 + a18 + " " + a18 + a17 + a17 + a18 + " " + a18 + a17 + a17 + a18 + " " + a18 + a17 + a17 + a18 + " " + a18 + a17 + a17 + a18 + " " + a18 + "    " + a18 + a17 + a17 + a17);
	setCursor(27, 8); imprimeString(a17 + a17 + a19 + a19 + "  " + a18 + "    " + a18 + a19 + a19 + a17 + " " + a18 + a19 + a19 + a18 + " " + a18 + a17 + a17 + a19 + " " + a18 + a17 + a17 + a19 + " " + a18 + "    " + a18 + a17 + a17 + a17);
	setCursor(27, 9); imprimeString(a18 + a19 + a19 + a19 + a18 + " " + a18 + a19 + a19 + a18 + " " + a18 + "  " + a18 + " " + a18 + "  " + a18 + " " + a18 + a19 + a19 + a18 + " " + a18 + a19 + a19 + a18 + " " + a18 + a19 + a19 + a18 + " " + a18 + a19 + a19 + a19);
	setCursor(37, 11); imprimeString("1)  Nuevo Juego");
	setCursor(37, 13); imprimeString("2)  Historial");
	setCursor(37, 15); imprimeString("3)  Salir");
	setCursor(37, 20); imprimeString("Ingrese un numero: ");
}