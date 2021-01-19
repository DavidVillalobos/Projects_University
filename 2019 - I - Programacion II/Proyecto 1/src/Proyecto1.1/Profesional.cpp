#include "Profesional.h"

Profesional::Profesional(Empleado *empleado, Puesto *puesto):Contrato(empleado){
	this->puesto = puesto;
}

Puesto* Profesional::getPuesto(){ return puesto; }

string Profesional::toString(){
	stringstream s;
	s << "Contrato\n ";
	s << "\tFecha de ingreso: " << fechaIngreso() << endl;
	s << "\tFecha de cesantia: " << fechaCesantia() << endl;
	s << "\tSalario Bruto: " << getSalarioBruto() << endl;
	s << "\tSalario Neto: " << getSalarioNeto() << endl;
	s << "\tAdicionales: " << getAdicionales() << endl;
	s << "Empleado\n" << getEmpleado() << endl;
	if (puesto) {
		s << "Puesto\n" << puesto << endl;
	}
	return s.str();
}

string Profesional::informe(){
	stringstream s;
	s << getEmpleado()->getId() << '\t';
	s << getEmpleado()->getNombreCompleto() << '\t';
	s << getPuesto()->getCodigo() << '\t';
	s << getSalarioNeto();
	return s.str();
}

void Profesional::guardar(ofstream &salida){
	salida << "1\t" << getEmpleado()->getId()<<"\t";
	salida << puesto->getCodigo() << "\t" << getAdicionales() << "\t";
	salida << getDiaIngreso() << "/" << getMesIngreso() << "/" << getAnnoIngreso() << "\t";
	if (getAnnoCesantia() == -1) { //Si aun cesantia no existe
		salida << "00/00/0000\n"; // fecha sin inicializar
	}
	else {
		salida << getDiaCesantia() << "/" << getMesCesantia() << "/" << getAnnoCesantia()<<endl;
	}
}

void Profesional::cesantiaContrato() {}

Profesional::~Profesional(){}
