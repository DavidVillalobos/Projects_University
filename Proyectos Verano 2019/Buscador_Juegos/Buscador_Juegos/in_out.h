#ifndef IN_OUT_H
#define IN_OUT_H

#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

void imprimeInt(int);
void imprimeChar(char);
void imprimeString(string);
int leerInt();
char leerChar();
string leerString();
void limpiaPantalla();
void setColor(int);
void setCursor(int, int);
void pausa();
void limpiarBuffer();
int convertirInt(string);
double convertirDouble(string);
string StringChar(char);
void pantallaPrincipal();
void imprimeRectangulo(int x, int y, int ancho, int largo, int color, string relleno, int colorRelleno);
void imprimeMarco(int x, int y, int ancho, int largo, int color);
void imprimeMarcoDoble(int x, int y, int ancho, int largo, int color, string relleno, int colorRelleno, int espaciadoInterno);
void cargando(int x, int y, int ancho, int largo, int segundos,int color, string relleno, int colorRelleno);
#endif