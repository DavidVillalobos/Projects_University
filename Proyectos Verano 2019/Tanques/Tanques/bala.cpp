#include "bala.h"

bala::bala(int X, int Y ,int limArriba, int limAbajo, int limIzq, int limDer) {
	this->X = X;
	this->Y = Y;
	this->limArriba = limArriba;
	this->limAbajo = limAbajo;
	this->limIzq = limIzq;
	this->limDer = limDer;
}

void bala::mover() {
	borrar();
	switch (direccion) {
	case 1: {Y--; break; }
	case 2: {X++; break; }
	case 3: {Y++; break; }
	case 4: {X--; break; }
	default: {break; }
	}
	pintar();
}
int bala::getDireccion() { return direccion; }
int bala::getX() {return X;}
int bala::getY() { return Y; }
void bala::borrar() {setCursor(X,Y); imprimeString(" ");}
void bala::pintar() { setCursor(X, Y);imprimeString("*");}
void bala::setDireccion(int direccion) { this->direccion = direccion; }
void bala::setX(int X) { this->X = X; }
void bala::setY(int Y) { this->Y = Y; }

bool bala::colision(tanque * J1,tanque *J2){
	if (  X >= J2->getX()&&   X< J2->getX()+3  && Y >= J2->getY() && Y < J2->getY()+2) {
		borrar();
		if (J2->getSalud() == 1) { 
			J2->setVidas(J2->getVidas() - 1);
			J2->setSalud(J2->getSalud() - 1);
			J2->explosion();
			if (J2->getVidas()>0) {
				J1->setPuntuacion(J1->getPuntuacion() + 100);
				J2->setSalud(3);
			}
			else {
				J1->setPuntuacion(J1->getPuntuacion() + 500);
			}
		}
		else { 
			J2->borrarPosAnt(); Sleep(60);
			J2->imprimirTanque(); Sleep(60);
			J2->borrarPosAnt(); Sleep(60);
			J2->imprimirTanque();
			J2->setSalud(J2->getSalud() - 1); 
			J1->setPuntuacion(J1->getPuntuacion() + 50);
		}
		return true;
	}
	return false;
}

bool bala::direccionar(tanque *J) {
	switch (direccion) {
	case 1: {if (J->getY() > limArriba + 2) { X = J->getX() + 1; Y = J->getY() - 1; return true;}return false; }//Arriba
	case 2: {if (J->getX() + 4 < limDer) { X = J->getX() + 3; Y = J->getY(); return true;}return false; }//Derecha
	case 3: {if (J->getY() + 2 <  limAbajo) { X = J->getX() + 1; Y = J->getY() + 2; return true;}return false; }//Abajo
	case 4: {if (J->getX() > limIzq + 2) { X = J->getX() - 1; Y = J->getY(); return true;}return false; }//Izquierda
	}
}

void bala::explosion() {
	Sleep(50);
	setCursor(X, Y); imprimeString("*");
	setCursor(X-1, Y+1); imprimeString("* *");
	setCursor(X, Y+2); imprimeString("*");
	Sleep(40);
	setCursor(X, Y); imprimeString(" ");
	setCursor(X-1, Y + 1); imprimeString(" * ");
	setCursor(X, Y + 2); imprimeString(" ");
	Sleep(30);
	setCursor(X, Y); imprimeString("*");
	setCursor(X - 1, Y + 1); imprimeString("* *");
	setCursor(X, Y + 2); imprimeString("*");
	Sleep(20);
	setCursor(X, Y); imprimeString(" ");
	setCursor(X - 1, Y + 1); imprimeString(" * ");
	setCursor(X, Y + 2); imprimeString(" ");
	Sleep(10);
	setCursor(X, Y); imprimeString("*");
	setCursor(X - 1, Y + 1); imprimeString("* *");
	setCursor(X, Y + 2); imprimeString("*");
	Sleep(5);
	setCursor(X, Y); imprimeString(" ");
	setCursor(X - 1, Y + 1); imprimeString("   ");
	setCursor(X, Y + 2); imprimeString(" ");
}
bala::~bala(){}
