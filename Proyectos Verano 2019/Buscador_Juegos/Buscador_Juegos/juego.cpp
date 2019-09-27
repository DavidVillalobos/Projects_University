#include "juego.h"
juego::juego(string nombre, string disponibilidad, etiquetas *listEtiquetas, string descripcion, juego *sig) {
	this->nombre = nombre;
	this->disponibilidad = disponibilidad;
	this->listEtiquetas = listEtiquetas;
	this->descripcion = descripcion;
	this->sig = sig;
}
string juego::getNombre() { return nombre; }
etiquetas* juego::getListEtiquetas() { return listEtiquetas; }
string juego::getDescripcion() { return descripcion; }
string juego::getDisponibilidad() { return disponibilidad; }
void juego::setSig(juego *sig) { this->sig = sig; }
juego* juego::getSig() { return sig; }
string juego::toStringCompatibles(etiquetas *listBusc) {
	stringstream s;
	s << "\t\t\tEl Juego --> | " << nombre << " | "<<endl;
	s << "\t\t\tCon las etiquetas " << listEtiquetas->toString()<<endl;
	s << "\t\t\tfue encontrado con un " << listEtiquetas->porcentajeCompatibles(listBusc) << "% de compatibilidad" << endl;
	s << "\t\t\tSe encuentra disponible para " << disponibilidad << endl;
	s << "\t\t\tDescripcion del Juego: " << endl;
	s << "\t\t\t"+descripcion << endl;
	return s.str();
}
string juego::toString(){
	stringstream s;
	s << "\t\t\tEl Juego --> | " << nombre << " | " << endl;
	s << "\t\t\tCon las etiquetas " << listEtiquetas->toString() << endl;
	s << "\t\t\tSe encuentra disponible para " << disponibilidad << endl;
	s << "\t\t\tDescripcion del Juego: ";
	s <<"\t\t\t"+descripcion << endl;
	return s.str();
}
juego::~juego() {}