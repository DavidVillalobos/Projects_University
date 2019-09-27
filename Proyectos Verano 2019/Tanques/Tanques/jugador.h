#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
#include <sstream>
using namespace std;
class jugador {
private:
	int puntuacion;
	string nombre;
	string modalidad;
	jugador *sig;
public:
	jugador(int = 0, string = "ifndef", string = "indef", jugador* = NULL);
	int getPuntuacion();
	string getNombre();
	string getModalidad();
	jugador* getSig();
	void setPuntuacion(int);
	void setNombre(string);
	void setModalidad(string);
	void setSig(jugador*);
	string toString();
	~jugador();
};
#endif