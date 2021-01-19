#ifndef PACIENTE_Geriatria_H
#define PACIENTE_Geriatria_H
#include "TipoPaciente.h"
class Paciente_Geriatria : public TipoPaciente {
private:
	string nombre_Acompanante;
public:
	Paciente_Geriatria(string,int,string,string,string);
	string toString();
	~Paciente_Geriatria();
};

#endif