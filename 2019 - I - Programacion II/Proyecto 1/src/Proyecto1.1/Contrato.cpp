#include "Contrato.h"

Contrato::Contrato(Empleado* empleado){
	this->empleado = empleado;
	this->ingreso = new Fecha(); //Sin parametro, pone el dia de hoy
	this->cesantia = NULL; //La Fecha de Cesantia aun no se especifica
	salarioBruto = 0; // Aun no se especifica
	salarioNeto = 0; // Aun no se especifica
}

Contrato::~Contrato() {
	delete ingreso;
	ingreso = NULL;
	if (cesantia != NULL) {
		delete cesantia;
		cesantia = NULL;
	}
}

Empleado * Contrato::getEmpleado(){ return empleado; }

void Contrato::cesarContrato(){
	cesantia = new Fecha;
}

int Contrato::getDiaIngreso(){ return ingreso->getDia(); }

int Contrato::getMesIngreso() { return ingreso->getMes(); }

int Contrato::getAnnoIngreso() { return ingreso->getAnno(); }

float Contrato::getSalarioBruto() { return salarioBruto; }

float Contrato::getSalarioNeto(){ return salarioNeto; }

int Contrato::getAdicionales(){ return adicionales; }

int Contrato::getDiaCesantia() {
	if (cesantia) {
		return cesantia->getDia();
	}
	return -1;
}

int Contrato::getMesCesantia() {
	if (cesantia) {
		return cesantia->getMes();
	}
	return -1;
}

int Contrato::getAnnoCesantia() {
	if (cesantia) {
		return cesantia->getAnno();
	}
	return -1;
}

void Contrato::setDiaIngreso(int diaIngreso){ ingreso->setDia(diaIngreso); }

void Contrato::setMesIngreso(int mesIngreso) { ingreso->setMes(mesIngreso); }

void Contrato::setAnnoIngreso(int annoIngreso) { ingreso->setAnno(annoIngreso); }

void Contrato::setSalarioBruto(float salarioBruto) { this->salarioBruto = salarioBruto; }

void Contrato::setSalarioNeto(float salarioNeto) { this->salarioNeto = salarioNeto; }

bool Contrato::setDiaCesantia(int diaCesantia) {
	if (cesantia){
		this->cesantia->setDia(diaCesantia);
		return true;
	}
	return false;
}

bool Contrato::setMesCesantia(int mesCesantia){
	if (cesantia) {
		this->cesantia->setMes(mesCesantia);
		return true;
	}
	return false;
}

bool Contrato::setAnnoCesantia(int annoCesantia){
	if (cesantia) {
		this->cesantia->setAnno(annoCesantia);
		return true;
	}
	return false;
}

void Contrato::setAdicionales(int adicionales){
	this->adicionales = adicionales;
}

void Contrato::Tdif_Tactual(int &dia, int &mes, int &anno){
	Fecha actual; //Se crea con la hora local
	Fecha f = *ingreso - actual; //Guardamos la diferencia de tiempo en f
	dia = f.getDia();
	mes = f.getMes();
	anno = f.getAnno();
	//Damos los valores y los enviamos por parametros de salida
}

string Contrato::fechaIngreso(){ return ingreso->toString(); }

string Contrato::fechaCesantia(){
	if (cesantia) {
		return cesantia->toString();
	}
	return "SIN DEFINIR";
}

ostream & operator<<(ostream &salida, Contrato *c){
	salida << c->toString();
	return salida;
}
