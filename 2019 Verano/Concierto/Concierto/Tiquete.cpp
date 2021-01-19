#include "Tiquete.h"

Tiquete::Tiquete(string nombre, string asiento, string dia, string hora, int precio, int precioImpresion, bool tipo, string horaDeCompra) {
	this->nombre=nombre;
	this->asiento=asiento;
	this->dia=dia;
	this->hora=hora;
	this->precio = precio;
	this->precioImpresion = precioImpresion;
	this->tipo = tipo;
	this->horaDeCompra = horaDeCompra;
	impuestoVentas = 13;
}

Tiquete::~Tiquete(){}

string Tiquete::getNombre(){ return nombre; }

string Tiquete::getAsiento(){ return asiento; }

string Tiquete::getDia(){ return dia; }

string Tiquete::getHora(){ return hora; }

int Tiquete::getPrecio(){ return precio; }

int Tiquete::getPrecioImpresion(){ return precioImpresion; }

string Tiquete::getHoraDeCompra() {return horaDeCompra; }

bool Tiquete::getTipo(){ return tipo; }

int Tiquete::getImpuestodeVentas(){ return impuestoVentas; }

void Tiquete::setPrecio(int precio) { this->precio = precio; }

void Tiquete::setPrecioImpresion(int precioImpresion) {this->precioImpresion = precioImpresion;}

string Tiquete::toString(){
	stringstream s;
	s << "----------------------------------------\n";
	s << "   "<<dia<<"  CONCIERTO NAVIDE\245O\n";
	s << "       "<<hora<<"\n";
	s << "  Hora de Compra"<<horaDeCompra<< "   Entrada: "; (tipo) ? s << "VIP\n" : s << "General\n";
	s << "  Asiento: " << asiento << "    "; s << "  Precio: " << precio;
	s << "\n  Impuesto de Ventas: " << impuestoVentas << "%\n   Costo de impresion: "<<precioImpresion<<"\n";
	s << "  Propietario: "<<nombre<<"\n";
	s << "----------------------------------------\n";
	setColor(15);
	return s.str();
}


