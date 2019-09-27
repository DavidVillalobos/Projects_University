#include "Puesto.h"

Puesto::Puesto(string codigo, string descripcion, int salarioBase):codigo(codigo),descripcion(descripcion),salarioBase(salarioBase){
}

Puesto::~Puesto() {}

string Puesto::toString(){
	stringstream s;
	s << "\tCodigo: " << codigo << endl;
	s << "\tDecripcion: " << descripcion<<endl;
	s << "\tSalario Base: " << salarioBase<<endl;
	return s.str();
}

string Puesto::getCodigo(){ return codigo; }

string Puesto::getDescripcion(){ return descripcion; }

int Puesto::getSalarioBase(){ return salarioBase; }

ostream & operator<<(ostream &salida, Puesto *p){
	salida << p->toString();
	return salida;
}

void Puesto::setCodigo(string codigo) { this->codigo = codigo; }

void Puesto::setDescripcion(string descripcion) { this->descripcion = descripcion; }

void Puesto::setSalarioBase(int salarioBase) { this->salarioBase = salarioBase; }

void Puesto::guardar(ofstream &entrada){
	entrada << codigo << "\t";
	entrada << descripcion << "\t";
	entrada << salarioBase << "\n";
}
