#include "Planilla.h"

Planilla::Planilla(Empleado *empleado, int ahorroNavideno, int ahorroEscolar) :Contrato(empleado) {
	this->ahorroEscolar = ahorroEscolar;
	this->ahorroNavideno = ahorroNavideno;
}

int Planilla::getAhorroEscolar(){ return ahorroEscolar; }

int Planilla::getAhorroNavideno(){ return ahorroNavideno; }

void Planilla::setAhorroEscolar(int v){
	ahorroEscolar = v;
}

void Planilla::setAhorroNavideno(int v){
	ahorroNavideno = v;
}

Planilla::~Planilla(){}
