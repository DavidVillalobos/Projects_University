//Integer.cpp
//Autor:
//Luis David Villalobos González
//Descripción: Definición de los métodos de la clase Integer.h

#include "Integer.h"

//Constantes
Integer zero(0);
Integer one(1);

//Constructores
Integer::Integer() {
	this->start = nullptr;
	this->sign = true;
}

Integer::Integer(int num) {
	std::stringstream s;
	s << num;
	init(s.str());
}

Integer::Integer(double num) {
	std::stringstream s;
	s << num;
	init(s.str());
}

Integer::Integer(std::string num) {
	if (num.empty()) { throw new Exception(3); }
	for (int i = 0; i < num.size(); i++) {
		if (num[i] != '+' && num[i] != '-') {
			if (!isdigit(num[i])) { 
				throw new Exception(2);
			}
		}
	}
	init(num);
}

Integer::Integer(const Integer& other) {
	this->sign = other.sign;
	this->start = new Nodo(*(other).start);
}


//Métodos de operaciones Aritméticas
//Suma
Integer Integer::sum(Integer& other) {
	bool signThis = this->sign;
	bool signOther = other.sign;
	// * si ambos son negativos simplemente resto el mayor con el menor
	if (!sign && !other.sign) {
		Integer result;
		Nodo* auxOwn = start;
		Nodo* auxOther = other.start;
		int ac = 0;
		result.sign = false;
		while (auxOwn && auxOther) {
			result.insertFinal(auxOwn->suma(*auxOther, ac));
			auxOwn = auxOwn->next;
			auxOther = auxOther->next;
		}	
		if (auxOwn) {
			Nodo* aux = new Nodo(*auxOwn);
			result.insertFinal(aux + ac);
		}
		else if (auxOther) {
			Nodo* aux = new Nodo(*auxOther);
			result.insertFinal(aux + ac);
		}
		else if (ac != 0) {
			Nodo* aux = new Nodo;
			*aux += ac;
			result.insertFinal(aux);
		}
		return result;
	}
	// * si ambos son positivos simplemente sumo   8 + 2 = 10
	else if (sign && other.sign) {
		Integer result;
		Nodo* auxOwn = start;
		Nodo* auxOther = other.start;
		int ac = 0;
		while (auxOwn && auxOther) {
			result.insertFinal(auxOwn->suma(*auxOther, ac));
			auxOwn = auxOwn->next;
			auxOther = auxOther->next;
		}
		if (auxOwn) {
			result.insertFinal(new Nodo(*auxOwn + ac));
		}
		else if (auxOther) {
			result.insertFinal(new Nodo(*auxOther + ac));
		}
		else if (ac != 0) {
			Nodo* aux = new Nodo;
			*aux += ac;
			result.insertFinal(aux);
		}
		return result;
	}
	// * si alguno es negativo entonces resto el mayor con el menor luego debo analizar los signos 
	else {
		Integer aux;
		bool signResult; 
		if (*this < other) {
			// si el mayor de ellos es negativo el resultado es negativo   (-8) + 2 = (-6)
			if (sign && other.sign) {
				signResult = true;
			}
			else if (!sign && other.sign) {
				this->sign = other.sign = true;
				if (*this < other) {
					signResult = true;
				}
				else {
					signResult = false;
				}
			}
			else {
				signResult = false;
			}
			aux = *this - other;
			aux.sign = signResult;
		}
		else {
			// si el mayor de ellos es negativo el resultado es negativo   2 + (-8) = (-6)
			if (sign && other.sign) {
				signResult = true;
			}
			else if (sign && !other.sign) {
				this->sign = other.sign = true;
				if (*this < other) {
					signResult = false;
				}
				else {
					signResult = true;
				}
			}
			else {
				signResult = false;
			}
			this->sign = other.sign = true;
			aux = *this - other;
			aux.sign = signResult;
		}
		this->sign = signThis;
		other.sign = signOther;
		return aux;
	}
}

