#include "coleccionVuelo.h"

coleccionVuelo::coleccionVuelo() {
	tam = 30;
	cant = 0;
	v = new vuelo*[tam];
	for (int i = 0; i<tam; i++) {
		v[i] = NULL;
	}
}

bool coleccionVuelo::insertarVuelo(vuelo *_v) {
	vuelo *auxMayor;
	vuelo *auxMenor;
	ruta *auxR1;
	ruta *auxR2;
	if (cant < tam) {
		for (int i = 0; i<cant; i++) {
			if (v[i]->getId() == _v->getId()) {
				imprimeString("\n Este vuelo ya est\240 registrado");
				Sleep(1000);
				return false;
			}
			if (v[i]->getAv()->getId() == _v->getAv()->getId()) {
				if (v[i]->getFecha() == _v->getFecha()) {
					auxR1 = v[i]->getRut();
					auxR2 = _v->getRut();
					if (auxR1->getHduracion() >= auxR2->getHduracion()) {
						auxMayor = v[i];
						auxMenor = _v;
					}
					else {
						auxMayor = _v;
						auxMenor = v[i];
					}
					if (auxMayor->getHhoraSalida() <= auxMenor->getHhoraSalida() && auxMayor->getHhoraLlegada() >= auxMenor->getHhoraLlegada()) {
						imprimeString("\n Lo sentimos, el avi\242n asignado a este vuelo no se encuentra disponible en este horario");
						Sleep(2000);
						return false;
					}
				}
			}
		}
		v[cant] = _v;
		cant++;
		imprimeString("\n El vuelo se ha ingresado correctamente");
		Sleep(1000);
		return true;
	}
	imprimeString("\n Lo sentimos, la aerol241nea ha alcanzado su capacidad m\240xima de vuelos");
	Sleep(2000);
	return false;
}

int coleccionVuelo::buscarVuelo(string id) {
	for (int i = 0; i < cant; i++) {
		if (v[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

void coleccionVuelo::mostrarVuelo(string id) {
	int pos = buscarVuelo(id);
	if (pos == -1) {
		imprimeString("\n Lo sentimos, el vuelo no se encuentra registrado en el sistema");
		Sleep(1000);
	}
	else
		imprimeString(v[pos]->toString());
}

bool coleccionVuelo::eliminarVuelo(string id) {
	if (v[cant - 1]->getId() == id) {
		delete v[cant - 1];
		v[cant - 1] = NULL;
		cant--;
		imprimeString("\n El vuelo se ha eliminado con \202xito");
		Sleep(1000);
		return true;
	}
	else {
		int pos = buscarVuelo(id);
		if (pos != -1) {
			delete v[pos];
			for (int i = pos; i < cant - 1; i++) {
				v[i] = v[i + 1];
			}
			cant--;
			imprimeString("\n El vuelo se ha eliminado con \202xito");
			Sleep(1000);
			return true;
		}
	}
	imprimeString("\n Lo sentimos, este vuelo no es\240 registrado en el sistema");
	Sleep(2000);
	return false;
}

vuelo* coleccionVuelo::getVuelo(int pos) {
	return v[pos];
}

void coleccionVuelo::toString() {
	color(14); imprimeString("\n     같같같같같같같같같같같같같같같같같같같같같\n");
	imprimeString("     같                                      같\n");
	color(14); imprimeString("     같          "); color(15); imprimeString("VUELOS DISPONIBLES"); color(14); imprimeString("          같\n");
	imprimeString("     같                                      같\n");
	imprimeString("     같같같같같같같같같같같같같같같같같같같같같\n\n"); color(15);
	for (int i = 0; i<cant; i++) {
		imprimeString("\n __________________________________________________________\n\n");
		imprimeString("   Vuelo #"); imprimeInt(i + 1); imprimeString("\n");
		imprimeString(v[i]->toString());
		imprimeString("\n __________________________________________________________\n\n\n");
	}
}

coleccionVuelo::~coleccionVuelo() {
	for (int i = 0; i<cant; i++) {
		delete v[i];
	}
	delete[] v;
}