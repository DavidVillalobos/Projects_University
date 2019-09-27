#ifndef TIQUETE_H
#define TIQUETE_H
#include <string>
#include <sstream>
using std::string;
using std::stringstream;
#include "in_out.h"
class Tiquete {
private:
	string nombre;
	string asiento;
	string dia;
	string hora;
	int precio;
	int precioImpresion;
	bool tipo;
	string horaDeCompra;
	int impuestoVentas;
public:
	Tiquete(string,string,string,string,int,int,bool,string);
	~Tiquete();
	string getNombre();
	string getAsiento();
	string getDia();
	string getHora();
	int getPrecio();
	int getPrecioImpresion();
	string getHoraDeCompra();
	bool getTipo();
	int getImpuestodeVentas();
	void setPrecio(int);
	void setPrecioImpresion(int);
	string toString();
};
#endif // !TIQUETE