#pragma once
#include"ObjetoBase.h"
#include<sstream>
using namespace std;
class Puesto : public ObjetoBase {
private:
	string codigo;
	string descripcion;
	int salarioBase;
public:
	Puesto(string = "indef", string = "indef", int = 0);
	virtual ~Puesto();
	string getCodigo();
	string getDescripcion();
	int getSalarioBase();
	void setCodigo(string);
	void setDescripcion(string);
	void setSalarioBase(int);
	void guardar(ofstream&);
	string toString();
	friend ostream& operator<<(ostream&, Puesto*);
};

