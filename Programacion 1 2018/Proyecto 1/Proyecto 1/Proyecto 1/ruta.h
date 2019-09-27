#ifndef RUTA_H
#define RUTA_H

#include <string>
#include <sstream>

using namespace std;

class ruta {
private:
	string id, origen, destino;
	int hDuracion, mDuracion, escala;
public:
	ruta(string = "indefinido", string = "indefinido", string = "indefinido", int = 0, int = 0, int = 0);
	void setId(string);
	void setOrigen(string);
	void setDestino(string);
	void setHduracion(int);
	void setMduracion(int);
	void setEscala(int);
	string getId();
	string getOrigen();
	string getDestino();
	int getHduracion();
	int getMduracion();
	int getEscala();
	string toString();
	~ruta();
};
#endif