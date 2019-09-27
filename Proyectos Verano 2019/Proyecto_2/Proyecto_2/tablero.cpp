#include "tablero.h"

tablero::tablero() {
	matriz = new ficha**[13];
	for (int i = 0; i < 13; i++) {
		matriz[i] = new ficha*[13];
	}
	for (int i = 0; i < 13; i++) {
		for (int a = 0; a < 13; a++) {
			matriz[i][a] = NULL;
		}
	}	
}

ficha* tablero::getFicha(int fil,int col) {
	return matriz[fil][col];
}

void tablero::setFicha(int fil, int col, ficha *f) {
	matriz[fil][col] = f;
}

void tablero::toString(ficha **bolsita) {
	string a1 = "\311"; string a2 = "\315"; string a3 = "\273";
	string a4 = "\272"; string a5 = "\310"; string a6 = "\274";
	string a7 = "\337"; string a8 = "\333"; string a9 = "\334"; setColor(15);
	imprimeString("\n\t\t      \333\337\337\337\333 \333\337\337\333 \337\337\337\333 \333\337\337\333 \333\337\337\333 \333\337\337\333 \333    \333\337\337\337\n");
	imprimeString("\t\t      \337\337\334\334  \333    \333\334\334\337 \333\334\334\333 \333\337\337\334 \333\337\337\334 \333    \333\337\337\337\n");
	imprimeString("\t\t      \333\334\334\334\333 \333\334\334\333 \333  \333 \333  \333 \333\334\334\333 \333\334\334\333 \333\334\334\333 \333\334\334\334\n");
	string vectorLetras[13] = { "  A   ","  B   ","  C   ","  D   ","  E   ","  F   ","  G   ","  H   ","  I   ","  J   ","  K   ","  L   ","  M   " };
	imprimeString("   "); for (int i = 0; i < 13; i++) { imprimeString(vectorLetras[i]); }
	imprimeString("\n");
	for (int i = 0; i < 13; i++) {
		setColor(15); imprimeString("   ");
		for (int a = 0; a < 13; a++) {
			setColor(casillaPremios(i, a)); imprimeString(a1 + a2 + a2 + a2 + a3 + " ");
		}
		imprimeString("\n "); setColor(15);
		imprimeInt(i + 1); if (i < 9) { imprimeString(" "); }
		for (int a = 0; a < 13; a++) {
			setColor(casillaPremios(i, a));  imprimeString(a4); setColor(15);
			(matriz[i][a] != NULL) ? imprimeString(matriz[i][a]->toString()) : imprimeString("   ");
			setColor(casillaPremios(i, a));  imprimeString(a4 + " ");
		}
		imprimeString("\n   ");
		for (int a = 0; a < 13; a++) { setColor(casillaPremios(i, a)); imprimeString(a5 + a2 + a2 + a2 + a6 + " "); }
		if (i != 12) { imprimeChar('\n'); }
	}
	string b1 = "\311", b2 = "\315", b3 = "\273", b4 = "\272", b5 = "\310", b6 = "\274"; a8 = "\333";
	setColor(15); setCursor(87, 2); setColor(14); imprimeString("DISTRIBUCION DE LETRAS"); setColor(15);
	setCursor(81, 3); imprimeString(b1); for (int i = 0; i < 30; i++) { imprimeString(b2); }imprimeString(b3);
	setCursor(81, 4);
	imprimeString(b4);
	int aux = 2;
	for (int i = 0; i < 27; i++) {
		imprimeString(" " + bolsita[i]->getLetra() + "-"); imprimeInt(bolsita[i]->getDisponibles()); imprimeString(" ");
		if (i % 5 == 0 && i != 0) {
			imprimeString(b4); setCursor(81, 4 + aux); aux++; imprimeString(b4);
		}
	}
	setCursor(81, 10); imprimeString(b5); for (int i = 0; i < 30; i++) { imprimeString(b2); }imprimeString(b6);

	setCursor(89, 11); setColor(12); imprimeString("PUNTAJE DE LETRAS"); setColor(15);
	setCursor(81, 12); imprimeString(b1); for (int i = 0; i < 30; i++) { imprimeString(b2); }imprimeString(b3);
	setCursor(81, 13);
	imprimeString(b4);
	aux = 2;
	for (int i = 0;i < 27; i++) {
		imprimeString(" " + bolsita[i]->getLetra() + "-"); imprimeInt(bolsita[i]->getValor()); imprimeString(" ");
		if (i % 5 == 0 && i != 0) {
			imprimeString(b4); setCursor(81, 12 + aux); aux++; imprimeString(b4);
		}
	}
	setCursor(81, 19); imprimeString(b5); for (int i = 0; i < 30; i++) { imprimeString(b2); }imprimeString(b6);
	setCursor(87, 20); setColor(10); imprimeString("SIMBOLOGIA DE PREMIOS"); setColor(15);

	setCursor(81, 21); imprimeString(b1); for (int i = 0; i < 30; i++) { imprimeString(b2); }imprimeString(b3);
	setCursor(81, 22); imprimeString(b4); setColor(14); imprimeString("  " + a8); setColor(15); imprimeString("-> Triple Valor de Letra   " + b4);
	setCursor(81, 23); imprimeString(b4); setColor(13);  imprimeString("  " + a8); setColor(15); imprimeString("-> Doble  Valor de Letra   " + b4);
	setCursor(81, 24); imprimeString(b4); setColor(9); imprimeString("  " + a8); setColor(15); imprimeString("-> Triple Valor de Palabra " + b4);
	setCursor(81, 25); imprimeString(b4); setColor(10); imprimeString("  " + a8); setColor(15); imprimeString("-> Doble Valor de Palabra  " + b4);
	setCursor(81, 26); imprimeString(b5); for (int i = 0; i < 30; i++) { imprimeString(b2); }imprimeString(b6);
}

int tablero::casillaPremios(int i, int a) {// filas i columnas a
	if (((i == 6) && (a == 0 || a == 12)) || (i == 12 || i == 0) && (a == 0 || a == 12 || a == 6)) { return 9; }
	if ((((i == 1 || i == 11) && a == 1) || ((i == 11 || i == 1) && a == 11))) { return 10; }
	if ((((i == 2 || i == 10) && a == 2) || (((i == 2 || i == 10) && a == 10)))) { return 10; }
	if ((((i == 3 || i == 9) && a == 3) || (((i == 3 || i == 9) && a == 9)))) { return 10; }
	if (((i == 4 || i == 8) && a == 4) || ((i == 4 || i == 8) && a == 8) || (((i == 1) || (i == 11)) && a == 8)) { return 14; }
	if (((i == 4 || i == 8) && a == 1) || ((i == 1 || i == 11) && a == 4) || (a == 11 && (i == 4 || i == 8))) { return 14; }
	if (((i == 7 || i == 5) && a == 2) || (i == 6 && a == 3) || ((i == 3 || i == 9) && a == 6)) { return 13; }
	if (((i == 2 || i == 5 || i == 7 || i == 10) && (a == 5 || a == 7)) || (i == 6 && a == 9) || ((i == 5 || i == 7) && a == 10)) { return 13; }
	if (((a == 0 || a == 12) && (i == 3 || i == 9)) || ((a == 3 || a == 9) && (i == 0 || i == 12))) { return 13; }
	if (i == 6 && a == 6) { return 8; }
	return 15;
}

bool tablero::vacio(int fila, int columna) {
	return(matriz[fila][columna] == NULL);
}

tablero::~tablero() {
	for (int i = 0; i < 13; i++) {
		delete[] matriz[i];
	}
	delete[] matriz;
}