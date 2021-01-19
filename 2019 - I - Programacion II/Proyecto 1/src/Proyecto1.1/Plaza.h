#pragma once
#include"Puesto.h"
class Plaza: public ObjetoBase{
private:
	Puesto* puesto;
	bool vacante;
public:
	Plaza(Puesto*,bool);
	virtual ~Plaza();
	Puesto* getPuesto();
	bool getVacante();
	string toString();
	friend ostream& operator<<(ostream&, Plaza*);
	void setVacante(bool);
	virtual void guardar(ofstream&);
};

