#ifndef JUEGO_H
#define JUEGO_H
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <fstream>
using namespace std;
#include "tanque.h"
#include "in_out.h"
#include "bala.h"
#include "jugadores.h"
class juego{
private:
	jugadores *listJugadores;
	jugadores **listEquipos;
	int limArriba, limAbajo, limIzq, limDer;
public:
	juego();
	void cargar();
	void menus();
	void modo_CLS_PVP();
	void modo_CLS_PVM();
	void modo_SPV_INDV();
	void modo_SPV_EQU();
	void modo_BTTL();
	bool disparo(tanque*, tanque*, bala*);
	~juego();
};
#endif

