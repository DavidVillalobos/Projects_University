#include "ViewConsole.h"

void printString(string w) { 
	cout << w;
}

int getInt() {
	int n;
	while (true) {
		if (cin >> n) {
			cin.clear();
			cin.ignore(1024, '\n');
			return n;
		}else {
			printString("Este valor es incorrecto, por favor digita un NUMERO\n");
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
}

string getString() {
	string w;
	while (true) {
		getline(cin, w);
		if (!w.empty()) return w;
	}
}

void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	//Azul (1) Verde (2) Cian (3) Rojo (4) Morado (5)
	//Amarillo  (6) Blanco (7) Gris (8) Azul claro(9) Verde claro(10) Cian claro(11)
	//Rojo claro(12) Morado claro(13) Amarillo claro(14) Blanco Brillante (15)
}

void setCursorPosition(int x, int y) {
	HANDLE out;
	out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(out, dwPos);
}

void setConsoleSize(int cols, int lines){
	string command = "mode con: cols=" + to_string(cols) + " lines=" + to_string(lines);
	system(command.c_str());
}

int wherex() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.dwCursorPosition.X;
}

int wherey() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.dwCursorPosition.Y;
}

int stringToInt(string s) {
	stringstream r(s);
	int v;
	r >> v;
	return v;
}