#ifndef CONTROL_H
#define	CONTROL_H
#include <string>
#include <fstream>
using namespace std;
#include "etiquetas.h"
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

