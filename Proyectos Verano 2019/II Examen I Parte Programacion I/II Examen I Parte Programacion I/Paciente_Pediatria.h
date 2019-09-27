#ifndef PACIENTE_Pediatria_H
#define PACIENTE_Pediatria_H
#include "TipoPaciente.h"
class Paciente_Pediatria: public TipoPaciente{
private:
	string nombreEncargado,ApellidosEncargado, numero_TelefonoEncargado;
public:
	Paciente_Pediatria(string,string,string, int, string, string, string);
	string toString();
	~Paciente_Pediatria();
};
#endif