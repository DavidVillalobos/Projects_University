#pragma once
#include"ObjetoBase.h"
#include"Fecha.h"
class Empleado : public ObjetoBase{
	string id;
	string nombre;
	string apellido1;
	string apellido2;
	Fecha* nacimiento;
	string direccion;
	int numeroTelefono;
public:
	Empleado(string,string,string,string,int,int,int,string,int);
	virtual ~Empleado();
	string getId();
	string getnombre();
	string getApellido1();
	string getApellido2();
	string getDireccion();
	string getFechaNacimiento();
	string getNombreCompleto();
	int getNumeroTelefono();
	int getDiaNac();
	int getMesNac();
	int getAnnoNac();
	void setNombre(string);
	void setApellido1(string);
	void setApellido2(string);
	void setDireccion(string);
	void setNumeroTelefono(int);
	void setDiaNac(int);
	void setMesNac(int);
	void setAnnoNac(int);
	void guardar(ofstream&);
	string toString();
	friend ostream& operator<<(ostream&, Empleado*);
};

