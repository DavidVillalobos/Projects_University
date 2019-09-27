#include "Empresa.h"

Empresa::Empresa(string nombre, string direccion, int numeroTelefono){
	this->nombre = nombre;
	this->direccion = direccion;
	this->numeroTelefono = numeroTelefono;
	listC = new Lista();
	listE = new Lista();
	listP = new Lista();
	listPl = new Lista();
	cargasSociales = 9;
	ahorroObligatorio = 2;
	impuestoSobreLaRenta = 20;
}

Empresa::~Empresa() { delete listC, listE, listP; }

int Empresa::getCargasSociales(){ return cargasSociales; }

int Empresa::getAhorroObligatorio(){ return ahorroObligatorio; }

int Empresa::getImpuestoSobreLaRenta(){ return impuestoSobreLaRenta; }

string Empresa::getNombre(){ return nombre; }

string Empresa::getdireccion(){ return direccion; }

int Empresa::getNumeroTelefono(){ return numeroTelefono; }

void Empresa::setDireccion(string direccion){ this->direccion = direccion; }

void Empresa::setNumeroTelefono(int numeroTelefono){ this->numeroTelefono = numeroTelefono;}

void Empresa::ingresarEmpleado(Empleado* nuevo) { listE->insertarInicio(nuevo);}

Lista* Empresa::getListE(){ return listE; }

Lista* Empresa::getListC(){ return listC; }

Lista* Empresa::getListP(){ return listP; }

Lista* Empresa::getListPl(){ return listPl; }

void Empresa::ingresarContrato(Contrato *nuevo){ listC->insertarInicio(nuevo); }

void Empresa::ingresarPuesto(Puesto *nuevo){ listP->insertarInicio(nuevo); }

void Empresa::ingresarPlaza(Plaza *nuevo){ listPl->insertarInicio(nuevo); }

float Empresa::CalcularSalarioNeto(Contrato* c) {
	float cs = c->getPuesto()->getSalarioBase() * float(cargasSociales / 100);
	float ao = c->getSalarioBruto() * float(ahorroObligatorio / 100);
	float ir = (c->getSalarioBruto() > 1200000) ? (c->getSalarioBruto() - 1200000) * float(impuestoSobreLaRenta / 100) : 0;
	c->setSalarioNeto(c->getSalarioBruto() - cs - ao - ir);
	return c->getSalarioNeto();	
}

float Empresa::CalcularSalarioBruto(Contrato *c) {
	c->setSalarioBruto(c->getAdicionales() + c->getPuesto()->getSalarioBase());
	return c->getSalarioBruto();
}

int Empresa::CalcularVacaciones(Contrato* c) {
	int dia, mes, anno; // Variables para el paso de parametros por referencia
	c->Tdif_Tactual(dia, mes, anno); //Retorna por referencia la diferencia entre la fecha de ingreso y la actual
	return 30 * anno;//Se retornan los dias de vacaciones
}

float Empresa::CalcularLiquidacion(Contrato* c) {
	int dia, mes, anno;
	c->Tdif_Tactual(dia, mes, anno);
	if (anno == 0) {
		if (3 <= mes && mes <= 6) {
			return c->getSalarioNeto()/30 * 7;
		}
		if (6 < mes && mes <= 11) {
			return c->getSalarioNeto()/30 * 14;
		}
	}
	return (19 + ((1 / 2) * anno)) * (c->getSalarioNeto() / 30);
}

float Empresa::despedir(Contrato *c){
	c->cesarContrato();//Inicializa la fecha de cesantia como hoy
	c->cesantiaContrato(); //Los contratos con plaza seran desactivados
	return CalcularLiquidacion(c); 
}

Planilla* Empresa::getContratoPlanilla(Contrato *c) {
	Planilla* p = dynamic_cast<Planilla*>(c);
	return p;
}

Profesional* Empresa::getContratoProfesional(Contrato *c) {
	Profesional* p = dynamic_cast<Profesional*>(c);
	return p;
}

float Empresa::calcularAguinaldo(Contrato*c) {
	float salario = c->getSalarioBruto() * 12;
	salario += c->getAdicionales();
	return salario / 12;
}

Puesto * Empresa::getPuesto(string cod) {
	Puesto *r = NULL;
	for (int i = 0; i < listP->getK(); i++) {
		//Convertidor de ObjetoBase* a Puesto*
		r = dynamic_cast <Puesto*>(listP->getElemento(i));
		if ( r->getCodigo() == cod) {
			break;
		}
	}
	return r;
}

Contrato* Empresa::getContrato(string id) {
	Contrato *r = NULL;
	Empleado *e = NULL;
	for (int i = 0; i < listC->getK(); i++) {
		//Convertidor de ObjetoBase* a Contrato*
		r = dynamic_cast <Contrato*>(listC->getElemento(i));
		if (r) {
			e = r->getEmpleado();
			if (e) {
				if (e->getId() == id) {
					break;
				}
			}
		}
	}
	return r;
}

Contrato* Empresa::getContrato(int pos) {
	Contrato *r = dynamic_cast <Contrato*>(listC->getElemento(pos));
	if (r) {
		return r;
	}
	return NULL;
}

Empleado* Empresa::getEmpleado(string id) {
	Empleado *r = NULL;
	for(int i = 0; i < listE->getK(); i++) {
		//Convertidor de ObjetoBase* a Empleado*
		r = dynamic_cast<Empleado*>(listE->getElemento(i));
		if (r) {
			if (r->getId() == id) {
				break;
			}
		}
	}
	return r;
}

Plaza* Empresa::getPlaza(string cod) {
	Plaza *r = NULL;
	Puesto *p = NULL;
	for (int i = 0; i < listP->getK(); i++) {
		//Convertidor de ObjetoBase* a Contrato*
		r = dynamic_cast <Plaza*>(listP->getElemento(i));
		if (r) {
			p = r->getPuesto();
			if (p->getCodigo() == cod) {
				return r;
				break;
			}
		}
	}
	return r;
}

Lista* Empresa::getContrato_Puesto(string cod) {
	Lista *list = new Lista();
	Contrato *c;
	Puesto *p;
	for (int i = 0; i < listC->getK(); i++) {
		//Convertidor de ObjetoBase* a Contrato*
		c = dynamic_cast <Contrato*>(listC->getElemento(i));
		if (c) {
			p = c->getPuesto();
			if (p) {
				if (p->getCodigo() == cod) {
					list->insertarInicio(c);
				}
			}
		}
	}
	return list;
}

bool Empresa::eliminarPuesto(string cod) {
	for (int i = 0; i < listP->getK(); i++) {
		Puesto *p = dynamic_cast <Puesto*>(listP->getElemento(i));
		if (p) {
			if (p->getCodigo() == cod) {
				listP->eliminar(i);
				return true;
			}
		}
	}
	return false;
}