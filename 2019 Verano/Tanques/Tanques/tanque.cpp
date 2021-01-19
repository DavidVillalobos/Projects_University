#include "tanque.h"

tanque::tanque(int X, int Y, int jugador, int limArriba, int limAbajo, int limIzq, int limDer, string usuario, int direccion, int color){
	this->X=X;
	this->Y=Y;
	this->jugador=jugador;
	this->limArriba=limArriba;
	this->limAbajo=limAbajo;
	this->limIzq=limIzq;
	this->limDer=limDer;
	this->usuario=usuario;
	this->direccion=direccion;
	this->color = color;
	vidas = 3;
	disparos = 5;
	puntuacion = 0;
	salud = 3;
}

int tanque::getX() { return X; }

int tanque::getY(){ return Y; }

int tanque::getVidas() { return vidas; }

int tanque::getDisparos() { return disparos; }

int tanque::getJugador() { return jugador; }

string tanque::getUsuario() { return usuario; }

int tanque::getPuntuacion() { return puntuacion; }

int tanque::getDireccion() { return direccion; }

int tanque::getSalud() { return salud; }

int tanque::getColor(){return color;}

int tanque::getLimArriba(){return limArriba;}

int tanque::getLimAbajo(){return limAbajo;}

int tanque::getLimIzq(){return limIzq;}

int tanque::getLimDer(){return limDer;}

void tanque::setX(int X) { this->X = X; }

void tanque::setY(int Y){ this->Y = Y; }

void tanque::setVidas(int vidas){ this->vidas = vidas; }

void tanque::setJugador(int jugador) { this->jugador = jugador; }

void tanque::setDisparos(int disparos) { this->disparos = disparos; }

void tanque::setUsuario(string usuario) { this->usuario = usuario; }

void tanque::setPuntuacion(int puntuacion) { this->puntuacion=puntuacion; }

void tanque::setDireccion(int direccion) { this->direccion = direccion; }

void tanque::setSalud(int salud) { this->salud = salud; }

void tanque::imprimirTanque(){
	setColor(color);
	if (vidas > 0) {
		switch (direccion) {
		case 1: {
			setCursor(X, Y); imprimeString("\334\333\334");
			setCursor(X, Y + 1); imprimeString("\337 \337");
			break;
		}
		case 2: {
			setCursor(X, Y); imprimeString("\337\333\334");
			setCursor(X, Y + 1); imprimeString("\337\337");
			break;
		}
		case 3: {
			setCursor(X, Y); imprimeString("\334 \334");
			setCursor(X, Y + 1); imprimeString("\337\333\337");
			break;
		}
		case 4: {
			setCursor(X, Y); imprimeString("\334\333\337");
			setCursor(X, Y + 1); imprimeString(" \337\337");
			break;
		}
		default: {break; }
		}
	}
	else {
		borrarPosAnt();
		setCursor(X, Y); imprimeString("\305"); setCursor(X, Y+1); imprimeString("\337");
	}
}

void tanque::borrarPosAnt(){
	setCursor(X, Y); imprimeString("   ");
	setCursor(X, Y + 1); imprimeString("   ");
}

void tanque::toString(int x, int y) {
	setColor(15);
	if (vidas>0) {	
		y++; setCursor(x, y); imprimeString(" Jugador #"); imprimeInt(jugador);
		y++; setCursor(x, y); imprimeString(" Usuario: "+usuario);
		y++; setCursor(x, y); imprimeString("                 "); setCursor(x, y); imprimeString("Vidas: "); for (int i = 0; i < vidas; i++) { cout << " \376"; }
		y++; setCursor(x, y); imprimeString("                 "); setCursor(x, y); imprimeString("Salud: "); for (int i = 0; i < salud; i++) { cout << " +"; }
		y++; setCursor(x, y); imprimeString("Puntuacion: "); imprimeInt(puntuacion);
		y++;setCursor(x, y); imprimeString("                  ");setCursor(x, y); imprimeString("Balas: "); for (int i = 0; i < disparos; i++) { cout << " *"; }
	}
	else {
		y++; setCursor(x, y); imprimeString("                 "); 
		y++; setCursor(x, y); imprimeString("                 ");
		y++; setCursor(x, y); imprimeString("  " + usuario + " Ha Muerto ");
		y++; setCursor(x, y); imprimeString("                 "); 
		y++; setCursor(x, y); imprimeString("                 ");
		y++; setCursor(x, y); imprimeString("                 "); 
	
	}
}

