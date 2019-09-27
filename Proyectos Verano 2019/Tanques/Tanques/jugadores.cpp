#include "jugadores.h"
#include<iostream>
jugadores::jugadores() { 
	primero = NULL;
	actual = NULL; 
}
void  jugadores::insertarPrimero(int puntuacion, string nombre, string modalidad) {
	primero = new jugador(puntuacion,nombre,modalidad,primero);
}
void jugadores::insertarFinal(int puntuacion, string nombre, string modalidad) {
	actual = primero;
	if (actual != NULL) {
		if (actual->getSig() != NULL) {
			while (actual->getSig() != NULL) {
				actual = actual->getSig();
			}
			actual->setSig(new jugador(puntuacion, nombre,modalidad, NULL));
		}
		else {
			actual->setSig(new jugador(puntuacion, nombre,modalidad, NULL));
		}
	}
	else {
		insertarPrimero(puntuacion, nombre,modalidad);
	}
}
bool jugadores::ordenar() {
	if (primero == NULL || primero->getSig() == NULL) { return false; }
	// si la lista esta vacia o si solo hay un elemento no puedo ordenarla
	jugador *aux = primero;
	jugador *aux2;
	int puntuacion;
	string nombre;
	string modalidad;
	while (aux->getSig() != NULL) {
		aux2 = aux->getSig();
		while (aux2 != NULL) {
			if (aux->getPuntuacion() < aux2->getPuntuacion()) {
				puntuacion = aux2->getPuntuacion();
				nombre = aux2->getNombre();
				modalidad = aux2->getModalidad();
				aux2->setPuntuacion(aux->getPuntuacion());
				aux2->setNombre(aux->getNombre());
				aux2->setModalidad(aux->getModalidad());
				aux->setPuntuacion(puntuacion);
				aux->setNombre(nombre);
				aux->setModalidad(modalidad);
			}
			aux2 = aux2->getSig();
		}
		aux = aux->getSig();
	}
	return true;
}
bool jugadores::insertarOrdenado(int puntuacion, string nombre, string modalidad) {
	if (primero == NULL) { insertarPrimero(puntuacion,nombre,modalidad); return true; }
	if (primero->getSig() == NULL) {
		if (puntuacion < primero->getPuntuacion()) {
			insertarPrimero(puntuacion,nombre,modalidad); return true;
		}
		else {
			insertarFinal(puntuacion,nombre,modalidad);
			return true;
		}
	}
	if (puntuacion < primero->getPuntuacion()) {
		insertarPrimero(puntuacion,nombre,modalidad);
		return true;
	}
	actual = primero;
	while (actual->getSig() != NULL) {
		if (puntuacion < actual->getSig()->getPuntuacion()) {
			actual->setSig(new jugador(puntuacion,nombre,modalidad,actual->getSig()));
			return true;
		}
		actual = actual->getSig();
	}
	insertarFinal(puntuacion,nombre,modalidad);
	return true;
}
int jugadores::sumaPuntuaciones(){
	actual = primero; int suma = 0;
	while (actual!=NULL) {
		suma+=actual->getPuntuacion();
		actual = actual->getSig();
	}
	return suma;
}
jugador* jugadores::buscarEspecifico(string nombre) {
	actual = primero;
	while (actual != NULL) {
		if (actual->getNombre() == nombre) {
			return actual;
		}
		actual = actual->getSig();
	}
	return NULL;
}
string jugadores::toString() {
	stringstream s;
	int i = 0;
	actual = primero;
	while (actual!=NULL) {
		i++;
		s <<i<<") "<<actual->toString();
		actual = actual->getSig();
	}
	return s.str();
}
int jugadores::cuentaNodos(){
	actual = primero;
	int can = 0;
	while (actual!=NULL) {
		can++;
		actual = actual->getSig();
	}
	return can;
}
jugadores* jugadores::mejores(int num){
	if (primero==NULL) {return NULL;}
	jugadores *aux = new jugadores();
	if (cuentaNodos() <= num) {
		actual = primero;
		while (actual != NULL) {
			aux->insertarOrdenado(actual->getPuntuacion(), actual->getNombre(), actual->getModalidad());
			actual = actual->getSig();
		}
	}
	else {
		ordenar();
		actual = primero;
		int i = 0;
		while (i!=num+1) {
			aux->insertarOrdenado(actual->getPuntuacion(), actual->getNombre(), actual->getModalidad());
			actual = actual->getSig();
			i++;
		}		
	}
	return aux;
}
jugadores* jugadores::list_Puntuaciones(string modo) {
	if (primero == NULL) { return NULL; }
	actual = primero;
	jugadores *aux = new jugadores();
	while (actual!=NULL) {
		if (actual->getModalidad()==modo) {
			aux->insertarOrdenado(actual->getPuntuacion(), actual->getNombre(), actual->getModalidad());
		}
		actual = actual->getSig();
	}
	return aux;
}
bool jugadores::eliminaInicio() {
	actual = primero;
	if (primero == NULL){
		return false;
	}
	else{
		actual = primero;
		primero = primero->getSig();
		delete actual;
		return true;
	}
}
jugadores::~jugadores() {
	while (primero!=NULL){
		eliminaInicio();
	}
}