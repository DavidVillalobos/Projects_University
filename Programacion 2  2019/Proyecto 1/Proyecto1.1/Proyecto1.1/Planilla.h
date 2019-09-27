#pragma once
#include"Contrato.h"
class Planilla: public Contrato{
private:
	int ahorroEscolar;  //Beneficios
	int ahorroNavideno; // De ahorro
public:
	Planilla(Empleado * empleado, int,int);
	virtual Puesto* getPuesto() = 0;
	virtual string toString() = 0;
	virtual void guardar(ofstream&) = 0;
	virtual string informe() = 0;
	virtual void cesantiaContrato() = 0;
	int getAhorroEscolar();
	int getAhorroNavideno();
	void setAhorroEscolar(int);
	void setAhorroNavideno(int);
	virtual ~Planilla();
};