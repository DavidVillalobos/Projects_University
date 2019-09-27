#include "Arbol.h"

Arbol::Arbol(Posicion *pos, Estrategia* e){ 
	wchar_t f = pos->getSimbolo();
	raiz = new Nodo(pos, L"", f, e);
	raiz->setValor(0);
}

wstring Arbol::toString(){
	if (raiz) {
		return raiz->toString();
	}
	return L"";
}

Nodo * Arbol::getMayor(){
	return raiz->getMayor();
}

Nodo* Arbol::getRaiz() {
	return raiz;
}

Nodo * Arbol::buscarNodo(Posicion *pos){
	return raiz->buscarNodo(pos);
}

Arbol::~Arbol() { delete raiz; }
