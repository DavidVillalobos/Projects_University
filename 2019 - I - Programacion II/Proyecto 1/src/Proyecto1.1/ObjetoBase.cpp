#include "ObjetoBase.h"

ObjetoBase::~ObjetoBase(){}

ostream& operator<<(ostream &salida , ObjetoBase *obj) {
	salida<<obj->toString();
	return salida;
}
