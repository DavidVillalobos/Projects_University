#include "Empleado.h"

Empleado::Empleado(string id, string nombre, string apellido1, string apellido2, int diaNac, int mesNac,int annoNac, string direccion, int numeroTelefono){
	this->id = id;
	this->nombre = nombre;
	this->apellido1 = apellido1;
	this->apellido2 = apellido2;
	this->nacimiento = new Fecha(diaNac,mesNac,annoNac);
	this->direccion = direccion;
	this->numeroTelefono = numeroTelefono;
}

Empleado::~Empleado() {}

string Empleado::getId(){ return id; }

string Empleado::getnombre(){ return nombre; }

string Empleado::getApellido1(){ return apellido1; }

string Empleado::getApellido2(){ return apellido2; }

string Empleado::getDireccion(){ return direccion; }

string Empleado::getFechaNacimiento(){ return nacimiento->toString(); }

string Empleado::getNombreCompleto(){
	return nombre + " " + apellido1 + " " + apellido2;
}

int Empleado::getNumeroTelefono(){ return numeroTelefono; }

int Empleado::getDiaNac(){ return nacimiento->getDia(); }

int Empleado::getMesNac() { return nacimiento->getMes(); }

int Empleado::getAnnoNac() { return nacimiento->getAnno(); }

void Empleado::setNombre(string nombre){ this->nombre = nombre; }

void Empleado::setApellido1(string apellido1){ this->apellido1 = apellido1; }

void Empleado::setApellido2(string apellido2){ this->apellido2 = apellido2; }

void Empleado::setDireccion(string direccion){ this->direccion = direccion; }

void Empleado::setNumeroTelefono(int numeroTelefono){ this->numeroTelefono = numeroTelefono; }

void Empleado::setDiaNac(int diaNac){ nacimiento->setDia(diaNac); }

void Empleado::setMesNac(int mesNac){ nacimiento->setMes(mesNac); }

void Empleado::setAnnoNac(int annoNac){ nacimiento->setAnno(annoNac); }

void Empleado::guardar(ofstream &entrada){
	entrada << id << "\t";
	entrada << nombre << "\t";
	entrada << apellido1 << "\t";
	entrada << apellido2 << "\t";
	entrada << nacimiento->guardar() << "\t";
	entrada << direccion << "\t";
	entrada << numeroTelefono << endl;
}

string Empleado::toString(){
	stringstream s;
	s << "\tCedula: " << id << endl;
	s << "\tNombre: " << getNombreCompleto()<<endl;
	s << "\tFecha de nacimiento: "<<nacimiento<<endl;
	s << "\tDireccion: "<<direccion<<endl;
	s << "\tNumero de Telefono: " << numeroTelefono<<endl;
	return s.str();
}

ostream & operator<<(ostream &salida, Empleado *e){
	salida << e->toString();
	return salida;
}