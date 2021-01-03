#include "in_out.h"

void imprimeInt(int entero) {
	cout << entero;
}

void imprimeChar(char caract) {
	cout << caract;
}

void imprimeString(std::string cadena) {
	cout << cadena;
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

char leerChar() {
	char ch;
	cin >> ch;
	return ch;
}

std::string leerString() {
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

string StringChar(char c)
{
	return string(1, c);
}

void pantallaPrincipal(){
	int x=35, y=8;
	string d = "\333"; string b = "\337"; string c = "\334";
	string a = " "; string e = "\333";
	setColor(15);
	setCursor(x,y); imprimeString(d + b + b + d + " " + d + "  " + d + "  " + d + b + b + b + d + "  " + d + b + b + d + "  " + d + b + b + d + "  " + d + b + b + c + "  " + d + b + b + b + d + "  " + d + b + b + d);
	y++; setCursor(x, y); imprimeString(d + b + b + c + " " + d + "  " + d + "  " + b + b + b + c + c + "  " + d + "     " + d + c + c + d + "  " + d + "  " + d + "  " + d + "   " + d + "  " + d + c + c + b);
	y++; setCursor(x, y); imprimeString(d + c + c + d + " " + b + c + c + b + "  " + d + c + c + c + d + "  " + d + c + c + d + "  " + d + "  " + d + "  " + d + c + c + b + "  " + d + c + c + c + d + "  " + d + "  " + d);
	setColor(12);
	y++; y++; setCursor(x, y); imprimeString("           " + a + a + a + a + a + a + a + a + a + a);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); imprimeString("       " + a + a + a + a + a); setColor(15); imprimeString(e + e); setColor(12); imprimeString(d + d + d + d); setColor(15); imprimeString(e + e); setColor(12); imprimeString(a + a + a + a + a); 
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); imprimeString("     " + a + a + a); setColor(15); imprimeString(e + e + e + e + e + e); setColor(12); imprimeString(d + d + d + d); setColor(15); imprimeString(e + e + e + e + e + e); setColor(12); imprimeString(a + a + a + "       "); setColor(15); imprimeString (d + b + b + c + "  " + d + b + b + b);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); setColor(12); imprimeString("   " + a + a + a + a + d + d); setColor(15); imprimeString(e + e + e + e); setColor(12); imprimeString(d + d + d + d + d + d + d + d); setColor(15); imprimeString(e + e + e + e); setColor(12); imprimeString(d + d + a + a + a + "    "); setColor(15); imprimeString(d + "  " + d + "  " + d + b + b + b);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); setColor(12); imprimeString("  " + a + a); setColor(15); imprimeString(e + e); setColor(12); imprimeString(d + d + d + d + d + d + d + d + d + d + d + d + d + d + d + d + d + d + d + d); setColor(15); imprimeString(e + e); setColor(12); imprimeString(a + a + "    "); setColor(15); imprimeString(d + c + c + b + "  " + d + c + c + c);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); setColor(12); imprimeString(" " + a + a + a); setColor(15); imprimeString(e + e + e + e); setColor(12); imprimeString(d + d + d + d); setColor(15); imprimeString(e + e + e + e + e + e + e + e); setColor(12); imprimeString(d + d + d + d); setColor(15); imprimeString(e + e + e + e); setColor(12); imprimeString(a + a + a);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); imprimeString(a + a); setColor(15); imprimeString(e + e + e + e + e + e); setColor(12); imprimeString(d + d); setColor(15); imprimeString(e + e + e + e + e + e + e + e + e + e + e + e); setColor(12); imprimeString(d + d); setColor(15); imprimeString(e + e + e + e + e + e); setColor(12); imprimeString(a + a);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); imprimeString(a + a); setColor(15); imprimeString(e + e + e + e + e + e); setColor(12); imprimeString(d + d); setColor(15); imprimeString(e + e + e + e + e + e + e + e + e + e + e + e); setColor(12); imprimeString(d + d); setColor(15); imprimeString(e + e + e + e + e + e); setColor(12); imprimeString(a + a );
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); imprimeString(a + a); setColor(15); imprimeString(e + e + e + e); setColor(12); imprimeString(d + d + d + d); setColor(15); imprimeString(e + e + e + e + e + e + e + e + e + e + e + e); setColor(12); imprimeString(d + d + d + d); setColor(15); imprimeString(e + e + e + e); setColor(12); imprimeString(a + a); setColor(15); imprimeString("    " + d + "  " + d + "  " + d + "  " + d + b + b + b + "  " + d + b + b + d + "  " + d + b + b + b + d + "  " + d + b + b + b + d);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); setColor(12); imprimeString(a + a + d + d + d + d + d + d + d + d + d + d); setColor(15); imprimeString(e + e + e + e + e + e + e + e); setColor(12); imprimeString(d + d + d + d + d + d + d + d + d + d + a + a + " "); setColor(15); imprimeString(c + "  " + d + "  " + d + "  " + d + "  " + d + b + b + b + "  " + d + " " + c + c + "  " + d + "   " + d + "  " + b + b + b + c + c);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); setColor(12); imprimeString(a + a + d + d + d + d+d+d); setColor(14); imprimeString(d + d + d + d + d + d + d + d + d + d + d + d + d + d + d + d); setColor(12); imprimeString(d+d+ d + d + d + d + a + a); setColor(15); imprimeString(" " + d + c + c + d + "  " + b + c + c + b + "  " + d + c + c + c + "  " + d + c + c + d + "  " + d + c + c + c + d + "  " + d + c + c + c + d);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); setColor(12); imprimeString(a + a + a + a + a + a ); setColor(14); imprimeString(d+d+d + d + d + d + " " + " " + d + d + d + d + " " + " " + d + d + d + d+d+d); setColor(12); imprimeString( a + a + a + a + a + a);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); imprimeString("  "+a + a + a + a); setColor(14); imprimeString(d + d + d + d + d + d + " " + " " + d + d + d + d + " " + " " + d + d + d + d + d + d); setColor(12); imprimeString(a + a + a + a);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); imprimeString("    "+a + a); setColor(14); imprimeString(d + d + d + d + d + d + d + d + d + d + d + d + d + d + d + d + d + d + d + d); setColor(12); imprimeString(a + a);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); imprimeString("     "+a + a + a); setColor(14); imprimeString(d + d + d + d + d + d + d + d + d + d + d + d + d + d + d + d); setColor(12); imprimeString(a + a + a);
	//---------------------------------------------------------------------------------------------
	y++; setCursor(x, y); imprimeString("       " + a + a + a + a + a + a + a + a + a + a + a + a + a + a + a + a + a + a);
	y = y - 2; x = x + 31; setCursor(x, y);
	cargando(68, 24, 1, 36, 4,15,"\260",2);
}
void imprimeRellenoRectangulo(int x, int y, int ancho, int largo, int color, string relleno) {
	setCursor(x, y);
	for (int j = 0; j < ancho; j++) {
		for (int i = 0; i < largo; i++) { if (color != 0) { setColor(color); } imprimeString(relleno); }y++; setCursor(x, y);
	}
}

