#pragma once
#include"Lista.h"
#include"Contrato.h"
#include"Plaza.h"
#include"PlanillaCorta.h"
#include"PlanillaIdefinida.h"
#include"Profesional.h"
class Empresa{
private:
	Lista *listC, *listE, *listP, *listPl;
	string nombre, direccion;
	int numeroTelefono;
	int cargasSociales, ahorroObligatorio, impuestoSobreLaRenta;//Porcentajes
public:
	Empresa(string,string,int);
	virtual ~Empresa();
	int getCargasSociales();
	int getAhorroObligatorio();
	int getImpuestoSobreLaRenta();
	virtual Contrato* getContrato(string);
	Contrato * getContrato(int);
	virtual Empleado* getEmpleado(string);
	virtual Puesto* getPuesto(string);
	virtual Plaza* getPlaza(string);
	Lista* getContrato_Puesto(string);
	virtual string getNombre();
	virtual string getdireccion();
	virtual int getNumeroTelefono();
	virtual void setDireccion(string);
	virtual void setNumeroTelefono(int);
	void ingresarEmpleado(Empleado*);
	bool eliminarPuesto(string);
	Lista* getListE();
	Lista* getListC();
	Lista* getListP();
	Lista * getListPl();
	void ingresarContrato(Contrato*);
	void ingresarPuesto(Puesto*);
	void ingresarPlaza(Plaza*);
	float CalcularSalarioNeto(Contrato*);
	float CalcularSalarioBruto(Contrato*);
	int CalcularVacaciones(Contrato*);
	float CalcularLiquidacion(Contrato*);
	float despedir(Contrato*);
	Planilla* getContratoPlanilla(Contrato*);
	Profesional * getContratoProfesional(Contrato *);
	float calcularAguinaldo(Contrato*);
};