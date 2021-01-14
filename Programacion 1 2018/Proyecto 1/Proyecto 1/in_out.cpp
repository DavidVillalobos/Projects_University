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

void opcionIncorrecta() {
	cerr << " Esta opci\242n no se encuentra en el men\243, por favor int\202ntelo de nuevo" << endl;
	Sleep(2000);
	limpiaPantalla();
}

void color(int col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

void pausa() {
	system("pause");
}