#include "PlanillaCorta.h"

PlanillaCorta::PlanillaCorta(Empleado *empleado, Puesto *puesto, int ahorroNavideno, int ahorroEscolar): Planilla(empleado, ahorroNavideno, ahorroEscolar) {
	this->puesto = puesto;
}

Puesto * PlanillaCorta::getPuesto(){return puesto; }

string PlanillaCorta::toString(){
	stringstream s;
	s << "Contrato\n ";
	s << "\tFecha de ingreso: " << fechaIngreso() << endl;
	s << "\tFecha de cesantia: " << fechaCesantia() << endl;
	s << "\tSalario Bruto:" << getSalarioBruto() << endl;
	s << "\tSalario Neto:" << getSalarioNeto() << endl;
	if (getAhorroNavideno() != 0) {
		s << "\tAhorro Navide\244o: " << getAhorroNavideno() << "%" << endl;
	}
	if (getAhorroEscolar() != 0) {
		s << "\tAhorro Escolar: " << getAhorroEscolar() << "%" << endl;
	}
	s << "Empleado\n" << getEmpleado() << endl;
	s << "Puesto\n " << endl;
	if (getPuesto()) {
		s << getPuesto() << endl;
	}
	return s.str();
}

string PlanillaCorta::informe(){
	stringstream s;
	s << getEmpleado()->getId() << '\t';
	s << getEmpleado()->getNombreCompleto() << '\t';
	s << getPuesto()->getCodigo() << '\t';
	s << getSalarioNeto();
	return s.str();
}

void PlanillaCorta::cesantiaContrato(){}

void PlanillaCorta::guardar(ofstream &salida){
	salida << "2\t" << getEmpleado()->getId() << "\t" << puesto->getCodigo() << "\t";
	salida << getAdicionales() << "\t" << getAhorroEscolar() << "\t" << getAhorroNavideno() <<"\t";
	salida << getDiaIngreso() << "/" << getMesIngreso() << "/" << getAnnoIngreso() << "\t";
	if (getAnnoCesantia() == -1) { //Si aun cesantia no existe
		salida << "00/00/0000\n"; // fecha sin inicializar
	}
	else {
		salida << getDiaCesantia() << "/" << getMesCesantia() << "/" << getAnnoCesantia() << endl;
	}
}

PlanillaCorta::~PlanillaCorta(){}
