#pragma once
#include<fstream>
#include<string>
using namespace std;

class ObjetoBase{
public:
	virtual string toString() = 0;
	virtual void guardar(ofstream&) = 0;
	virtual ~ObjetoBase(void) {}
	friend ostream& operator<<(ostream &salida, ObjetoBase *obj) {
		salida << obj->toString();
		return salida;
	}
};

