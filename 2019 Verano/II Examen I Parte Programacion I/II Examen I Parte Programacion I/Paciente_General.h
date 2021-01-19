#ifndef PACIENTE_General_H
#define PACIENTE_General_H
#include "TipoPaciente.h"
class Paciente_General : public TipoPaciente{
private:
	string ocupacion, patrono;
	bool incapacidad;
public:
	Paciente_General(string,string,bool,int,string,string,string);
	string toString();
	~Paciente_General();
};
#endif
