#pragma once
#include"Planilla.h"
class PlanillaCorta: public Planilla{
private:
	Puesto* puesto;
public:
	PlanillaCorta(Empleado*, Puesto*, int, int);
	Puesto* getPuesto();
	string toString();
	string informe();
	void cesantiaContrato();
	virtual void guardar(ofstream&);
	virtual ~PlanillaCorta();
};

