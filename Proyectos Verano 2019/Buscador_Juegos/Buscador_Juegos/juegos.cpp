#include "juegos.h"
#include <iostream>
juegos::juegos(){
	primero = actual = NULL;
}

void juegos::insertarJuego(string nombre, string disponibilidad, etiquetas *listEtiquetas, string descripcion) {
	primero = new juego(nombre, disponibilidad, listEtiquetas, descripcion, primero);
}

bool juegos::insertarJuegoOrdenado(juego *insertar,etiquetas *listBusc) {
	juego *nuevo = new juego(insertar->getNombre(), insertar->getDisponibilidad(), insertar->getListEtiquetas(), insertar->getDescripcion(), NULL);
	if (primero == NULL) { 
		primero = nuevo;
		return true; 
	}
	if (primero->getSig() == NULL) {
		if (nuevo->getListEtiquetas()->porcentajeCompatibles(listBusc) > primero->getListEtiquetas()->porcentajeCompatibles(listBusc)) {
			nuevo->setSig(primero);
			primero = nuevo;
			return true;
		}
		primero->setSig(nuevo);
		return true; 
	}
	if (nuevo->getListEtiquetas()->porcentajeCompatibles(listBusc) > primero->getListEtiquetas()->porcentajeCompatibles(listBusc)) {
		primero = new juego(insertar->getNombre(), insertar->getDisponibilidad(), insertar->getListEtiquetas(), insertar->getDescripcion(), primero);
		return true;
	}
	actual = primero;
	while (actual->getSig() != NULL) {
		if (nuevo->getListEtiquetas()->porcentajeCompatibles(listBusc) > actual->getSig()->getListEtiquetas()->porcentajeCompatibles(listBusc)) {
			nuevo->setSig( actual->getSig());
			actual->setSig(nuevo);
			return true;
		}
		actual = actual->getSig();
	}
	actual->setSig(nuevo);
	return true;
}

void juegos::limitarLista(int limite) {
	if (cuentaJuegos() > limite) {
		actual = primero;
		for (int i = 1; i < limite; i++) {
			actual = actual->getSig();
		}
		juego *aux = actual;
		while (actual->getSig() != NULL) {
			eliminarFinal();
			actual = aux;
		}
	}
}

bool juegos::eliminarFinal() {
	if (actual == NULL) { return false; }
	if (actual->getSig() == NULL) {
		delete primero;
		return true;
	}
	actual = primero;
	while (actual->getSig()->getSig() != NULL) {
		actual = actual->getSig();
	}
	delete actual->getSig();
	actual->setSig(NULL);
	return true;
}

juegos* juegos::lista_Juegos_Compatibles(etiquetas *listBusc) {
	if (primero != NULL) {
		juegos *listCompatibles = new juegos();
		int pActual= 0, p1 = 0, p2 = 0, p3 = 0;
		actual = primero;
		while (actual != NULL) {
			if (listBusc->porcentajeCompatibles(actual->getListEtiquetas())>0) {
				listCompatibles->insertarJuegoOrdenado(actual, listBusc);
			}
			actual = actual->getSig();
		}
		if (listCompatibles->cuentaJuegos() == 0) {
			delete listCompatibles;
			return NULL;
		}
		return listCompatibles;
	}
	return NULL;
}

int juegos::cuentaJuegos() {
	actual = primero;
	int can = 0;
	while (actual != NULL) {
		can++;
		actual = actual->getSig();
	}
	return can;
}

string juegos::toStringCompatibles(etiquetas *listBusc) {
	stringstream s;
	actual = primero;
	int i = 1;
		s << "\t\t\t----------------------LISTA DE JUEGOS RECOMENDADOS-----------------------" << endl;
	while (actual != NULL) {
		s << "\t\t\t( JUEGO # " << i << " )" << endl;
		s << actual->toStringCompatibles(listBusc) << endl;
		s << "\t\t\t-------------------------------------------------------------------------" << endl;
		actual = actual->getSig();
		i++;
	}
	return s.str();
}

string juegos::toString(){
	stringstream s;
	actual = primero;
	int i = 1;
	s << "\t\t\t----------------------LISTA DE JUEGOS REGISTRADOS------------------------" << endl;
	while (actual != NULL) {
		s << "\t\t\t( JUEGO # " << i << " )" << endl;
		s << actual->toString();
		s << "\t\t\t-------------------------------------------------------------------------" << endl;
		actual = actual->getSig();
		i++;
	}
	return s.str();
}

juego* juegos::buscarJuego(string nombre) {
	actual = primero;
	while (actual != NULL) {
		if (actual->getNombre() == nombre) {
			return actual;
		}
		actual = actual->getSig();
	}
	return NULL;
}

juegos::~juegos(){
	while (primero != NULL) {
		actual = primero;
		primero = primero->getSig();
		delete actual;
	}
}