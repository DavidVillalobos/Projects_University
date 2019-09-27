#pragma once
#include"Planilla.h"
#include"Plaza.h"
class PlanillaIdefinida: public Planilla{
private:
	Plaza *plaza;
public:
	PlanillaIdefinida(Empleado*,Plaza*, int, int);
	Puesto* getPuesto();
	Plaza * getPlaza();
	string toString();
	string informe();
	void cesantiaContrato();
	virtual void guardar(ofstream&);
	virtual ~PlanillaIdefinida();
};

