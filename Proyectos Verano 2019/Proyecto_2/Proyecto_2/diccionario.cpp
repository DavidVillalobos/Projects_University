#include "diccionario.h"

diccionario::diccionario() { lista = new listaDiccionario(); }

listaDiccionario* diccionario::getLista() { return lista; }

bool diccionario::buscarPalabra(string palabra) {
	ifstream f;
	f.open("../prueba.txt");
	while (f.good()) {
		string bloque, letra, word; bool bandera = true;
		getline(f, bloque, '*'); //lee hasta *
		getline(f, letra, '/');// lee la letra(A) hasta /
		if (palabra[0] == letra[0]) { // si la letra que esta entre / * es la primera de la palabra que busco 
			while (bandera == true) {
				getline(f, word, '/');
				if (word == palabra) {
					f.close();
					lista->insertarInicio(palabra);
					return true;
				}
				if ((word[0] == '#')) {
					bandera = false;
				}
			}
			getline(f, bloque);
		}
	}
	f.close();
	return false;
}

diccionario::~diccionario() { delete lista; }