void imprimeRectangulo(int x, int y, int ancho, int largo, int color,string relleno, int colorRelleno) {
	if (color != 0) { setColor(color); }setCursor(x, y); imprimeString("\311"); for (int i = 0; i < largo; i++) { imprimeString("\315"); }imprimeString("\273");
	setCursor(x + 1, y + 1); if (relleno != " ") { setColor(colorRelleno); imprimeRellenoRectangulo(x + 1, y + 1, ancho, largo, colorRelleno, relleno); }
	setColor(color);for (int a = 0; a < ancho; a++) {y++; setCursor(x, y); imprimeString("\272"); setCursor(x + largo+1, y); imprimeString("\272");}
	y++; setCursor(x, y); imprimeString("\310"); for (int i = 0; i < largo; i++) { imprimeString("\315"); }imprimeString("\274");
}

void imprimeMarco(int x, int y, int ancho, int largo, int color) {
	if (color != 0) { setColor(color); } setCursor(x, y); imprimeString("\311"); for (int i = 0; i < largo; i++) { imprimeString("\315"); }imprimeString("\273");
	for (int j = 0; j < ancho; j++) {
		y++; setCursor(x, y); imprimeString("\272"); for (int i = 0; i < largo; i++) {  imprimeString(" "); }if (color != 0) { setColor(color); } imprimeString("\272");
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
	*/
	imprimeMarco(x, y, ancho, largo, color);
	if (largo>7 && ancho>5&& espaciadoInterno>3) {
		// se cumplen las dimensiones, sino la figura quedara desalineada
		if (ancho != 0 || largo != 0 || espaciadoInterno != 0 || ancho % 2 != 0 || largo % 2 != 0 || espaciadoInterno % 2 != 0) {
			//si alguno no es par, quedara desalineada
			if (relleno != " ") {// si quiere que el relleno quede vacio, simplemente no lo pinto
				imprimeRellenoRectangulo(x + 1, y + 1, espaciadoInterno / 2 - 1, largo, colorRelleno, relleno);//Relleno Arriba
				imprimeRellenoRectangulo(x + 1, y + ancho + 1 - espaciadoInterno / 2, espaciadoInterno / 2, largo, colorRelleno, relleno);//Relleno Abajo
				imprimeRellenoRectangulo(x + 1, y + espaciadoInterno / 2, ancho - espaciadoInterno + 2, espaciadoInterno, colorRelleno, relleno);//Relleno Izquierdo
				imprimeRellenoRectangulo(x + largo - espaciadoInterno + 1, y + espaciadoInterno / 2, ancho - espaciadoInterno + 2, espaciadoInterno, colorRelleno, relleno);// Relleno Derecho
			}
			imprimeMarco(x + espaciadoInterno, y + espaciadoInterno / 2, ancho - espaciadoInterno, largo - 2 * espaciadoInterno, color);
		}
	}
}

void cargando(int x, int y, int ancho, int largo, int segundos, int color, string relleno, int colorRelleno) {
	/* Antes de utilizar este metodo tomar en cuenta que solo funciona si la division entre el largo
	y los segundos es una division entera, Porque, como el cargando se divide en partes por segundo para cargarlo al
	no ser exacta siempre faltara una parte del final que pues son decimales y el ciclo no detecta los decimales por ser entero*/
	if (largo%segundos == 0) {
		imprimeMarco(x, y, ancho, largo, color);
		int aux = largo / segundos;
		int auxLargo = aux;
		setColor(color);
		for (int i = 0; i < segundos; i++) {
			imprimeRellenoRectangulo(x + 1, y + 1, ancho, auxLargo, colorRelleno, "\333");
			auxLargo = auxLargo + aux;
			Sleep(1000);
		}
	}
}