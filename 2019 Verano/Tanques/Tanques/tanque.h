#ifndef TANQUE_H 
#define TANQUE_H
#include<string>
using namespace std;
#include "in_out.h"
class tanque;
class bala;
#include "bala.h"
class tanque {
private:
	int X,Y,limArriba, limAbajo, limIzq, limDer;
	int vidas,salud,disparos,jugador;
	int puntuacion,direccion,color;
	string usuario;
public:
	tanque(int X, int Y, int jugador, int limArriba, int limAbajo, int limIzq, int limDer, string usuario, int direccion, int color);
	int getX();
	int getY();
	int getVidas();
	int getDisparos();
	int getJugador();
	string getUsuario();
	int getPuntuacion();
	int getDireccion();
	int getSalud();
	int getColor();
	int getLimArriba();
	int getLimAbajo();
	int getLimIzq();
	int getLimDer();
	void setX(int);
	void setY(int);
	void setVidas(int);
	void setDisparos(int);
	void setJugador(int);
	void setUsuario(string);
	void setPuntuacion(int);
	void setDireccion(int);
	void setSalud(int);
	void imprimirTanque();
	void borrarPosAnt();
	void toString(int,int);
	void explosion();
	void revivir(int, int);
	void movimiento(char);
	bool moverIA(int,int, bala*);
	void recargar(int x,int y);
	~tanque();
};
#endif 