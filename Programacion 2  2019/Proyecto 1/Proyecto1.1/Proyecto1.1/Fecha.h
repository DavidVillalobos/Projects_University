#pragma once
#include<iostream>
#include<sstream>
using namespace std;
class Fecha{
private:
	int dia, mes, anno;
public:
	Fecha();
	Fecha(int,int,int);
	virtual ~Fecha();
	int getDia();
	int getMes();
	int getAnno();
	void setDia(int);
	void setMes(int);
	void setAnno(int);
	string toString();
	Fecha operator-(Fecha&);
	Fecha horaLocal();
	friend ostream& operator<<(ostream&, Fecha*);
	string guardar();
};

