#include "PlanillaIdefinida.h"

PlanillaIdefinida::PlanillaIdefinida(Empleado *empleado, Plaza *plaza,int ahorroNavideno, int ahorroEscolar) : Planilla(empleado, ahorroNavideno, ahorroEscolar) {
	this->plaza = plaza;
}

Puesto * PlanillaIdefinida::getPuesto(){
	return plaza->getPuesto();
}

Plaza * PlanillaIdefinida::getPlaza() {
	return plaza;
}

string PlanillaIdefinida::toString(){
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

string PlanillaIdefinida::informe(){
	stringstream s;
	s << getEmpleado()->getId() << '\t';
	s << getEmpleado()->getNombreCompleto() << '\t';
	s << getPuesto()->getCodigo() << '\t';
	s << getSalarioNeto();
	return s.str();
}

void PlanillaIdefinida::cesantiaContrato(){
	getPlaza()->setVacante(true); //La vacante esta disponible de nuevo
}

void PlanillaIdefinida::guardar(ofstream &salida){
	salida << "3\t" << getEmpleado()->getId() << "\t" << plaza->getPuesto()->getCodigo() << "\t";
	salida << getAdicionales() << "\t" << getAhorroEscolar() << "\t" << getAhorroNavideno() << "\t";
	(plaza->getVacante() == false) ? salida << "NO": salida << "SI";
	salida << getDiaIngreso() << "/" << getMesIngreso() << "/" << getAnnoIngreso() << "\t";
	if (getAnnoCesantia() == -1) { //Si aun cesantia no existe
		salida << "00/00/0000\n"; // fecha sin inicializar
	}
	else {
		salida << getDiaCesantia() << "/" << getMesCesantia() << "/" << getAnnoCesantia() << endl;
	}
}

PlanillaIdefinida::~PlanillaIdefinida(){}