void tanque::explosion() {
	borrarPosAnt();
	setColor(color);
	setCursor(X, Y); imprimeString(" \317\317 ");
	setCursor(X, Y + 1); imprimeString("\317\317\317\317");
	setCursor(X, Y + 2); imprimeString(" \317\317 ");
	Sleep(200);
	setCursor(X, Y); imprimeString("    ");
	setCursor(X, Y + 1); imprimeString("     ");
	setCursor(X, Y + 2); imprimeString("    ");
	Sleep(200);
	setCursor(X, Y); imprimeString("\317  \317");
	setCursor(X, Y + 1); imprimeString(" \317\317");
	setCursor(X, Y + 2); imprimeString("\317  \317");
	Sleep(200);
	setCursor(X, Y); imprimeString("    ");
	setCursor(X, Y + 1); imprimeString("   ");
	setCursor(X, Y + 2); imprimeString("    ");
	Sleep(200);
	setCursor(X, Y); imprimeString(" \317\317 ");
	setCursor(X, Y + 1); imprimeString("\317\317\317\317");
	setCursor(X, Y + 2); imprimeString(" \317\317 ");
	Sleep(200);
	setCursor(X, Y); imprimeString("    ");
	setCursor(X, Y + 1); imprimeString("     ");
	setCursor(X, Y + 2); imprimeString("    ");
}

void tanque::revivir(int X, int Y){
	if (vidas>0) {
		disparos = 5;
		this->X = X;
		this->Y = Y;
		(jugador == 1) ? this->direccion=4: this->direccion = 2;
		imprimirTanque(); Sleep(60);
		borrarPosAnt(); Sleep(60);
		imprimirTanque(); Sleep(60);
		borrarPosAnt(); Sleep(60);
		imprimirTanque(); Sleep(60);
		borrarPosAnt(); Sleep(60);
		imprimirTanque(); Sleep(60);
		borrarPosAnt(); Sleep(60);
		imprimirTanque(); Sleep(60);
		borrarPosAnt(); Sleep(60);
		imprimirTanque(); Sleep(60);
		borrarPosAnt(); Sleep(60);
		imprimirTanque(); Sleep(60);
		borrarPosAnt(); Sleep(60);
		imprimirTanque(); Sleep(60);
	}
}

void tanque::movimiento(char tecla) {
	switch (tecla) {
	case 72: {if (Y > limArriba + 1) { Y--; direccion = 1; }break; }// Arriba
	case 'w': {if (Y > limArriba + 1) { Y--; direccion = 1; }break; }// Arriba
	case 77: {if (X + 2 < limDer) { X++; direccion = 2; }break; }//Derecha
	case 'd': {if (X + 2 < limDer) { X++; direccion = 2; }break; }//Derecha
	case 80: {if (Y + 2 < limAbajo + 1) { Y++; direccion = 3; }break; }//Abajo
	case 's': {if (Y + 2 < limAbajo + 1) { Y++; direccion = 3; }break; }//Abajo
	case 75: {if (X > limIzq + 1) { X--; direccion = 4; } break; }//Izquierda
	case 'a': {if (X > limIzq + 1) { X--; direccion = 4; } break; }//Izquierda
	default: {break;}
	}
}

