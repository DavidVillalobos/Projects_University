//Nodo.h
//Autor:
//Luis David Villalobos González
//Descripción: Declaracion de la clase Nodo

#ifndef NODO_H
#define NODO_H

int const Tam = 9;//Tamaño del arreglo en el Nodo
int const Can = 4;//Cantidad de Digitos por espacio en el vector 
int const Base = 10;//Base Numerica

#include <sstream>

class Nodo {
	int n[Tam];
public:
	Nodo* next;
	//Constructores
	Nodo();
	Nodo(int[], Nodo* = nullptr);
	Nodo(const Nodo&);
	
	int* getN();

	//Operaciones Aritméticas
	Nodo* suma(const Nodo&, int&);
	Nodo* resta(const Nodo&, int&);
	Nodo* multiplicar(const Nodo& p);
	Nodo* complemento();
	
	//Sobrecarga de Operadores
	int& operator[](int);
	Nodo& operator =(const Nodo&);
	bool operator==(const Nodo&);
	bool operator!=(const Nodo&);
	bool operator<(const Nodo&);
	Nodo operator+=(const Nodo&);
	Nodo& operator+=(const unsigned long long int&);
	Nodo& operator+(int);
	Nodo& operator-(int);
	
	//Metodos Axiliares
	int size();
	std::string to_string(bool);
	//Destructor
	~Nodo();
};
#endif // !NODO_H