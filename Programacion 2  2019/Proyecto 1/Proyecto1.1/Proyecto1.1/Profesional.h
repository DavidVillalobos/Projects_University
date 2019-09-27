#pragma once
#include"Contrato.h"
class Profesional: public Contrato{
private:
	Puesto *puesto;
public:
	Profesional(Empleado*, Puesto*);
	Puesto* getPuesto();
	string toString();
	string informe();
	void guardar(ofstream&);
	void cesantiaContrato();
	virtual ~Profesional();
};

