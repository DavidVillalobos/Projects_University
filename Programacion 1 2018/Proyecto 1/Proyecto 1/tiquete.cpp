#include "tiquete.h"

tiquete::tiquete(string id, string idVuelo, string orig_dest, string sal_Lleg, char fil, int precio, int col, pasajero *pasaj) :id(id), idVuelo(idVuelo), orig_dest(orig_dest), sal_Lleg(sal_Lleg), fil(fil), precio(precio), col(col), pasaj(pasaj) {}

string tiquete::getId() { return id; }

string tiquete::getIdPers() { return pasaj->getId(); }

string tiquete::getIdVuelo() { return idVuelo; }

string tiquete::getOrig_dest() { return orig_dest; }

string tiquete::getSal_Lleg() { return sal_Lleg; }

int tiquete::getCol() { return col; }

int tiquete::getPrecio() { return precio; }

char tiquete::getFil() { return fil; }

pasajero* tiquete::getPasajero() { return pasaj; }

string tiquete::toString() {
	string colT= "";
	string filT = "";
	colT = static_cast<std::ostringstream*>(&(std::ostringstream() << getCol()))->str();
	filT = static_cast<std::ostringstream*>(&(std::ostringstream() << getFil()))->str();
	stringstream s;
	s << endl;
	s << "   N\243mero de tiquete: " << id << "    ID del Vuelo: " << idVuelo << endl;
	s <<"   N\243mero de Asiento: " << filT << "-" << colT <<  "   Hora de salida: " << sal_Lleg << endl;
	s <<"  "<<pasaj->toString();
 	s <<"   Direcci\242n: " << orig_dest<< "    Valor del Tiquete: " << precio << endl;
	return s.str();
}

tiquete::~tiquete() {}