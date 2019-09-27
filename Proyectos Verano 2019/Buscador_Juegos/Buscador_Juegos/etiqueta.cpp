#include "etiqueta.h"
etiqueta::etiqueta(string info, etiqueta *sig) { this->info = info; this->sig = sig; }
string etiqueta::getInfo() { return info; }
etiqueta* etiqueta::getSig() { return sig; }
void etiqueta::setInfo(string info) { this->info = info; }
void etiqueta::setSig(etiqueta* sig) { this->sig = sig; }
etiqueta::~etiqueta() {}