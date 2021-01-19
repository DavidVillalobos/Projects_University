#pragma once
#include<iostream>
#include<sstream>
using namespace std;
#include "Elemento.h" 
class Departamento : public Elemento {
private:
	string _nombre;
	// Aquí se define un atributo para manejar la colección 
	// de elementos componentes. 
	Elemento* subDepartamentos[5];
	// La colección de elementos puede ser implementada como 
	// un arreglo o lista, de manera genérica o específica. 
	int cantidad;
public: 
	Departamento(string nom = " ") {
		this->_nombre = nom;
		cantidad = 0;
	}
	virtual ~Departamento(){}
	// El método permite agregar empleados o nuevos 
	// departamentos. 
	virtual void agregar(Elemento* e){
		if (cantidad < 5) {
			subDepartamentos[cantidad++] = e;
		}
	}
	// EL gasto de planilla es la suma del gasto de 
	// cada uno de los componentes. 
	virtual double gastoPlanilla() const {
		double suma = 0;
		for (int i = 0; i < cantidad; i++){
			suma += subDepartamentos[i]->gastoPlanilla();
		}
		return suma;
	}
	virtual string toString(int pos) const{
		stringstream s;
		if (0 < cantidad) {
			for (int a = 0; a <= pos; a++){
					s << " ";
			}
			s << "* " << _nombre << " : " << gastoPlanilla() << "\n";
			for (int i = 0; i < cantidad; i++) {	
				for (int a = 0; a <= pos+2; a++) {
					s << " ";
				}
				s << subDepartamentos[i]->toString(pos + 3) << "\n";
			}
		}
		return s.str();
	}

	string getNombre() const{ return _nombre; }
};