bool tanque::moverIA(int x, int y, bala *J) {
	if (jugador==0) {
		if (y == Y) {// si estoy en la misma fila
				if (x < X) {// estoy a la derecha
					movimiento('a');// voy izquierda
				}
				else {// estoy a la izquierda
					movimiento('d');// voy derecha
				}
				// si estoy en su misma columna estaria en su misma posicion y en cualquiera de estos casos
				return true;// dispare
		}
		else {
			if (x == X) {// estoy en su misma columna
				if (y < Y) {// estoy abajo 
					movimiento('w');// voy arriba
				}
				else {// estoy arriba
					movimiento('s');// voy abajo
				}
				// si estoy en su misma fila estaria en su misma posicion y en cualquiera de estos casos
				return true;// dispare
			}
			else {int desde, hasta;
				switch (direccion) {
				case 1: {desde = x - 2; hasta = x + 2;
					if (desde< X && X < hasta) {
						if (y>Y) {
						movimiento('s');
						}
						else {
						movimiento('w');
						}
						return true;
					}
					break; }
				case 2: {desde = y - 1; hasta = y + 1; 
					if (desde < Y && Y < hasta) {
						if (x > X) {
						 movimiento('d');
						}
						else {
						 movimiento('a');
						}
						return true;
					}
					break; }
				case 3: {desde = x - 3; hasta = x + 1;
					if (desde < X && X < hasta) {
						if (y > Y) {
							movimiento('s');
						}
						else {
							movimiento('w');
						}
						return true;
					}
					break; }
				case 4: {desde = y - 2; hasta = y + 2; 
					if (desde < X && X < hasta) {
						if (x > X) {
							movimiento('d');
						}
						else {
							movimiento('a');
						}
						return true;
					}
				break; }
				}
				if (X > x && Y > y) {//Cuadrante 4
					if ((X - x) > (Y - y)) {// calcule la diferencia cual esta mas cerca
						movimiento('w');// voy arriba
					}
					else {
						movimiento('a');// voy abajo
					}
				}
				else {
					if (X < x && Y < y) {// Cuadrante 2
						if ((X - x) < (Y - y)) {// calcule la diferencia cual esta mas cerca
							movimiento('s');// voy abajo
						}
						else {
							movimiento('d');// voy derecha
						}
					}
					else {
						if (X > x && Y < y) {// Cuadrante 1
							if ((X - x) > (y - Y)) {// calcule la diferencia cual esta mas cerca
								movimiento('s');// voy abajo
							}
							else {
								movimiento('a');// voi izquierda
							}
						}
						else {
							if (X < x && Y > y) {// Cuadrante 3
								if ((x - X) > (Y - y)) {// calcule la diferencia cual esta mas cerca
									movimiento('w'); //Voy arriba
								}
								else {
									movimiento('d');// Voy derecha
								}
							}
						}
					}
				}
			}
		}
	}
	else {//Activando metodo de huir
		if (J!=NULL) {
			if ((J->getY() - 3) < Y &&  Y < (J->getY() + 3)) {
				if ((Y - limArriba) > (limAbajo - Y)) {// calcule la diferencia cual esta mas cerca
					if (limArriba!= X - 3) {
						movimiento('w');// voy Arriba
					}
					else {
						movimiento('s');// voy Abajo
					}
				}
				else {
					if (limAbajo != Y - 3) {
							movimiento('s');// voy Abajo
					}
					else {
						movimiento('w');// voy Arriba
					}
				}
				jugador = 0;
				return false;
			}
			if ((J->getX() - 3) < X &&  X < (J->getX() + 3)) {
				if ((X - limDer) > (limIzq - X)) {// calcule la diferencia cual esta mas cerca
					if (limDer!= X + 3) {
						movimiento('a');// voy Izquierda
					}
					else {
						movimiento('d');// voy Derecha
					}
				}
				else {
					if (limIzq != X - 3) {
						movimiento('d');// voy Derecha
					}
					else {
						movimiento('a');// voy Izquierda
					}
				}
				jugador = 0;
				return false;
			}
		}
		else {
			if ((y - 3) < Y &&  Y < (y + 3)) {
					if (limAbajo != Y - 3) {
						movimiento('s');// voy Abajo
						jugador = 0;
						return false;
					}
					else {
						movimiento('w');// voy Arriba
						movimiento('w');// voy Arriba
						movimiento('w');// voy Arriba
						movimiento('w');// voy Arriba
						jugador = 0;
						return false;
					}
					if (limArriba != Y + 3) {
						movimiento('w');// voy Arriba
						jugador = 0;
						return false;
					}
					else {
						movimiento('s');// voy Abajo
						movimiento('s');// voy Abajo
						movimiento('s');// voy Abajo
						movimiento('s');// voy Abajo
						jugador = 0;
						return false;
					}
			}
			if ((x - 3) < X &&  X < (x + 3)) {
					if (limDer != X + 3) {
						movimiento('a');// voy Izquierda
					}
					else {
						movimiento('d');// voy Derecha
						movimiento('d');// voy Derecha
						movimiento('d');// voy Derecha
						movimiento('d');// voy Derecha
					}
			}
		}
		jugador = 0;
	}
	return false;// no dispare
}

void tanque::recargar(int x, int y) {
	y += 6; setColor(15);
	setCursor(x, y); imprimeString("                  ");
	disparos = 5;
	setCursor(x, y); imprimeString("Balas: "); for (int i = 0; i < disparos; i++) { Sleep(30); cout << " \317"; }
}
tanque::~tanque(){}