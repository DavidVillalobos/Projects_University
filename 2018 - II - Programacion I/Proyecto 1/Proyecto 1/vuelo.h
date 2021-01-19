#ifndef VUELO_H
#define VUELO_H
#include <string>
#include <sstream>
using namespace std;
#include "pasajero.h"
#include "tiquete.h"
#include "avion.h"
#include "ruta.h"
#include "in_out.h"
class vuelo {
private:
	string id, fecha, aeroLlegada, aeroSalida, piloto;
	int hHoraSalida, mHoraSalida, precio, hHoraLlegada, mHoraLlegada, cantTyP;
	avion *av;
	ruta *rut;
	tiquete **coleccionTiquete;
	pasajero **lista;
	bool **asiento;
public:
	vuelo(string = "000", string = "0/0/0", string = "---", string = "---", string = "indefinido", int = 0, int = 0, int = 0, avion* = NULL, ruta* = NULL);
	void setId(string);
	void setFecha(string);
	void setAeroLlegada(string);
	void setAeroSalida(string);
	void setPiloto(string);
	void setHhoraLlegada();
	void setMhoraLlegada();
	void setHhoraSalida(int);
	void setMhoraSalida(int);
	void setPrecio(int);
	void setCantTyP(int);
	void setAv(avion*);
	void setRut(ruta*);
	string getId();
	string getFecha();
	string getAeroLlegada();
	string getAeroSalida();
	string getPiloto();
	int getHhoraSalida();
	int getMhoraSalida();
	int getHhoraLlegada();
	int getMhoraLlegada();
	int getPrecio();
	int getCantTyP();
	avion* getAv();
	ruta* getRut();
	tiquete* getTiquete(int);
	pasajero* getPasajero(int);
	void mostrarAsientos();
	void listaPasajeros();
	void listaTiquetes();
	string toString();
	int LetraAsiento(char);
	int buscarTiquete(string);
	bool insertarTiquete(tiquete*);
	void mostrarTiquete(string);
	bool eliminarTiquete(string);
	~vuelo();
};
#endif