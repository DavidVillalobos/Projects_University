#include "vuelo.h"

vuelo::vuelo(string id, string fecha, string aeroLlegada, string aeroSalida, string piloto, int hHoraSalida, int mHoraSalida, int precio, avion *av, ruta *rut) {
	this->id = id;
	this->fecha = fecha;
	this->aeroLlegada = aeroLlegada;
	this->aeroSalida = aeroSalida;
	this->piloto = piloto;
	this->hHoraSalida = hHoraSalida;
	this->mHoraSalida = mHoraSalida;
	this->precio = precio;
	this->av = av;
	this->rut = rut;
	setHhoraLlegada();
	setMhoraLlegada();
	cantTyP = 0;
	int fil = av->getFila();
	int col = av->getCol();
	int cant = av->getCantPasajeros();
	coleccionTiquete = new tiquete*[cant];
	for (int i = 0; i<cant; i++) {
		coleccionTiquete[i] = NULL;
	}
	lista = new pasajero*[cant];
	for (int i = 0; i<cant; i++) {
		lista[i] = NULL;
	}
	asiento = new bool*[col];
	for (int i = 0; i<col; i++) {
		asiento[i] = new bool[fil];
	}
	for (int i = 0; i < av->getFila(); i++) {
		for (int u = 0; u < av->getCol(); u++) {
			asiento[u][i] = true;
		}
	}
}

void vuelo::setId(string id) { this->id = id; }

void vuelo::setFecha(string fecha) { this->fecha = fecha; }

void vuelo::setHhoraLlegada() {
	int suma = hHoraSalida + rut->getHduracion();
	(suma >= 24) ? hHoraLlegada = suma - 24 : hHoraLlegada = suma;
}

void vuelo::setMhoraLlegada() {
	int suma = mHoraSalida + rut->getMduracion();
	(suma >= 60) ? mHoraLlegada = suma - 60,(hHoraLlegada+1>24)? hHoraLlegada = hHoraLlegada+1 - 24 : hHoraLlegada = hHoraLlegada+1: mHoraLlegada = suma;
}

void vuelo::setHhoraSalida(int h) { hHoraSalida = h; }

void vuelo::setMhoraSalida(int m) { mHoraSalida = m; }

void vuelo::setAeroLlegada(string aLlegada) { aeroLlegada = aLlegada; }

void vuelo::setAeroSalida(string aSalida) { aeroSalida = aSalida; }

void vuelo::setPiloto(string piloto) { this->piloto = piloto; }

void vuelo::setPrecio(int precio) { this->precio = precio; }

void vuelo::setCantTyP(int cant) { cantTyP = cant; }

void vuelo::setAv(avion *av) { this->av = av; }

void vuelo::setRut(ruta *rut) { this->rut = rut; }

string vuelo::getId() { return id; }

string vuelo::getFecha() { return fecha; }

string vuelo::getAeroLlegada() { return aeroLlegada; }

string vuelo::getAeroSalida() { return aeroSalida; }

string vuelo::getPiloto() { return piloto; }

int vuelo::getHhoraLlegada() { return hHoraLlegada; }

int vuelo::getMhoraLlegada() { return mHoraLlegada; }

int vuelo::getHhoraSalida() { return hHoraSalida; }

int vuelo::getMhoraSalida() { return mHoraSalida; }

int vuelo::getPrecio() { return precio; }

int vuelo::getCantTyP() { return cantTyP; }

avion* vuelo::getAv() { return av; }

ruta* vuelo::getRut() { return rut; }

tiquete* vuelo::getTiquete(int pos) {
	return coleccionTiquete[pos];
}

pasajero* vuelo::getPasajero(int pos) {
	return lista[pos];
}

void vuelo::mostrarAsientos() {
	imprimeString("\n                               ASIENTOS DISPONIBLES DEL VUELO "); imprimeString(id); imprimeString("\n");
	char letras[6] = { 'A','B','C','D','E','F' };
	imprimeString("  ");
	for (int u = 1; u < 10; u++) {
		imprimeString(" ."); imprimeInt(u);
	}
	for (int u = 10; u < av->getFila() + 1; u++) {
		imprimeString(" "); imprimeInt(u);
	}
	imprimeString("\n");
	for (int i = 0; i < av->getCol(); i++) {
		color(15);
		imprimeChar(letras[i]); imprimeString(" ");
		for (int u = 0; u<av->getFila(); u++) {
			(asiento[i][u] == true) ? color(10) : color(12);
			imprimeString(" []");
		}
		imprimeString("\n");
		if (i == 1 || i == 3) {
			imprimeString("\n");
		}
	}
	color(15);
}

