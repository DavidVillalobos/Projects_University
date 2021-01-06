//main.cpp
//Autor:
//Luis David Villalobos González
//Descripción: Prueba de Integer

#include<iostream>
#include"Integer.h"


//Methods Test
void test_operators(Integer&, Integer&);

//Operators
void test_operators_comparation(Integer&,Integer&);
void test_operators_arithmetic(Integer&,Integer&);
void test_operators_assignment(Integer&,Integer&);

void test_functions();

Integer requestInteger();

int main() {
	Integer a("+7122822");
	Integer b(-323);
	test_operators(a, b);
	Integer c("-80379712873");
	Integer d("383282");
	test_operators(c, d);
	Integer x("-3390082829191");
	Integer y(-9383981);
	test_operators(x, y);
	Integer z("8580493234");
	Integer w(839282);
	test_operators(z, w);
	test_functions();
	return 0;
}

//Test general operators
void test_operators(Integer& a, Integer& b) {
	std::cout << "a:  " << a << std::endl;
	std::cout << "b:  " << b << std::endl;
	test_operators_comparation(a, b);
	test_operators_arithmetic(a, b);
	test_operators_assignment(a, b);
}

void test_operators_comparation(Integer& a, Integer& b) {
	std::cout << "\n***Prueba de Operadores de Comparacion***\n\n";
	//------------- Operador == -------------
	std::cout << "a == b  -->  ";
	(a == b) ? std::cout << "true" : std::cout << "false";
	std::cout << std::endl;
	//------------- Operador != -------------
	std::cout << "a != b  -->  ";
	(a != b) ? std::cout << "true" : std::cout << "false";
	std::cout << std::endl;
	//------------- Operador < -------------
	std::cout << "a < b  -->  ";
	(a < b) ? std::cout << "true" : std::cout << "false";
	std::cout << std::endl;
	//------------- Operador <= -------------
	std::cout << "a <= b  -->  ";
	(a <= b) ? std::cout << "true" : std::cout << "false";
	std::cout << std::endl;
	//------------- Operador > -------------
	std::cout << "a > b  -->  ";
	(a > b) ? std::cout << "true" : std::cout << "false";
	std::cout << std::endl;
	//------------- Operador >= -------------
	std::cout << "a >= b  -->  ";
	(a >= b) ? std::cout << "true" : std::cout << "false";
	std::cout << std::endl;
	system("pause");
}

void test_operators_arithmetic(Integer& a, Integer& b) {
	std::cout << "\n***Prueba de Operadores Aritmeticos***\n\n";
	//------------- Operador + -------------
	std::cout << "+  -->  ";
	std::cout << a + b << std::endl;
	//------------- Operador - -------------
	std::cout << "-  -->  ";
	std::cout << a - b << std::endl;
	//------------- Operador * -------------
	std::cout << "*  -->  ";
	std::cout << a * b << std::endl;
	//------------- Operador / -------------
	std::cout << "/  -->  ";
	try {// Control de errores en la division
		std::cout << a / b << std::endl;
	}
	catch (Exception* e) {
		std::cout << e->showError();
		delete e;
	}
	system("pause");
}

void test_operators_assignment(Integer& a,Integer& b){
	std::cout << "\n***Prueba de Operadores de Asignacion***\n\n";
	//------------- Operador = -------------
	std::cout << "a = b \n";
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	a = b;
	std::cout << "--> a: " << a << std::endl;
	//------------- Operador += -------------
	std::cout << "\na += b \n";
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	a += b;
	std::cout << "--> a: " << a << std::endl;
	//------------- Operador -= -------------
	std::cout << "\na -= b \n";
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	a -= b;
	std::cout << "--> a: " << a << std::endl;
	//------------- Operador *= -------------
	std::cout << "\na *= b \n";
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	a *= b;
	std::cout << "--> a: " << a << std::endl;
	//------------- Operador /= -------------
	std::cout << "\na /= b \n";
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	try {// Control de errores en la division
		a /= b;
		std::cout << "--> a: " << a << std::endl;
	}
	catch (Exception* e) {
		std::cout << e->showError();
		delete e;
	}
	system("pause");
}

void test_functions(){
	std::cout << "\n***Prueba de Funciones***\n\n";
	//-------------Factorial-----------------
	std::cout << "Factorial(1000): " << Integer::factorial(1000) << std::endl;
	//-------------Fibonacci-----------------
	std::cout << "Fibonacci(348): " << Integer::fibonacci(348) << std::endl;
	//-------------Combinations-----------------
	std::cout << "Combinations(10, 3): " << Integer::combinations(10, 3) << std::endl;
	system("pause");
}

Integer requestInteger(){
	while (true) {
		std::string num;
		std::cout << "Enter a number: ";
		getline(std::cin, num);
		try {
			return Integer(num);
		}
		catch (Exception* e) {
			std::cout << e->showError();
			delete e;
		}
	}
}