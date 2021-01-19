#include "Plaza.h"

Plaza::Plaza(Puesto* puesto, bool vacante){
	this->puesto = puesto;
	this->vacante = vacante;
}

Puesto* Plaza::getPuesto(){
	return puesto;
}

bool Plaza::getVacante(){
	return vacante;
}

string Plaza::toString(){
	stringstream s;
	s<<"Vacante: ";
	(vacante)? s << "SI" : s << "NO" ;
	if (puesto) {
		s << puesto<<endl;
	}
	return s.str();
}

Plaza::~Plaza(){}

void Plaza::setVacante(bool vacante) {
	this->vacante = vacante;
}

void Plaza::guardar(ofstream &entrada){
	entrada << puesto->getCodigo() << "\t";
	(vacante) ? entrada<<"SI\n": entrada <<"NO\n";
}

ostream & operator<<(ostream &salida, Plaza *p){
	salida << p->toString();
	return salida;
}
