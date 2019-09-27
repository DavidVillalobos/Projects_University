#include "Lista.h"
#include<sstream>
Lista::Lista() {
	primero = NULL;
	k = 0;
}

ObjetoBase * Lista::getElemento(int pos){
	if (!primero) { return NULL; }
	ObjetoBase *r = NULL;
	if (pos < k) {
		Nodo* actual = primero;
		int i = 0;
		while (actual) {
			if (i == pos) {
				r = actual->getInfo();
				break;
			}
			actual = actual->getSig();
			i++;
		}
	}
	return r;
}

void Lista::insertarInicio(ObjetoBase *info) {
	primero = new Nodo(info, primero);
	k++;
}

int Lista::getK(){
	return k;
}

string Lista::toString(){
	stringstream s;
	Nodo* actual = primero;
	int i = 1;
	while (actual) {
		s << "[ "<<i<<" ] - - - - - - - - - - - - - - - - - - - \n";
		s << actual->getInfo();
		s << endl;
		actual = actual->getSig();
		i++;
	}
	return s.str();
}

void Lista::guardar(ofstream &entrada){
	Nodo* actual = primero;
	while (actual) {
		actual->getInfo()->guardar(entrada);
		actual = actual->getSig();
	}
}

bool Lista::eliminar(int pos){
	if (!primero) { return false; }
	if (pos < k) {
		Nodo* actual = primero;
		if (pos == 0) {
			primero = primero->getSig();
			delete actual;
			k--;
			return true;
		}
		int i = 1;
		while (actual->getSig()) {
			if (i == pos) {
				Nodo *tmp = actual->getSig();
				actual->setSig(actual->getSig()->getSig());
				delete tmp;
				k--;
				return true;
			}
			actual = actual->getSig();
			i++;
		}
	}
	return false;
}

Lista::~Lista() {
	Nodo *actual = primero;
	while (actual) {
		primero = actual->getSig();
		delete actual;
		actual = primero;
	}
}

