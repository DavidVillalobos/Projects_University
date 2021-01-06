//Exception.cpp
//Autor:
//Luis David Villalobos González
//Descripción: Definición de los métodos de la clase Exception.h

#include "Exception.h"

Exception::Exception(int numError): numError(numError){}

std::string Exception::showError(){
	switch (numError) {
	case 1: return "Integer division by zero\n"; break;
	case 2: return "Only numerical values are allowed\n"; break;
	case 3: return "An empty value is not allowed\n"; break;
		default: return "Unknown error contact technical support";
	}
}