#include "coleccionRuta.h"

coleccionRuta::coleccionRuta() {
	cant = 0;
	tam = 30;
	_r = new ruta*[tam];
	for (int i = 0; i < 30; i++) {
		_r[i] = NULL;
	}
}

int coleccionRuta::getCant() { return cant; }

bool coleccionRuta::insertarRuta(ruta *rut) {
	if (cant<30) {
		for (int i = 0; i < cant; i++) {
			if (_r[i]->getId() == rut->getId()) {
				imprimeString(" Esta ruta ya est\240 registrada en el sistema");
				Sleep(1000);
				return false;
			}
		}
		_r[cant] = rut;
		cant++;
		imprimeString(" La ruta se ingres\242 correctamente");
		Sleep(1000);
		return true;
	}
	imprimeString(" Lo sentimos, el sistema no tiene capacidad para m\240s rutas");
	Sleep(1000);
	return false;
}

int coleccionRuta::buscarRuta(string id) {
	for (int i = 0; i < cant; i++) {
		if (_r[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

bool coleccionRuta::eliminarRuta(string id) {
	int aux = buscarRuta(id);
	if (aux != -1) {
		if (_r[cant - 1]->getId() == id) {
			delete _r[cant - 1];
			_r[cant - 1] = NULL;
			cant--;
			imprimeString("\n La ruta ha sido eliminada con \202xito");
			Sleep(1000);
		}
		else {
			int pos = buscarRuta(id);
			if (pos != -1) {
				delete _r[pos];
				for (int i = pos; i < cant - 1; i++) {
					_r[i] = _r[i + 1];
				}
				cant--;
				imprimeString("\n La ruta ha sido eliminada con \202xito");
				Sleep(1000);
			}
		}
		return true;
	}
	else {
		imprimeString("\n La identificaci\242n no es v\240lida, intente con otra");
		Sleep(2000);
		
	}
	return false;
}

void coleccionRuta::muestraRuta(string id) {
	int aux = buscarRuta(id);
	if (aux != -1) {
		imprimeString(_r[aux]->toString());
		system("pause");
	}
	else {
		imprimeString("La identificacion no es valida, intente con otra");
		Sleep(3000);
	}
}

void coleccionRuta::toString() {
	color(14); imprimeString("\n     같같같같같같같같같같같같같같같같같같같같같\n");
	imprimeString("     같                                      같\n");
	color(14); imprimeString("     같          "); color(15); imprimeString("RUTAS DISPONIBLES"); color(14); imprimeString("           같\n");
	imprimeString("     같                                      같\n");
	imprimeString("     같같같같같같같같같같같같같같같같같같같같같\n\n"); color(15);
	for (int i = 0; i < cant; i++) {
		imprimeString("\n __________________________________________________________\n\n");
		imprimeString("   Ruta #"); imprimeInt(i + 1); imprimeString("\n");
		imprimeString(_r[i]->toString());
		imprimeString("\n __________________________________________________________\n\n\n");
	}
}

ruta* coleccionRuta::getRuta(int pos) {
	return _r[pos];
}

coleccionRuta::~coleccionRuta() {
	for (int i = 0; i < cant; i++) {
		delete _r[i];
	}
	delete[] _r;
} 