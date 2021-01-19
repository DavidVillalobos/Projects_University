#pragma once
#include"Empresa.h"
#include"In_Out.h"
class Controlador{
private:
	Empresa* empresa;
	int modalidadContrato;
	bool modalidadPago;
public:
	Controlador();
	virtual ~Controlador();
	void iniciarPrograma();
	void menuPrincipal();
	void cargarDatos();
	void guardarDatos();
	void menuGerencia();
	void menuRecursosHumanos();
	void menuContabilidad();
	void IngresarEmpleado();
	void IngresarPuesto();
	bool IngresarContrato(Empleado*);
	void menuEmpleado();
	void menuPuesto();
	void menuPlaza();
	void menuContrato();
	void modificarEmpleado(Empleado*);
	void modificarPuesto(Puesto*);
	void modificarContrato(Contrato*);
	string modalidadContratacion();
};