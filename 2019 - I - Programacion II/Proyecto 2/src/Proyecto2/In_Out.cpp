#include "In_Out.h"

   //conversion de texto normal a texto unicode
void setTextUnicode(){ _setmode(_fileno(stdout), 0x00020000); }

   //conversion de texto unicode a texto normal
void setTextNormal(){ _setmode(_fileno(stdout), _O_TEXT); }

void imprimir(wchar_t caracter){ wcout << caracter; }

void imprimir(int entero){ wcout << entero; }

void imprimir(wstring cadena){ wcout << cadena; }

void imprimir(wstring cadena, int sectiempo) { wcout << cadena; Sleep(sectiempo*1000); }

int leerInt(){
	int n;
	while (true) {
		if (wcin >> n) {
			wcin.clear();
			wcin.ignore(1024, L'\n');
			return n;
		}
		else {
			wcerr << L"Este valor es incorrecto, por favor digita un NÚMERO\n";
			wcin.clear();
			wcin.ignore(1024, L'\n');
		}
	}
}

wstring leerwString() {
	wstring cadena;
	while (true) {
		getline(wcin, cadena);
		if (!cadena.empty()) {  //Verificacion para que el cin no lea end═line como una palabra
			return cadena;
		}
	}
}

void setColor(int col) { 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

void setCursor(int x, int y) {
	HANDLE hcon; 
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y; 
	SetConsoleCursorPosition(hcon, dwPos);
}

void cleanBuffer() {
	cin.clear();
	cin.ignore(1024, '\n');
}

int stringToInt(wstring s) {
	wstringstream r(s);
	int v;
	r >> v;
	return v;
}

wstring ToString(wchar_t c) {
	return wstring(1, c);    //Este metodo convierte un caracter
	 //  A wstring un numero de veces n (n,wchar_t)
}

wchar_t stringTochar(wstring s) {
	return wchar_t(s[0]);
}

wstring intToString(int entero) {
	wstringstream s;
	s << entero;
	return s.str();
}

void mostrarCursor(bool visibilidad) {//    esconde el cursor
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = visibilidad;  //  set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

wstring mayorPalabra(wstring *opciones, int cant) {
	wstring mayor = opciones[0];
	for (int a = 1; a < cant; a++) {
		if (opciones[a].length() > mayor.length()) {
			mayor = opciones[a];
		}
	}
	return mayor;
}

int menuSeleccion(int x, int y, wstring *opciones, int cant, int color, int colorSelect, bool direccion) {
	wstring mayor;
	int pos_Simetrica;
	if (direccion) {
		mayor = mayorPalabra(opciones, cant);  //  Retorna la palabra con mas letras
		pos_Simetrica = int(mayor.length()) / 2; //   todo estos Dan warning pero necesito division entera
	}
	int *posY = new int[cant];
	int *posX = new int[cant];
	int canLetras;
	int opcSelect = 1;
	int selecAnt = opcSelect;
	wchar_t tecla = '*';
	mostrarCursor(false);//    Esconde el cursor
	for (int i = 0; i < cant; i++) {//   Guarda las posiciones simetricas de cada opcion 
		if (direccion) {
			canLetras = pos_Simetrica - int(opciones[i].length()) / 2; // apartir de la palabra mas larga
			x += canLetras;
			posX[i] = x;
			posY[i] = y;
			imprimeOpcion(x, y, opciones[i], color);
			x -= canLetras;
			y += 3;
		}
		else {
			posX[i] = x;
			posY[i] = y;
			imprimeOpcion(x, y, opciones[i], color);
			x += int(opciones[i].length()) + 6;
		}
	}
	imprimeOpcion(posX[0], posY[0], opciones[0], colorSelect);
	while (tecla != 13) {
		if (_kbhit()) {
			tecla = _getch();
			if (tecla == 72 || tecla == 80 || tecla == 75 || tecla == 77) {
				if (direccion) {
					switch (tecla) {
						case 72: {if (opcSelect != 1) { opcSelect--; }break; } // Tecla Arriba
						case 80: {if (opcSelect != cant) { opcSelect++; }break; }//  Tecla Abajo
					}
				}
				else {
					switch (tecla) {
						case 75: {if (opcSelect != 1) { opcSelect--; }break; } // Tecla Izquierda
						case 77: {if (opcSelect != cant) { opcSelect++; }break; }//  Tecla Derecha
					}
				}
				if (opcSelect != 0 && opcSelect != cant + 1) {
					imprimeOpcion(posX[selecAnt - 1], posY[selecAnt - 1], opciones[selecAnt - 1], color);
					imprimeOpcion(posX[opcSelect - 1], posY[opcSelect - 1], opciones[opcSelect - 1], colorSelect);
					selecAnt = opcSelect;
				}
			}
		}
	}
	delete[] posX;
	delete[] posY;
	return opcSelect;
}

void imprimeOpcion(int x, int y, wstring opcion, int color) {
	setColor(15); int can = int(opcion.length()); can += 2;
	setCursor(x, y); imprimir(L"╔"); for (int i = 0; i < can; i++) { imprimir(L"═"); }imprimir(L"╗");
	setCursor(x, y + 1); imprimir(L"║ "); setColor(color); imprimir(opcion); setColor(15); imprimir(L" ║");
	setCursor(x, y + 2); imprimir(L"╚"); for (int i = 0; i < can; i++) { imprimir(L"═"); }imprimir(L"╝");
}

bool menuBinario(int x, int y, int color, int colorSelect) {
	wstring vec[2] = { L"Cancelar",L"Confirmar" };
	return (menuSeleccion(x, y, vec, 2, color, colorSelect, false) == 2);
}

void pause() { system("pause"); }

void cls() { system("cls"); }

void imprimeTitulo() {
	setColor(3);
	imprimir(L"\n\n\n");
	imprimir(L"\t╒════════════════════════════════════════════════════════════════════════════════════════════╖\n");
	imprimir(L"\t║                                                                                            ║\n");
	imprimir(L"\t║   ◘◘◘◘◘◘◘◘◘◘◘◘    ◘◘◘◘◘◘◘◘◘◘◘◘◘◘  ◘◘◘◘◘◘          ◘◘◘◘◘◘  ◘◘◘◘◘◘◘◘◘◘◘◘◘◘  ◘◘◘◘◘◘◘◘◘◘◘◘◘◘   ║\n");
	imprimir(L"\t║   ◘◘        ◘◘◘◘  ◘◘          ◘◘  ◘◘  ◘◘◘◘◘◘  ◘◘◘◘◘◘  ◘◘  ◘◘          ◘◘  ◘◘          ◘◘   ║\n");
	imprimir(L"\t║   ◘◘  ◘◘◘◘    ◘◘  ◘◘  ◘◘◘◘◘◘  ◘◘  ◘◘       ◘◘◘◘       ◘◘  ◘◘  ◘◘◘◘◘◘  ◘◘  ◘◘  ◘◘◘◘◘◘◘◘◘◘   ║\n");
	imprimir(L"\t║   ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘◘◘      ◘◘◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘           ║\n");
	imprimir(L"\t║   ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘◘◘◘◘  ◘◘  ◘◘  ◘◘◘◘◘◘  ◘◘◘◘◘◘  ◘◘  ◘◘  ◘◘◘◘◘◘  ◘◘  ◘◘  ◘◘◘◘◘◘◘◘◘◘   ║\n");
	imprimir(L"\t║   ◘◘  ◘◘  ◘◘  ◘◘  ◘◘          ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘          ◘◘  ◘◘          ◘◘   ║\n");
	imprimir(L"\t║   ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘◘◘◘◘  ◘◘  ◘◘  ◘◘   ◘◘◘◘   ◘◘  ◘◘  ◘◘  ◘◘◘◘◘◘  ◘◘  ◘◘◘◘◘◘◘◘◘◘  ◘◘   ║\n");
	imprimir(L"\t║   ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘          ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘          ◘◘  ◘◘   ║\n");
	imprimir(L"\t║   ◘◘  ◘◘◘◘    ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘          ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘◘◘◘◘◘◘◘◘  ◘◘   ║\n");
	imprimir(L"\t║   ◘◘        ◘◘◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘          ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘  ◘◘          ◘◘   ║\n");
	imprimir(L"\t║    ◘◘◘◘◘◘◘◘◘◘◘◘   ◘◘◘◘◘◘  ◘◘◘◘◘◘  ◘◘◘◘◘◘          ◘◘◘◘◘◘  ◘◘◘◘◘◘  ◘◘◘◘◘◘  ◘◘◘◘◘◘◘◘◘◘◘◘◘◘   ║\n");
	imprimir(L"\t║                                                                                            ║\n");
	imprimir(L"\t╚════════════════════════════════════════════════════════════════════════════════════════════╝\n");
	setColor(15);
	imprimir(L"\t                         Autores:     Rebecca Garita   &   Luis Villalobos\n\n\t\t\t\t\t");
}

void imprimeSubtitulo() {
	setColor(3);
	imprimir(L"\n\n\t\t█▀▀▄ █▀▀█ █▀▄▀█ █▀▀█ █▀▀▀█\n");
	    imprimir(L"\t\t█  █ █▄▄█ █ █ █ █▄▄█ ▀▀▀▄▄\n");
	    imprimir(L"\t\t█▄▄▀ █  █ █   █ █  █ █▄▄▄█\n");
	setColor(15);
}

void imprimeNuevoJuego(){
	setColor(3);
	imprimir(L"\n\n\t\t   █ █  █ █▀▀▀ █▀▀█ █▀▀▀█   █▄  █ █  █ █▀▀▀ █   █ █▀▀▀█\n");
		imprimir(L"\t\t▄  █ █  █ █▀▀▀ █ ▄▄ █   █   █ █ █ █  █ █▀▀▀  █ █  █   █\n");
		imprimir(L"\t\t█▄▄█ ▀▄▄▀ █▄▄▄ █▄▄█ █▄▄▄█   █  ▀█ ▀▄▄▀ █▄▄▄  ▀▄▀  █▄▄▄█\n\n");
	setColor(15);
}

void imprimeCargarJuego() {
	setColor(3);
	imprimir(L"\n\n\t\t█▀▀█ █▀▀█ █▀▀█ █▀▀█ █▀▀█ █▀▀█      █ █  █ █▀▀▀ █▀▀█ █▀▀▀█\n");
		imprimir(L"\t\t█    █▄▄█ █▄▄▀ █ ▄▄ █▄▄█ █▄▄▀   ▄  █ █  █ █▀▀▀ █ ▄▄ █   █\n");
		imprimir(L"\t\t█▄▄█ █  █ █  █ █▄▄█ █  █ █  █   █▄▄█ ▀▄▄▀ █▄▄▄ █▄▄█ █▄▄▄█\n\n");
	setColor(15);
}

void imprimeModoPrueba() {
	setColor(3);
	setCursor(78,5);  imprimir(L"█▀▄▀█ █▀▀▀█ █▀▀▄ █▀▀▀█   █▀▀█ █▀▀█ █  █ █▀▀▀ █▀▀█ █▀▀█");
	setCursor(78,6);  imprimir(L"█ █ █ █   █ █  █ █   █   █▄▄█ █▄▄▀ █  █ █▀▀▀ █▀▀▄ █▄▄█");
	setCursor(78, 7); imprimir(L"█   █ █▄▄▄█ █▄▄▀ █▄▄▄█   █    █  █ ▀▄▄▀ █▄▄▄ █▄▄█ █  █");
	setColor(15);
	setCursor(0, 0);
}

void imprimirFelicidades() {
	setColor(10); imprimir(L"\n\n\n");
	imprimir(L"\t ▀  █▀▀▀  █▀▀▀  █    ▀█▀  █▀▀█ ▀█▀  █▀▀▄  █▀▀█  █▀▀▄  █▀▀▀  █▀▀▀█\n");
	imprimir(L"\t █  █▀▀▀  █▀▀▀  █     █   █     █   █  █  █▄▄█  █  █  █▀▀▀  ▀▀▀▄▄\n");
	imprimir(L"\t █  █     █▄▄▄  █▄▄█ ▄█▄  █▄▄█ ▄█▄  █▄▄▀  █  █  █▄▄▀  █▄▄▄  █▄▄▄█\n\n");

	imprimir(L"\t	     █▀▀█  █▀▀█  █▄  █  █▀▀█  █▀▀▀█ ▀▀█▀▀  █▀▀▀  █\n");
	imprimir(L"\t	     █ ▄▄  █▄▄█  █ █ █  █▄▄█  ▀▀▀▄▄   █    █▀▀▀  ▀\n");
	imprimir(L"\t	     █▄▄█  █  █  █  ▀█  █  █  █▄▄▄█   █    █▄▄▄  ▄\n");
	setColor(15);
}

void imprimirPerdiste() {
	setColor(12); imprimir(L"\n\n\n");
	imprimir(L"\t █     █▀▀█  █▀▀▀█ ▀▀█▀▀ ▀█▀  █▀▄▀█  █▀▀█\n");
	imprimir(L"\t █     █▄▄█  ▀▀▀▄▄   █    █   █ █ █  █▄▄█\n");
	imprimir(L"\t █▄▄█  █  █  █▄▄▄█   █   ▄█▄  █   █  █  █\n\n");

	imprimir(L"\t █▀▀█  █▀▀▀  █▀▀█  █▀▀▄ ▀█▀  █▀▀▀█ ▀▀█▀▀  █▀▀▀\n");
	imprimir(L"\t █▄▄█  █▀▀▀  █▄▄▀  █  █  █   ▀▀▀▄▄   █    █▀▀▀\n");
	imprimir(L"\t █     █▄▄▄  █  █  █▄▄▀ ▄█▄  █▄▄▄█   █    █▄▄▄\n");
	setColor(15);
}


wstring ahora() {
	wstringstream s;
	time_t current_time;
	struct tm local_time;
	time(&current_time);
	localtime(&current_time);
	int anno = local_time.tm_year + 1900;
	int mes = local_time.tm_mon + 1;
	int dia = local_time.tm_mday;
	int hora = local_time.tm_hour;
	int min = local_time.tm_min;
	int seg = local_time.tm_sec;
	s << dia << L" " << mes << L" " << anno << L") a las (" << hora << L":" <<min << L":" << seg;
	return s.str();
}