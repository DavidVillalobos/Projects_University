#ifndef TIPOPACIENTE_H
#define TIPOPACIENTE_H
#include <iostream>
#include <sstream>
#include <string>
using std::string;
using std::cout;
using std::stringstream;
using std::cin;
class TipoPaciente{
private:
	int edad;
	string id;
	string nombre;
	string numero_Telefono;
public:
	TipoPaciente(int=0,string="indef",string = "indef",string = "indef");
	virtual int getEdad();
	virtual string getId();
	virtual string getNombre();
	virtual string getNumero_Telefono();
	virtual string toString() = 0;
	virtual ~TipoPaciente();
};
#endif
