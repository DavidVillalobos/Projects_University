#ifndef ETIQUETAS_H
#define ETIQUETAS_H
#include"etiqueta.h"
class etiquetas {
private:
	etiqueta* primero;
	etiqueta* actual;
public:
	etiquetas();
	void insertarEtiqueta(string);
	int porcentajeCompatibles(etiquetas*);
	string toString();
	bool buscarEtiqueta(string);
	int cuentaEtiquetas();
	~etiquetas();
};
#endif 