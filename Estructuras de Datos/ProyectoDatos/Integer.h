//Integer.h
//Autor:
//Luis David Villalobos González
//descripción: Biblioteca de clase para realizar calculos
// aritmeticos con enteros de logitud arbitraria

#ifndef INTEGER_H
#define INTEGER_H

#include"Exception.h"
#include"Nodo.h"
#include<math.h>
class Integer {
public:
	// Atributos
	bool sign;//true +, false -
	Nodo* start;

	// Constructores
	Integer();
	Integer(int);
	Integer(double);
	Integer(std::string);
	Integer(const Integer&);

	// Métodos de operaciones Aritméticas
	Integer sum(Integer&);
	Integer subtraction(Integer&);
	Integer multiply(Integer&);
	Integer division(Integer&);
	Integer complemento();

	// Sobrecargas de operadores Aritméticos
	Integer operator+(Integer&);
	Integer operator-(Integer&);
	Integer operator/(Integer&);
	Integer operator*(Integer&);

	// Sobrecarga de operadores de Asignación
	//=, +=, -=, *=, /=
	Integer operator=(const Integer&);
	Integer operator+=(Integer&);
	Integer operator-=(Integer&);
	Integer operator*=(Integer&);
	Integer operator/=(Integer&);

	// Sobrecarga de operadores de Comparación
	bool operator==(const Integer&);
	bool operator!=(const Integer&);
	bool operator<(Integer&);
	bool operator>(Integer&);
	bool operator>=(Integer&);
	bool operator<=(Integer&);

	// Sobrecarga de operador de Flujo de Salida
	friend std::ostream& operator<<(std::ostream&, Integer);
	
	// Conversiones
	static Integer parse(std::string);

	//Funciones
	static Integer factorial(int);
	static Integer fibonacci(int);
	static Integer combinations(int, int);

	//Métodos Auxiliares
	void clean();
	static Integer exponencial(Integer&, int);
	void init(std::string);
	void insertFinal(Nodo*);	
	bool reverseComparation(Nodo*, Nodo*);
	std::string reverse_to_string(Nodo*);
	int size();
	double d(int, int);

	//Destructor
	~Integer();
};
#endif // !INTEGER_H