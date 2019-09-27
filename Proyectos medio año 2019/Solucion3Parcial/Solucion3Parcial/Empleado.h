#pragma once
#include<fstream>
#include "Elemento.h"
#include"Departamento.h"
#include"Categoria.h"
class Empleado : public Elemento {
private:
	string _cedula;
	string _nombre;
	Departamento* _departamento;
	int _categoria;
public:
	Empleado(string cedula, string nombre, Departamento* depto, int categoria) :_cedula(cedula), _nombre(nombre), _departamento(depto), _categoria(categoria) {
	}
	// Para el empleado, el gasto de planilla es equivalente 
	// al monto de su salario. 
	virtual double gastoPlanilla() const { 
		return obtenerSalario();
	}
	// El salario del empleado se calcula a partir del 
	// monto base definido para la categoría correspondiente.
	virtual double obtenerSalario() const { 
		Categoria cate(_categoria);
		return cate.getSalarioBase();
	}
	virtual string toString(int i) const { 
		stringstream s;
		for (int a = 0; a < i; a++){
			s << " ";
		}
		s << "-> " << _nombre << " : " << gastoPlanilla();
		return s.str();
	}
	int obtenerCategoria() const { return _categoria; }
	string obtenerCedula() const { return _cedula; }
	Departamento* obtenerDepartamento() { return _departamento; }
	string obtenerNombre() const { return _nombre; }
};