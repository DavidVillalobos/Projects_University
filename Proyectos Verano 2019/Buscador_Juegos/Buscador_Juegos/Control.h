#ifndef CONTROL_H
#define	CONTROL_H
#include "juegos.h"
#include "in_out.h"

class Control{
private:
	juegos *listJuegos;
public:
	Control();
	void cargarArchivos();
	void menu();
	void iniciar();
	void saliendo();
	~Control();
};
#endif

