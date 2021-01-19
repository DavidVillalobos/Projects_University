#pragma once
#include"ObjetoBase.h"
class Nodo {
private:
	ObjetoBase* info;
	Nodo* sig;
public:
	Nodo(ObjetoBase*, Nodo*);
	ObjetoBase* getInfo();
	Nodo* getSig();
	void setInfo(ObjetoBase*);
	void setSig(Nodo*);
	virtual ~Nodo();
};