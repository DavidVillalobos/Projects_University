#ifndef PASAJERO_H
#define PASAJERO_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class pasajero {
private:
	string nombre, id;
public:
	pasajero(string = "indef", string = "indef");
	string getNombre();
	string getId();
	string toString();
	~pasajero();
};
#endif