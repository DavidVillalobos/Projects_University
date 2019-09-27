#include "TipoPaciente.h"
TipoPaciente::TipoPaciente(int edad, string id, string nombre, string numero_Telefono):edad(edad),id(id),nombre(nombre),numero_Telefono(numero_Telefono){}
int TipoPaciente::getEdad(){return edad; }
string TipoPaciente::getId(){ return id; }
string TipoPaciente::getNombre(){ return nombre; }
string TipoPaciente::getNumero_Telefono() { return numero_Telefono;  }
TipoPaciente::~TipoPaciente(){}
