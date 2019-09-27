#ifndef GIMNASIO_H
#define GIMNASIO_H
#include "Tiquete.h"
class Gimnasio {
private:
	bool **asiento;
	int cantidad;
	int tamanno;
	int columna;
	int fila;
	string dia;
	string hora;
	Tiquete **vector;
	int precioBoleto;
	int precioImpresion;
public:
	Gimnasio(int,int,int,int,string,string);
	~Gimnasio();
	bool** getAsientos();
	bool getAsiento(int,int);
	void setAsiento(int,int,bool);
	int getCantidad();
	int getTamanno();
	int getColumnas();
	int getFilas();
	string getDia();
	string getHora();
	Tiquete* getTiquete(int);
	int getPrecioBoleto();
	int getPrecioImpresion();
	void setCantidad(int);
	void setDia(string);
	void setHora(string);
	void setPrecioBoleto(int);
	void setPrecioImpresion(int);
	bool insertarTiquete(Tiquete*);
	void toStringMatriz(int,int);
	string toStringTiquetes();
	Tiquete * buscarTiquete(string);
};
#endif // !Gimnasio
