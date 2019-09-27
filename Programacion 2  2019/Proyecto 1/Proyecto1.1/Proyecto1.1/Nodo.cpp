#include "Nodo.h"

Nodo::Nodo(ObjetoBase *info, Nodo *sig){
	this->info = info;
	this->sig = sig;
}

ObjetoBase * Nodo::getInfo(){
	return info;
}

Nodo * Nodo::getSig(){
	return sig;
}

void Nodo::setInfo(ObjetoBase *info){
	this->info = info;
}

void Nodo::setSig(Nodo *sig){
	this->sig = sig;
}

Nodo::~Nodo(){
	delete info;
}
