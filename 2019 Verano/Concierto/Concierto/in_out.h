#ifndef IN_OUT_H
#define IN_OUT_H

#include <string>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <conio.h>
using std::string;
using std::cout;
using std::cin;
using std::stringstream;
void imprimeInt(int);
void imprimeChar(char);
void imprimeString(string);
int leerInt();
char leerChar();
string leerString();
void setColor(int);
void setCursor(int, int);
void limpiarBuffer();
int convertirInt(string);
string convertirString(int);
double convertirDouble(string);
string StringChar(char);
void imprimeCuadrilatero(int x, int y, int ancho, int largo, int color, string relleno, int colorRelleno);
void imprimeRellenoCuadrilatero(int, int, int, int, int, string);
void imprimeMarco(int, int, int, int, int);
void imprimeMarcoDoble(int x, int y, int ancho, int largo, int color, string relleno, int colorRelleno, int espaciadoInterno);
void cargando(int, int, int, int, int, int, string, int);
void mostrarCursor(bool);
int menuSeleccionLista(int x, int y, string *opciones, int cant, int color, int colorSelec, bool direccion);
int menuSeleccionCuadrilatero(int x, int y, int columnas, int filas, string *opciones, int cant, int color, int colorSelec);
void pintarSeleccion(int, int, string, int);
int convertirLetra(string);
char LetraMayuscula(char);
void menuSeleccionAsiento(int x, int y,int &filas, int &columnas);
string conLetraNum(int);
string palabraMayuscula(string);
void Regalo(int,int,int,int);
#endif