//Resta
Integer Integer::subtraction(Integer& other) {
	Integer result;
	// * si ambos son positivos simplemente sumo   8 + 2 = 10
	// * si alguno es negativo entonces resto el mayor con el menor luego debo analizar los signos      
	//     -> si el mayor de ellos es negativo el resultado es negativo   (-8) + 2 = (-6)
	//     -> si el menor de ellos es negativo el resultado es positivo   8 + (-2) = 6
	// * si ambos son negativos simplemente resto el mayor con el menor
	//   y el resultado es negativo,    (-8) - (-2) = (-8) + 2 = (-6)
	//Primero se deben terminar lozs metodos de comparacion
	Nodo* auxOwn = start;
	Nodo* auxOther = other.start;
	int acarreoNegativo = 0;

	if (*this < other) {
		while (auxOwn && auxOther) {
			//Como forma de optimizacion cada nodo se resta con su par y se envia el acarreo por referencia
			if (!sign && !other.sign) {
				result.sign = false;
				result.insertFinal(auxOwn->resta(*auxOther, acarreoNegativo));
			}
			else if (sign && other.sign) {
				result.sign = false;
				result.insertFinal(auxOther->resta(*auxOwn, acarreoNegativo));
			}
			else if (!sign && other.sign) {
				result.sign = false;
				result.insertFinal(auxOwn->suma(*auxOther, acarreoNegativo));
			}
			auxOwn = auxOwn->next;
			auxOther = auxOther->next;
		}
	}
	else {
		while (auxOwn && auxOther) {
			//Como forma de optimizacion cada nodo se resta con su par y se envia el acarreo por referencia
			if (!sign && !other.sign) {
				result.sign = true;
				result.insertFinal(auxOther->resta(*auxOwn, acarreoNegativo));
			}
			else if (sign && other.sign) {
				result.sign = true;
				result.insertFinal(auxOwn->resta(*auxOther, acarreoNegativo));
			}
			else if (sign && !other.sign) {
				result.sign = true;
				result.insertFinal(auxOwn->suma(*auxOther, acarreoNegativo));
			}
			auxOwn = auxOwn->next;
			auxOther = auxOther->next;
		}
	}
	if (auxOwn) {
		result.insertFinal(auxOwn - acarreoNegativo);
	}
	else if (auxOther) {
		result.insertFinal(auxOther - acarreoNegativo);
	}

	return result;
}

//Multiplicacion
Integer Integer::multiply(Integer& other) {
	if (*this == one) { return other; }
	if (other == one) { return *this; }
	if (*this == zero || other == zero) { return zero; }
	//Algoritmo de la multiplicacion O(n2)
	Integer resultadoTotal(zero);
	Nodo *producto_1 = nullptr;
	Nodo *producto_2 = nullptr;
	bool flag = *this > other;
	producto_1 = (flag) ? start : other.start;
	int vueltas = 0;
	Integer tmp;
	while (producto_1) {
		tmp = zero;
		producto_2 = (flag) ? other.start : start;      
		while (producto_2) {							
			Integer aux;								
			aux.start = producto_1->multiplicar(*producto_2);
			tmp += aux;
			producto_2 = producto_2->next;
		}
		producto_1 = producto_1->next;
		for (int i = 0; i < vueltas; i++) {
			tmp.start = new Nodo(zero.start->getN(), tmp.start);
		}
		resultadoTotal += tmp;
		vueltas++;
	}
	resultadoTotal.sign = sign == other.sign;
	return resultadoTotal;
}

