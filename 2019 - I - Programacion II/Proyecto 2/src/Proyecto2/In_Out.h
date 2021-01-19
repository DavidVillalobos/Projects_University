#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include<fstream>
#include<conio.h>
#include<Windows.h>
#include <fcntl.h> // Estos archivos son
#include <io.h>    // incluidos para imprimir
#include <stdio.h> // utilizando Unicode  
#include <time.h>
using namespace std;

void imprimir(wchar_t);
void imprimir(int);
void imprimir(wstring);
void imprimir(wstring, int);

int leerInt();
wstring leerwString();

void setColor(int);
void setCursor(int, int);
void cleanBuffer();
void mostrarCursor(bool);
void pause();
void cls();

void setTextUnicode();
void setTextNormal();
int stringToInt(wstring);
wstring intToString(int);
wchar_t stringTowchar_t(wstring);

wstring mayorPalabra(wstring*, int);

int menuSeleccion(int, int, wstring*, int, int, int, bool);
void imprimeOpcion(int, int, wstring, int);
bool menuBinario(int, int, int, int);

void imprimeTitulo();
void imprimeSubtitulo();
void imprimeNuevoJuego();
void imprimeCargarJuego();
void imprimeModoPrueba();
void imprimirFelicidades();
void imprimirPerdiste();

wstring ahora();
