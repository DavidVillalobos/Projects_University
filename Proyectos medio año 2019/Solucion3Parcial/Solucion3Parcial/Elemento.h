#pragma once
#include <exception>
#include <string> 
using namespace std;
class Elemento { 
	public:
	virtual ~Elemento(){}
	// gastoPlanilla() es un método que calcula la suma 
	// de los gastos de todos los componentes (empleados
	// y departamentos). 
	virtual double gastoPlanilla() const = 0;
	virtual string toString(int i) const = 0; 
}; 