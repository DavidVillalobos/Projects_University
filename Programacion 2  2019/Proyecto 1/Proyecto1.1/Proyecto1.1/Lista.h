#pragma once
#include"Nodo.h"
class Lista: public ObjetoBase{
private:
	Nodo *primero;
	int k;
public:
	Lista();
	ObjetoBase *getElemento(int);
	void insertarInicio(ObjetoBase*);
	int getK();
	string toString();
	void guardar(ofstream&);
	bool eliminar(int);
	virtual ~Lista();
};

