#ifndef  CONTROL_H
#define CONTROL_H
//#include <time.h>
#include <fstream>
#include "in_out.h"
#include "Gimnasio.h"
class Control {
private:
	Gimnasio **gym;
public:
	Control();
	void iniciar();
	void Compra();
	void menuAdministrador();
};
#endif // ! CONTROL_H
