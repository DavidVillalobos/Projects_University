#include "hangar.h"

hangar::hangar() {
	cant = 0;
	for (int i = 0; i<30; i++) {
		_a[i] = NULL;
	}
}

int hangar::getCant() { return cant; }

bool hangar::insertAvion(avion *av) {
	if (cant < 30) {
		for (int i = 0; i < cant; i++) {
			if (_a[i]->getId() == av->getId()) {
				imprimeString("\n Ya existe un avi\242n registrado en el hangar con ese ID");
				Sleep(1000);
				return false;
			}
		}
		_a[cant] = av;
		cant++;
		imprimeString("\n El avi\242n ha sido ingresado con \202xito");
		Sleep(1000);
		return true;
	}
	else {
		imprimeString("\n El hangar se ha quedado sin campo");
		Sleep(1000);
		return false;
	}
}

int hangar::buscarAvion(string id) {
	for (int i = 0; i < cant; i++) {
		if (_a[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

void hangar::muestraAvion(string id) {
	int aux = buscarAvion(id);
	if (aux != -1) {
		imprimeString(_a[aux]->toString());
		imprimeString("\n");
		system("pause");
	}
	else {
		imprimeString("\n La identificaci\242n no es v\240lida, intente con otra");
		Sleep(2000);
	}
}

bool hangar::eliminarAvion(string id) {
	int pos = buscarAvion(id);
	if (pos != -1) {
		if (_a[cant - 1]->getId() == id) {
			delete _a[cant - 1];
			_a[cant - 1] = NULL;
			cant--;
			imprimeString("\n El avi\242n ha sido elminado con \202xito");
			Sleep(1000);
			return true;
		}
		else {
			delete _a[pos];
			for (int i = pos; i < cant - 1; i++) {
				_a[i] = _a[i + 1];
			}
			cant--;
			imprimeString("\n El avi\242n ha sido elminado con \202xito");
			Sleep(1000);
			return true;
		}
	}
	else {
		imprimeString("\n Lo sentimos, el avi\242n no existe en el hangar");
		Sleep(1000);
		return false;
	}
}

void hangar::toString() {
	color(14); imprimeString("\n     같같같같같같같같같같같같같같같같같같같같같\n");
	imprimeString("     같                                      같\n");
	color(14); imprimeString("     같          "); color(15); imprimeString("AVIONES DISPONIBLES"); color(14); imprimeString("         같\n");
	imprimeString("     같                                      같\n");
	imprimeString("     같같같같같같같같같같같같같같같같같같같같같\n\n"); color(15);
	for (int i = 0; i<cant; i++) {
		imprimeString("\n __________________________________________________________\n\n");
		imprimeString("   Avi\242n #"); imprimeInt(i + 1); imprimeString("\n");
		imprimeString(_a[i]->toString());
		imprimeString("\n __________________________________________________________\n\n\n");
	}
}

avion* hangar::getAvion(int pos) {
	return _a[pos];
}

hangar::~hangar() {
	for (int i = 0; i < cant; i++) {
		delete _a[i];
	}
}