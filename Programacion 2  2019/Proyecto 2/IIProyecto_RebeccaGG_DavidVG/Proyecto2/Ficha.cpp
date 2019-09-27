#include "Ficha.h"

Ficha::Ficha(wchar_t simbolo) : simbolo(simbolo) {}

Ficha::~Ficha(){}

wchar_t Ficha::getSimbolo() { return simbolo; }

void Ficha::setSimbolo(wchar_t simbolo) { this->simbolo = simbolo; } // Cambia Cuando Corona
