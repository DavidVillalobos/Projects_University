#include "Gimnasio.h"

Gimnasio::Gimnasio(int fila, int columna,int precioBoleto, int precioImpresion, string dia, string hora){
	this->hora = hora;
	this->dia = dia;
	this->fila = fila;
	this->columna = columna;
	this->precioBoleto = precioBoleto;
	this->precioImpresion = precioImpresion;
	asiento = new bool*[fila];
	for (int i = 0; i < fila;i++) {
		asiento[i] = new bool[columna];
	}
	for (int i = 0; i < fila; i++) {
		for (int j = 0; j < columna; j++) {
			asiento[i][j] = true;
		}
	}
	tamanno = fila * columna;
	cantidad = 0;
	vector = new Tiquete*[tamanno];
	for (int i = 0; i < tamanno;i++) {
		vector[i] = NULL;
	}
}

Gimnasio::~Gimnasio(){
	for (int i = 0; i < tamanno;i++) {
		delete vector[i];
	}
	delete vector;
	for (int i = 0; i < fila; i++) {
		delete []asiento[i];
	}
	delete[] asiento;
}

bool **Gimnasio::getAsientos() { return asiento; }

bool Gimnasio::getAsiento(int fila, int columna) { return asiento[fila][columna]; }

void Gimnasio::setAsiento(int fila, int columna, bool valor) {  asiento[fila][columna]=valor; }

int Gimnasio::getCantidad(){ return cantidad; }

int Gimnasio::getTamanno(){ return tamanno; }

int Gimnasio::getColumnas(){ return columna; }

int Gimnasio::getFilas(){ return fila; }

string Gimnasio::getDia(){ return dia; }

string Gimnasio::getHora(){ return hora; }

Tiquete * Gimnasio::getTiquete(int pos){ return vector[pos]; }

int Gimnasio::getPrecioBoleto(){ return precioBoleto; }

int Gimnasio::getPrecioImpresion(){ return precioImpresion; }

void Gimnasio::setCantidad(int cantidad) {  this->cantidad = cantidad; }

void Gimnasio::setDia(string dia) { this->dia = dia; }

void Gimnasio::setHora(string hora) { this->hora = hora; }

void Gimnasio::setPrecioBoleto(int precioBoleto) { this->precioBoleto = precioBoleto; }

void Gimnasio::setPrecioImpresion(int precioImpresion) {  this->precioImpresion = precioImpresion;  }

bool Gimnasio::insertarTiquete(Tiquete *nuevo) {
	if (cantidad<tamanno) {
		vector[cantidad] = nuevo;
		cantidad++;
		return true;
	}
	return false; 
}

void Gimnasio::toStringMatriz(int x, int y){
	int xAux = x;
	string letras[50] = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","AA","AB","AC","AD","AE","AF","AG","AH","AI","AJ","AK","AL","AM","AN","AO","AP","AQ","AR","AS","AT","AU","AV","AW","AX"};
	for (int a = 0; a < columna; a++) { setColor(15); setCursor(xAux + 2, y - 1); imprimeString(letras[a]); xAux += 3; }
	xAux = x;
	for (int i = 0; i < fila; i++) {
		setColor(15); setCursor(xAux - 2, y); imprimeInt(i + 1);
		for (int a = 0; a < columna; a++) {
			setCursor(xAux + 1, y);
			(asiento[i][a]) ? setColor(10): setColor(12);
			imprimeString("[ ]");
			xAux += 3;
		}
		y += 1;
		xAux = x;
	}
}

string Gimnasio::toStringTiquetes(){
	stringstream s;
	s << "LISTA DE TIQUETES CONCIERTO "<<dia<<" - "<<hora<<"\n\n";
	for (int i = 0; i < cantidad; i++) {
		s<<vector[i]->toString()<<"\n";
	}
	return s.str();
}


Tiquete* Gimnasio::buscarTiquete( string asiento) {
	for (int i = 0; i < cantidad; i++){
		if (vector[i]->getAsiento()==asiento) {
			return vector[i];
		}
	}
	return NULL;
}