//Division
Integer Integer::division(Integer& other) {
	Integer onne(one);
	onne.sign = (sign == other.sign);
	if (other == zero) { throw new Exception(1); }
	if (*this == other) {
		return onne; 
	}
	if (*this == zero || (*this <= other && this->sign && other.sign)) { return zero; }
	if (other == one) { return *this; }
	bool signThis = this->sign;
	bool signOther = other.sign;
	other.sign = this->sign = true;
	Integer Own(*this);
	Integer Other(other);
	Integer vector[20] = { Integer(1000000),Integer(500000),Integer(250000),Integer(125000),
						   Integer(62500),Integer(31250),Integer(15625),Integer(7812),
							Integer(3906),Integer(1953),Integer(976),Integer(488),Integer(244),
							Integer(122),Integer(61),Integer(30),Integer(15),Integer(7),Integer(3), one };
	Integer multiplo(vector[0]);
	int i = 0;
	//Algoritmo de la division normal pero en vez de ir uno en uno, utiliza la busqueda binaria
	while (multiplo * other <= *this) {
		multiplo += vector[i];
	}
	i++;
	multiplo -= vector[i++];
	while (i < 20) {
		if (multiplo * other < *this) {
			multiplo += vector[i];
		}
		else {
			multiplo -= vector[i];
		}
		i++;
	}
	while (multiplo * other > * this) {
		multiplo -= one;
	}
	if ((multiplo + one + one + one) * other == *this) {
		multiplo = multiplo + one + one + one;
	}else if ((multiplo + one + one) * other == *this) {
		multiplo = multiplo + one + one;
	} else if ((multiplo + one) * other == *this) {
		multiplo = multiplo + one;
	}
	this->sign = signThis;
	other.sign = signOther;
	multiplo.sign = (sign == other.sign);
	return multiplo;
}

//Complemento
Integer Integer::complemento() {
	Integer result;
	Nodo* aux = start;
	while (aux) {
		result.insertFinal(aux->complemento());
		aux = aux->next;
	}
	Integer* s = new Integer(1);
	result += *s;
	return result;
}

// Sobrecarga de operadores Aritméticos

Integer Integer::operator+(Integer& other) { return sum(other); }

Integer Integer::operator-(Integer& other) { return subtraction(other); }

Integer Integer::operator/(Integer& other) { return division(other); }

Integer Integer::operator*(Integer& other) { return multiply(other); }

// Sobrecarga de operadores de Asignación

Integer Integer::operator=(const Integer& other) {
	this->sign = other.sign;
	this->start = new Nodo(*(other.start));
	return *this;
}

Integer Integer::operator+=(Integer& other) {
	*this = Integer(sum(other));
	return *this;
}

Integer Integer::operator-=(Integer& other) {
	*this = Integer(subtraction(other));
	return *this;
}

Integer Integer::operator*=(Integer& other) {
	*this = Integer(multiply(other));
	return *this;
}

Integer Integer::operator/=(Integer& other) {
	*this = Integer(division(other));
	return *this;
}

//Sobrecarga de operadores de Comparación
bool Integer::operator==(const Integer& other) {
	Nodo* auxOwn = start;
	Nodo* auxOther = other.start;
	while (auxOwn && auxOther) {
		if ((*auxOwn) != (*auxOther)) {
			return false;
		}
		auxOwn = auxOwn->next;
		auxOther = auxOther->next;
	}
	if (!auxOwn && !auxOther) {
		return true;
	}
	return false;
}

bool Integer::operator!=(const Integer& other) { return !(*this == other); }

bool Integer::operator<(Integer& other) {
	int cThis = size();
	int cOther = other.size();
	if (sign && other.sign) {
		if (cThis < cOther) {
			return true;
		}
		else if (cThis > cOther) {
			return false;
		}
		else {
			return reverseComparation(start, other.start);
		}
	}
	else if (!sign && !other.sign) {
		if (cThis > cOther) {
			return true;
		}
		else if (cThis < cOther) {
			return false;
		}
		else {
			return !reverseComparation(start, other.start);
		}
	}
	return (!sign && other.sign);
}

bool Integer::operator>(Integer& other) { return other < *this; }

bool Integer::operator>=(Integer& other) { return *this > other || *this == other; }

bool Integer::operator<=(Integer& other) { return *this < other || *this == other; }

//Sobrecarga del operado de Flujo de Salida
std::ostream& operator<<(std::ostream& os, Integer i) {
	if (!i.sign) { os << "-"; }
	os << i.reverse_to_string(i.start);
	return os;
}

//Conversiones
Integer Integer::parse(std::string num) { return Integer(num); }

