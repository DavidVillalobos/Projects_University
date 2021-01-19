#include "Paciente_Pediatria.h"

Paciente_Pediatria::Paciente_Pediatria(string nombreEncargado, string ApellidosEncargado, string numero_TelefonoEncargado, int edad, string id, string nombre, string numero_Telefono) :TipoPaciente(edad,id,nombre,numero_Telefono){
	this->nombreEncargado = nombreEncargado; 
	this->ApellidosEncargado = ApellidosEncargado;
	this->numero_TelefonoEncargado = numero_TelefonoEncargado;
}

string Paciente_Pediatria::toString(){
	stringstream s;
	s << "\nDatos del paciente de Pediatria\n";
	s << "Edad : " << getEdad()<<"\n";
	s << "Nombre : " << getNombre()<<"\n";
	s << "Numero de Telefono : " << getNumero_Telefono()<<"\n";
	s << "Nombre del Encargado : " << nombreEncargado<<"\n";
	s << "Apellidos del Encargado : " << ApellidosEncargado<<"\n";
	s << "Numero de Telefono del Encargado : " << numero_TelefonoEncargado<<"\n";
	return s.str();
}

Paciente_Pediatria::~Paciente_Pediatria(){}
