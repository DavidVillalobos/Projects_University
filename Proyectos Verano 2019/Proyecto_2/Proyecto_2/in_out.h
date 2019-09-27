#ifndef IN_OUT_H
#define IN_OUT_H
#include <string>
#include <sstream>
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
int convertirLetra(char);
void imprimeMenu();
#endif