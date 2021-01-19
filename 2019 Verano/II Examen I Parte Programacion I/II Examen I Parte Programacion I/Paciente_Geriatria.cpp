#include "Paciente_Geriatria.h"

Paciente_Geriatria::Paciente_Geriatria(string nombreAcompanante, int edad, string id, string nombre, string numero_Telefono) :TipoPaciente(edad, id, nombre, numero_Telefono) {
	this->nombre_Acompanante = nombreAcompanante;
}

string Paciente_Geriatria::toString(){
	stringstream s;
	s << "\nDatos del paciente de Geriatria\n";
	s << "Edad : " << getEdad() << "\n";
	s << "Nombre : " << getNombre() << "\n";
	s << "Numero de Telefono : " << getNumero_Telefono() << "\n";
	s << "Nombre del Acompanante : " << nombre_Acompanante<<"\n";
	return s.str();
}

Paciente_Geriatria::~Paciente_Geriatria(){}
