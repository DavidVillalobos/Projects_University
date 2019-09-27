#include <sstream>
#include <iostream>
#include<conio.h>
#include <Windows.h>
#include "Fecha.h"
#include<typeinfo>
using namespace std;
void print(int);
void print(string);
void print(float);
int readInt();
float readFloat();
void print(char);
string readLine();
void setColor(int);
void setCursor(int, int);
void cleanBuffer();
int stringToInt(string);
string intToString(int);
string floatToString(float);
double stringToDouble(string);
string charToString(char);
void imprimeRellenoCuadrilatero(int, int, int, int, int, string);
void imprimeMarco(int, int, int, int, int);
void imprimeMarcoDoble(int x, int y, int ancho, int largo, int color, string relleno, int colorRelleno, int espaciadoInterno);
void mostrarCursor(bool);
int menuSeleccionLista(int x, int y, string *opciones,int cant, int color, int colorSelec);
int menuSeleccionCuadrilatero(int x, int y, int columnas, int filas, string *opciones, int cant, int color, int colorSelec);
void pintarSeleccion(int, int, string, int);
string mayorPalabra(string *opciones, int cant);
string fuente(string);
string superior(char);
string medio(char);
string inferior(char);
char mayuscula(char);
string convertirMayuscula(string);
bool menuBinario(int, int, int, int);
void pause();
void cls();
void pedirFecha(int&, int&, int&);

