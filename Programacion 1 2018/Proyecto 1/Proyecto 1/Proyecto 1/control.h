#ifndef CONTROL_H
#define CONTROL_H
#include <string>
#include "in_out.h"
#include "hangar.h"
#include "tiquete.h"
#include "coleccionRuta.h"
#include "coleccionVuelo.h"
using namespace std;
class control {
private:
	hangar *hang;
	coleccionRuta *colR;
	coleccionVuelo *colV;
public:
	control();
	void menuPrincipal();
	void menuPasajero();
	void menuAdministrador();
	void gestionAvion();
	void gestionRuta();
	void gestionVuelo();
	void modificarAvion();
	void modificarVuelo();
	void modificarRuta();
	~control();
};
#endif