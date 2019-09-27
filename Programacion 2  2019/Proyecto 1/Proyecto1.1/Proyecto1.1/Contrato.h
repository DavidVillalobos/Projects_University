#pragma once
#include"ObjetoBase.h"
#include"Fecha.h"
#include"Puesto.h"
#include"Empleado.h"
class Contrato : public ObjetoBase {
private:
	Empleado* empleado;
	Fecha* ingreso;
	Fecha* cesantia;
	float salarioBruto;//Salario base + adicionales
	float salarioNeto;//Este se calcula con el salario base - deducciones
	int adicionales;
public:
	Contrato(Empleado*);
	virtual ~Contrato();
	virtual Empleado* getEmpleado();
	virtual Puesto* getPuesto() = 0;
	virtual string informe() = 0;
	virtual void cesantiaContrato() = 0;
	void cesarContrato();
	int getDiaIngreso();
	int getMesIngreso();
	int getAnnoIngreso();
	int getDiaCesantia();
	int getMesCesantia();
	int getAnnoCesantia();
	float getSalarioBruto();
	float getSalarioNeto();
	int getAdicionales();
	void setDiaIngreso(int);
	void setMesIngreso(int);
	void setAnnoIngreso(int);
	void setSalarioBruto(float);
	void setSalarioNeto(float);
	bool setDiaCesantia(int);
	bool setMesCesantia(int);
	bool setAnnoCesantia(int);
	void setAdicionales(int);
	virtual void guardar(ofstream&) = 0;
	void Tdif_Tactual(int&, int&, int&);
	string fechaIngreso();
	string fechaCesantia();
	virtual string toString() = 0;
	friend ostream& operator<<(ostream&, Contrato*);
};