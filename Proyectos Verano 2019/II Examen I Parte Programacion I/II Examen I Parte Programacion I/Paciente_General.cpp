#include "Paciente_General.h"

Paciente_General::Paciente_General(string ocupacion, string patrono, bool incapacidad,int edad, string id, string nombre, string numero_Telefono) :TipoPaciente(edad, id, nombre, numero_Telefono){
	this->ocupacion = ocupacion;
	this->patrono = patrono;
	this->incapacidad = incapacidad;
}

string Paciente_General::toString(){
	stringstream s;
	s << "\nDatos del paciente de Medicina General\n";
	s << "Edad : " << getEdad() << "\n";
	s << "Nombre : " << getNombre() << "\n";
	s << "Numero de Telefono : " << getNumero_Telefono() << "\n";
	s << "Ocupacion : " << ocupacion << "\n";
	s << "Patrono : " << patrono<< "\n";
	s << "El paciente";(incapacidad) ? s<<" si ": s << " no ";
	s << "presenta incapacidad laboral\n";
	return s.str();
}



Paciente_General::~Paciente_General(){}