void vuelo::listaPasajeros() {
 color(14); imprimeString("\n\n        °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
			   imprimeString("        °°                                      °°\n");
			   imprimeString("        °°          "); color(15); imprimeString("LISTA PASAJEROS"); color(14); imprimeString("             °°\n");
			   imprimeString("        °°                                      °°\n");
			   imprimeString("        °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n"); color(15);
	for (int i = 0; i<cantTyP; i++) {
		imprimeString("   "); imprimeInt(i + 1); imprimeString(") ");
		imprimeString(lista[i]->toString());
	}
}

void vuelo::listaTiquetes() {
	color(14); imprimeString("\n\n        °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
	imprimeString("        °°                                      °°\n");
	imprimeString("        °°          "); color(15); imprimeString("LISTA TIQUETES"); color(14); imprimeString("              °°\n");
	imprimeString("        °°                                      °°\n");
	imprimeString("        °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n"); color(15);
	for (int i = 0; i < cantTyP; i++) {
			imprimeString("\n __________________________________________________________\n\n");
			imprimeString("   Tiquete #"); imprimeInt(i + 1); imprimeString("\n");
			imprimeString(coleccionTiquete[i]->toString());
			imprimeString("\n __________________________________________________________\n\n\n");
	}
}

string vuelo::toString() {
	stringstream s;
	s << endl;
	s << "   ID: " << getId() << "\n\n   Ruta: " << rut->getOrigen() << "-" << rut->getDestino() << "   Fecha: " << getFecha() << endl;
	s << "   Aeropuerto de Salida: " << getAeroSalida() << "   Hora de Salida: " << getHhoraSalida() << ":" << getMhoraSalida() << endl;
	s << "   Aeropuerto de Llegada: " << getAeroLlegada() << "   Hora de Llegada: " << getHhoraLlegada() << ":" << getMhoraLlegada() << endl;
	s << "   Avion: " << getAv()->getId() << "   Piloto: " << getPiloto() << "   Precio: " << getPrecio() << endl;
	return s.str();
}

int vuelo::LetraAsiento(char col) {
	switch (col) {
	case 'a': return 0;
	case 'b': return 1;
	case 'c': return 2;
	case 'd': return 3;
	case 'e': return 4;
	case 'f': return 5;
	case 'A': return 0;
	case 'B': return 1;
	case 'C': return 2;
	case 'D': return 3;
	case 'E': return 4;
	case 'F': return 5;
	default: return -1;
	}
}

int vuelo::buscarTiquete(string id) {
	for (int i = 0; i < cantTyP; i++) {
		if (coleccionTiquete[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

bool vuelo::insertarTiquete(tiquete *t) {
	if (cantTyP < av->getCantPasajeros()) {
		for (int i = 0; i<cantTyP; i++) {
			if (coleccionTiquete[i]->getId() == t->getId()) {
				imprimeString("\n Lo sentimos, este tiquete no est\240 disponible");
				Sleep(2000);
				return false;
			}
			if (coleccionTiquete[i]->getIdPers()== t->getIdPers()) {
				imprimeString("\n Lo sentimos, no puedes tener m\240s de un asiento en este vuelo");
				Sleep(2000);
				return false;
			}
		}
		int fil = LetraAsiento(t->getFil()); 
		int col = t->getCol()- 1;
		if (asiento[fil][col] == true) {
			asiento[fil][col] = false;
			lista[cantTyP] = t->getPasajero();
			coleccionTiquete[cantTyP] = t;
			cantTyP++;
			imprimeString("\n La compra se realiz\242 con \202xito");
			Sleep(1000);
			return true;
		}
		imprimeString("\n Lo sentimos, este asiento no est\242 disponible");
		Sleep(1000);
		return false;
	}
	imprimeString("\n Lo sentimos los tiquetes para este vuelo est\n agotados");
	Sleep(1000);
	return false;
}

void vuelo::mostrarTiquete(string id) {
	int pos = buscarTiquete(id);
	if (pos == -1) {
		imprimeString("\n Lo sentimos, este tiquete no est\240 registrado en el vuelo");
		Sleep(2000);
	}
	else {
	imprimeString(coleccionTiquete[pos]->toString()+"\n");
	}
}

bool vuelo::eliminarTiquete(string id) {
	if (coleccionTiquete[cantTyP - 1]->getId() == id) {
		asiento[LetraAsiento(coleccionTiquete[cantTyP - 1]->getFil())][coleccionTiquete[cantTyP - 1]->getCol() - 1] = true;
		delete lista[cantTyP - 1];
		delete coleccionTiquete[cantTyP - 1];
		lista[cantTyP - 1] = NULL;
		coleccionTiquete[cantTyP - 1] = NULL;
		cantTyP--;
		imprimeString("\n El tiquete se elimin\242 con \202xito");
		Sleep(1000);
		return true;
	}
	else {
		int pos = buscarTiquete(id);
		if (pos != -1) {
			asiento[LetraAsiento(coleccionTiquete[pos]->getFil())][coleccionTiquete[pos]->getCol() - 1] = true;
			delete lista[pos];
			delete coleccionTiquete[pos];
			for (int i = pos; i < cantTyP - 1; i++) {
				lista[i] = lista[i + 1];
				coleccionTiquete[i] = coleccionTiquete[i + 1];
			}
			cantTyP--;
			imprimeString("\n El tiquete se elimin\242 con \202xito");
			Sleep(1000);
			return true;
		}
		imprimeString("\n Lo sentimos, este tiquete no est\240 registrado en el vuelo");
		Sleep(2000);
		return false;
	}
	
}

vuelo::~vuelo() {
	for (int j = 0; j < av->getFila(); j++) {
			delete[] asiento[j];
	}
	for (int i = 0; i<cantTyP; i++) {
		delete lista[i];
		delete coleccionTiquete[i];
		
	}
	
	delete[] asiento;
	delete[] lista;
	delete[] coleccionTiquete;
}