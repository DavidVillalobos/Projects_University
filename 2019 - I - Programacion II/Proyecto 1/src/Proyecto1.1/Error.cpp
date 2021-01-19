#include "Error.h"

Error::Error(int numError): numError(numError){}

string Error::ejecutar(){
	// Aqui se reportan los errores
	// Ademas se retorna el mensaje de error para que
	// In_Out lo imprima por consola
	string what;
	switch (numError) {
	case 1: what = ""; break;
	default: break;
	}
	//Se abre un archivo y se reporta el error
	return what;
}

Error::~Error(){}
