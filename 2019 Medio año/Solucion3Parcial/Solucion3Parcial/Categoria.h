#pragma once
#include <sstream>
#include<fstream>
using namespace std;
class Categoria {
private:
	int _id;
	string _nombre;
	double _salarioBase;
public:
	Categoria(int categoria) {
		ifstream entrada("../categorias.txt");
		string categor;
		string salarioBase;
		if (entrada.good()) {
			while (!entrada.eof()) {
				//11	Asistente administrativo	1500
				getline(entrada, categor, '\t');
				getline(entrada, _nombre, '\t');
				getline(entrada, salarioBase, '\n');
				if (!categor.empty() && !_nombre.empty() && !salarioBase.empty()) {
					stringstream r(categor);
					r >> _id;
					if (_id == categoria) {
						_salarioBase = atof(salarioBase.c_str());
						break;
					}
				}
			}
		}
		entrada.close();
	}
	double getSalarioBase() { return _salarioBase; }
	~Categoria() {}
};