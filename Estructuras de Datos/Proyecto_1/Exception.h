//Exception.h
//Autor:
//Luis David Villalobos González
//Descripción: Clase encargada del control de errores

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include<string>
class Exception {
	int numError;
public:
	Exception(int);
	std::string showError();
};
#endif // !EXCEPTION.H