//Funciones

// Factorial
Integer Integer::factorial(int n) {
	if (n == 0 || n == 1) { return one; }
	Integer sol = Integer(n);
	Integer anterior(sol - one);
	for (anterior; anterior > zero; anterior -= one) {
		sol *= anterior;
	}
	return sol;
}

// Fibonacci
Integer Integer::fibonacci(int n) {
	if (n <= 0) { return zero; }
	if (n == 1) { return one; }
	Integer actual;
	Integer ant2 = 0;
	Integer ant1 = 1;
	for (int i = 2; i <= n; i++) {
		actual = ant2 + ant1;
		ant2 = ant1;
		ant1 = actual;
	}
	return actual;
}

// Combinations
Integer Integer::combinations(int n, int k) {
	if (n < 0 || k < 0) { return zero; }
	Integer aux = factorial(n);
	Integer aux2 = factorial(n - k);
	Integer aux3 = factorial(k);
	Integer d = aux2 * aux3;
	return aux / d;
}

//Metodos Auxiliares
void Integer::clean() {
	Nodo* tmp = start;
	while (tmp) {
		start = start->next;
		delete tmp;
		tmp = start;
	}
}

//Exponencial
Integer Integer::exponencial(Integer &num, int n) {
	if (n == 0) { return one; }
	Integer elevado = num;
	for (int i = 1; i < n; ++i) { 
		elevado = elevado * num;
	}
	return elevado;
}

//Metodos Auxiliares
void Integer::init(std::string numero) {
	int n[Tam];
	start = nullptr;
	sign = true;
	if (numero[0] == '-') {
		sign = false;
		numero = numero.substr(1);
	}
	else if (numero[0] == '+') {
		numero = numero.substr(1);
	}
	std::string tmp = "";
	for (int i = int(numero.length()) - 1, k = Tam - 1; i >= 0; i -= Can, k--) {
		(i - Can >= 0) ? tmp = numero.substr(int(i - Can + 1), Can) : tmp = numero.substr(0, int(i + 1));
		n[k] = std::stoi(tmp);
		if (k == 0 || i < Can) {
			for (int u = 0; u < k; u++) { n[u] = 0; }
			insertFinal(new Nodo(n));
			k = Tam;
		}
	}
}

void Integer::insertFinal(Nodo* nuevo) {
	if (!start) {
		start = nuevo;
		return;
	}
	if (!start->next) {
		start->next = nuevo;
		return;
	}
	Nodo* aux = start;
	while (aux->next != nullptr) {
		aux = aux->next;
	}
	aux->next = nuevo;
}

bool Integer::reverseComparation(Nodo* this_n, Nodo* other_n) {
	if (this_n->next != nullptr && other_n->next != nullptr) {
		if (reverseComparation(this_n->next, other_n->next)) {
			return true;
		}
	}
	return *this_n < *other_n;
}

std::string Integer::reverse_to_string(Nodo* n) {//Debido a que la cantidad de nodos 
	// es poca si se pueden almacenar muchos numeros, es mas eficiente utilizar recursividad
	if (n != nullptr) {
		Nodo* next = n->next;
		return reverse_to_string(n->next) + n->to_string(!next);
	}
	return "";
}

int Integer::size() {
	if (!start) { return 0; }
	if (!start->next) { return start->size(); }
	int can = 0;
	Nodo* aux = start;
	while (aux->next) {
		aux = aux->next;
		can++;
	}
	return can * Tam * Can + aux->size();
}

double Integer::d(int b, int n) {//Retorna el desperdicio de memoria
	/*	Formula del desperdicio de memoria siendo b la
		cantidad de bytes por celda y n la cantidad de
		celdas en el nodo, sabemos que gastamos
		aproximadamente el 18,19% de la memoria por cada nodo
	*/
	double in_node = b * n + 4; // +4 del puntero next
	in_node *= 18.19;
	return in_node;// se desperdicia in_node cantidad de bytes por nodo
}

// Destructor
Integer::~Integer() { clean(); }