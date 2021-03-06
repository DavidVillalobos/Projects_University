﻿#include "Fecha.h"
#include <stdio.h>
#include <time.h>

Fecha::Fecha(){
	Fecha local = horaLocal();
	dia = local.dia;
	mes = local.mes;
	anno = local.anno;
}

Fecha::Fecha(int dia, int mes, int anno): dia(dia), mes(mes), anno(anno){}

Fecha::~Fecha(){}

int Fecha::getDia(){ return dia; }

int Fecha::getMes(){ return mes; }

int Fecha::getAnno(){ return anno; }

void Fecha::setDia(int dia) { this->dia = dia; }

void Fecha::setMes(int mes) { this->mes = mes; }

void Fecha::setAnno(int anno) { this->anno = anno; }

string Fecha::toString(){
	stringstream s;
	s << dia << " de ";
	switch (mes) {
	case 1: { s << "Enero"; break; }
	case 2: { s << "Febrero"; break; }
	case 3: { s << "Marzo"; break; }
	case 4: { s << "Abril"; break; }
	case 5: { s << "Mayo"; break; }
	case 6: { s << "Junio"; break; }
	case 7: { s << "Julio"; break; }
	case 8: { s << "Agosto"; break; }
	case 9: { s << "Septiembre"; break; }
	case 10: { s << "Octubre"; break; }
	case 11: { s << "Noviembre"; break; }
	case 12: { s << "Diciembre"; break; }
	default: s << "Error"; break;
	}
	s << " de " << anno;
	return s.str();
}

ostream & operator<<(ostream &salida, Fecha *f){
	salida << f->toString();
	return salida;
}

Fecha Fecha::operator-(Fecha &f) {
	if (f.dia == 1) {
		f.dia += 30;
		this->mes += 1;
	}
	int dia = f.dia = this->dia;	
	if (f.mes == 1) {
		f.mes += 12;
		this->anno += 1;

	}
	int mes = f.mes = this->mes;
	int anno = f.anno = this->anno;
	return Fecha(dia, mes, anno);
}

Fecha Fecha::horaLocal() {
	time_t current_time;
	struct tm local_time;
	time(&current_time);
	localtime(&current_time);
	int year = local_time.tm_year + 1900;
	int mes = local_time.tm_mon + 1;
	int dia = local_time.tm_mday;
	return Fecha(dia,mes,year);
}

string Fecha::guardar(){
	stringstream s;
	s<< dia << L"/" << mes << L"/" << anno;
	return s.str();
}
