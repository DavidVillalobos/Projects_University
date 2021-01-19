#ifndef BALA_H
#define BALA_H
class tanque;
class bala;
#include "tanque.h"
#include "in_out.h"
class bala{
private:
	int X,Y,direccion, limArriba, limAbajo, limIzq, limDer;
public:
	int getDireccion();
	int getX();
	int getY();
	bala(int X, int Y, int limArriba, int limAbajo, int limIzq, int limDer);
	void mover();
	void borrar();
	void pintar();
	void setDireccion(int);
	void setX(int);
	void setY(int);
	bool colision(tanque*,tanque*);
	bool direccionar(tanque*);
	void explosion();
	~bala();
};
#endif
