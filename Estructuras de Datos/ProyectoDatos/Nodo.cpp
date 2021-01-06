//Nodo.cpp
//Autor:
//Luis David Villalobos González
//Descripción: Definición de los métodos de la clase Nodo.h

#include "Nodo.h"

//Constructores
Nodo::Nodo(){
	this->next = nullptr;
	for (int i = 0; i < Tam; i++) { this->n[i] = 0; }
}

Nodo::Nodo(int n[], Nodo* next){
	this->next = next;
	for (int i = 0; i < Tam; i++) { this->n[i] = n[i]; }
}

Nodo::Nodo(const Nodo& other) {
	for (int i = 0; i < Tam; i++) { 
		this->n[i] = other.n[i]; 
	}
	this->next = (other.next)? new Nodo(*other.next): nullptr;
}

int* Nodo::getN(){ return n; }

//Operaciones Aritméticas
Nodo* Nodo::suma(const Nodo& p, int& ac) {
	Nodo* m = new Nodo;
	for (int i = Tam - 1; i >= 0; i--) {
		if (n[i] != 0 || p.n[i] != 0 || ac != 0) {
			ac = n[i] + p.n[i] + ac;
			if (ac > 9999) {
				ac -= 10000;
				m->n[i] = ac;
				ac = 1;
			}
			else {
				m->n[i] = ac;
				ac = 0;
			}
		}
	}
	return m;
}

Nodo* Nodo::resta(const Nodo& p, int& acN) {
	Nodo* m = new Nodo;
	int n1 = 0; int n2 = 0; int nuevo = 0;
	int dig1 = 0; int dig2 = 0; int x = 0;
	for (int i = Tam - 1; i >= 0; i--) {
		if (p.n[i] != 0 || n[i] != 0) {
			n1 = n[i];
			n2 = p.n[i];
			x = 0; nuevo = 0;
			while (n1 > 0 || n2 > 0) {
				dig1 = (n1 % 10) - acN;
				dig2 = n2 % 10;
				if (dig1 < dig2) {
					dig1 += 10;
					acN = 1;
				}
				else {
					acN = 0;
				}
				nuevo += (dig1 - dig2) * pow(10, x);
				n1 /= 10;
				n2 /= 10;
				x++;
			}
			m->n[i] = nuevo;
		}
		else {
			m->n[i] = 0;
		}
	}
	return m;
}

Nodo* Nodo::multiplicar(const Nodo &p) {
	Nodo* tmp = new Nodo;
	Nodo* tmp1 = tmp;
	Nodo* tmp2 = nullptr;
	Nodo* tmp3 = nullptr;
	unsigned long long int result = 0;
	unsigned long long int ac = 0;    
	int ite = Tam - 1;       
	bool flag = true;                     
	for (int i = Tam - 1; 0 <= i; i--) { 
		for (int j = Tam - 1; 0 <= j; j--) {
			if (ac != 0 || (p.n[i] != 0 && n[j] != 0)) {
				result = p.n[i] * n[j] + tmp->n[ite] + ac;
				if (result <= 9999) {
					tmp->n[ite] = result;
					ac = 0;
				}
				else {
					ac = result / 10000;
					tmp->n[ite] = result % 10000;
				}
			}
			if (ite == 0 && ac != 0) {
				tmp = new Nodo;
				tmp3 = tmp2;
				tmp2 = tmp1;
				tmp1 = tmp;
				if (tmp3) {
					tmp3->next = tmp2;
				}
				if (tmp2) {
					tmp2->next = tmp1;
				}
				flag = false;
				ite = Tam - 1;
			}
			else { ite--; }
		}
		(flag) ? ite = i - 1 : flag = true;
	}
	if (tmp3) {   // [X] -> [X] -> [X]
		return tmp3; 
	}
	if (tmp2) { 
		return tmp2; 
	}
	return tmp1;
}

Nodo* Nodo::complemento() {
	Nodo* res = new Nodo;
	int result;
	for (int x = Tam - 1; x >= 0; x--) {
		result = 0;
		result = 9999 - n[x];
		res->n[x] = result;
	}
	return res;
}

//Sobrecarga de Operadores
int& Nodo::operator[](int pos){ return n[pos]; }

Nodo& Nodo::operator=(const Nodo& p){
	this->next = next;
	for (int i = 0; i < Tam; i++) {
		this->n[i] = p.n[i];
	}
	return *this;
}

bool Nodo::operator==(const Nodo &p){
	for (int i = Tam - 1; 0 <= i; i--) {
		if (p.n[i] != n[i]) {
			return false;
		}
	}
	return true;
}

bool Nodo::operator!=(const Nodo &p){
	for (int i = Tam - 1; 0 <= i; i--) {
		if (p.n[i] != n[i]) {
			return true;
		}
	}
	return false;
}

bool Nodo::operator<(const Nodo& other){
	for (int i = 0; i < Tam; i++){
		if (n[i] < other.n[i]) { return true; }
		else if (n[i] > other.n[i]) { return false; }
	}
	return false;
}

Nodo Nodo::operator+=(const Nodo& other){
	int ac = 0;
	*this = *suma(other,ac);
	if (ac != 0) {
		Nodo* aux = new Nodo;
		aux += ac;
		aux->next = this;
		*this = *aux;
	}
	return *this;
}

Nodo& Nodo::operator+=(const unsigned long long int &num){
	unsigned long long int auxNum = num;
	for (int i = Tam - 1; 0 <= i; i--) {
		if (auxNum > 9999) {
			n[i] = auxNum % 10000;
			auxNum /= 10000;
		}
		else {
			n[i] = num;
			auxNum = 0;
			break;
		}
	}
	return *this;
}

Nodo& Nodo::operator+(int num){
	int ac = num;
	for (int i = Tam-1; 0 <= i ; i--){
		ac += n[i];
		if (ac > 9999) {
			n[i] = 0;
			ac -= 9999;
		}
		else {
			n[i] = ac;
			break;
		}
	}
	return *this;
}

Nodo& Nodo::operator-(int num){
	int acarreoNegativo = num;
	for (int i = Tam - 1; 0 <= i; i--) {
		if (num < n[i]) {
			n[i] -= num;
			break;
		}
		n[i] = n[i] + 10000 - num;
		acarreoNegativo = 1;
	}
	return *this;
}

//toString
std::string Nodo::to_string(bool last) {
	std::stringstream s;
	bool flag = true;
	for (int i = 0; i < Tam; i++) {
		if (last && n[i] != 0) {
			last = false;
			s << n[i];
		}
		else if (!last) {
			if (n[i] < 10) {
				s << "000" << n[i];
			}
			else if (n[i] < 100) {
				s << "00" << n[i];
			}
			else if (n[i] < 1000) {
				s << "0" << n[i];
			}
			else {
				s << n[i];
			}
		}
	}
	std::string num = s.str();
	if (num[0] == '\0') { return "0"; }
	return num;
}

//Método Auxiliar
int Nodo::size() {
	int i;
	for (i = 0; i < Tam; i++) { if (n[i] != 0) { break; } }
	if (i < Tam) {
		int can = (Tam - i - 1) * 4;
		if (999 < n[i]) { can += 4; }
		else if (99 < n[i]) { can += 3; }
		else if (9 < n[i]) { can += 2; }
		else { can += 1; }
		return can;
	}
	return 0;
}

//Destructor
Nodo::~Nodo(){}