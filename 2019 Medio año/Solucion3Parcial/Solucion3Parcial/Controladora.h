#pragma once
#include"Departamento.h"
#include"Empleado.h"
#include<iostream>
#include<sstream>
#include<fstream>
int iniciar() {
	//Creamos la coleccion inicial de departamentos
	Departamento* Departamentos[8];
	//insertamos los departamentos desde el archivo departamentos
	ifstream entrada("../departamentos.txt");
	int i = 0;
	string depa;
	if (entrada.good()) {
		while (!entrada.eof()) {
			getline(entrada, depa);
			Departamentos[i] = new Departamento(depa);
			i++;
		}
	}
	entrada.close();
	//Procedemos a leer el archivo de empleados y se busca el departamento donde van y se insertan
	entrada.open("../empleados.txt");
	if (entrada.good()) {
		string cedula, nombre, depto, categor;
		int categoria;
		Departamento* departamento = NULL;
		while (!entrada.eof()) {//723719	José	Gerencia    38
			getline(entrada, cedula, '\t');
			getline(entrada, nombre, '\t');
			getline(entrada, depto, '\t');
			getline(entrada, categor);
			if (!cedula.empty() && !nombre.empty() && !depto.empty() && !categor.empty()) {
				stringstream r(categor);
				r >> categoria;
				for (int a = 0; a < i; a++) {
					if (Departamentos[a]->getNombre() == depto) {
						departamento = Departamentos[a];
						break;
					}
				}
				if (departamento) {
					departamento->agregar(new Empleado(cedula, nombre, departamento, categoria));
				}
			}
			departamento = NULL;
		}
	}
	entrada.close();
	//finalmente acomodamos la jerarquia y se llama al metodo que calcula todos los salarios
	Departamento* depaBanco = new Departamento("Banco");
	Departamento* depaMantenimiento = depaBanco;
	Departamento* depaMantenimientoDiurno = depaBanco;
	Departamento* depaMantenimientoNocturno = depaBanco;
	Departamento* depaRRHH = depaBanco;
	Departamento* depaGerencia = depaBanco;
	Departamento* depaCajas = depaBanco;
	Departamento* depaAdministracion = depaBanco;
	// Para hacer la jerarquia es necesario saber el nombre del departamento por ello utilizamos variables con los mismos nombres
	for (int a = 0; a < i; a++) {
		if (Departamentos[a]->getNombre() == "Mantenimiento") {
			depaMantenimiento = Departamentos[a];
			//cout << depaMantenimiento->getNombre();
		}
		else {
			if (Departamentos[a]->getNombre() == "Mantenimiento (turno diurno)") {
				depaMantenimientoDiurno = Departamentos[a];
				//cout << depaMantenimientoDiurno->getNombre();
			}
			else {
				if (Departamentos[a]->getNombre() == "Mantenimiento (turno nocturno)") {
					depaMantenimientoNocturno = Departamentos[a];
					//cout << depaMantenimientoNocturno->getNombre();
				}
				else {
					if (Departamentos[a]->getNombre() == "RRHH") {
						depaRRHH = Departamentos[a];
						//cout << depaRRHH->getNombre();
					}
					else {
						if (Departamentos[a]->getNombre() == "Gerencia") {
							depaGerencia = Departamentos[a];
							//cout << depaGerencia->getNombre();
						}
						else {
							if (Departamentos[a]->getNombre() == "Cajas") {
								depaCajas = Departamentos[a];
								//cout << depaCajas->getNombre();
							}
							else {
								if (Departamentos[a]->getNombre() == "Administracion") {
									depaAdministracion = Departamentos[a];
									//cout << depaAdministracion->getNombre();
								}
								else {
									cout << "NO LO ENCONTRE" << Departamentos[a]->getNombre() << endl;
									system("pause");
								}
							}
						}
					}
				}
			}
		}
	}
	//Hacemos la jerarquia
	depaMantenimiento->agregar(depaMantenimientoDiurno);
	depaMantenimiento->agregar(depaMantenimientoNocturno);

	depaAdministracion->agregar(depaMantenimiento);
	depaAdministracion->agregar(depaCajas);

	depaBanco->agregar(depaAdministracion);
	depaBanco->agregar(depaGerencia);
	depaBanco->agregar(depaRRHH);

	// Mostramos el organigrama por consola
	cout << depaBanco->toString(1);
	//Llamamos el metodo de gastos
	cout << "El Gasto total es de: " << depaBanco->gastoPlanilla();
	cin.get();
	return 0;
}