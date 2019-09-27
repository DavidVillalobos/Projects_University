#include "TipoPaciente.h"
#include "Paciente_General.h"
#include "Paciente_Pediatria.h"
#include "Paciente_Geriatria.h"
int solicitarEdad(int limiteInferior, int limiteSuperior=0) {
	int edad;
	bool bandera = true;
	while (bandera) {
		cout << "Introduzca la edad: ";
		cin >> edad;
		if (limiteSuperior!=0) {
			if (limiteInferior <= edad && edad <= limiteSuperior) {
				bandera = false;
			}
			else {
				cout << "La edad de este paciente no pertenece a este bloque\n";
				cout << "Introduza una edad entre " << limiteInferior << " y " << limiteSuperior << "\n";
			}
		}
		else {
			if (limiteInferior <= edad) {
				bandera = false;
			}
			else {
				cout << "La edad de este paciente no pertenece a este bloque\n";
				cout << "Introduza una edad mayor o igual a " << limiteInferior <<"\n";
			}
		}
	}
	cin.clear();
	cin.ignore(1024, '\n');
	return edad;
}
int leerInt() {
	int n;
	while (true) {
		if (cin >> n) {
			return n;
		}
		else {
			cout << "Este valor es incorrecto, por favor digita un NUMERO\n";
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}

}
void imprimeInt(int entero) { cout << entero; }
void imprimeString(string cadena) { cout << cadena; }
string leerString() {
	string cad;
	getline(cin, cad);
	return cad;
}
void main() {
	int cantidad, opcion, edad;
	string id, nombre, numeroTel, NomEncargado, ApeEncargado, NomTelefono, ocupacion, patrono;
	bool incapacidad;
	cout << "Para comenzar por favor digite el numero de pacientes del hospital: "; cantidad = leerInt();
	cout << "Por favor introduzca la siguiete informacion de los pacientes\n";
	TipoPaciente **hospital;
	hospital = new TipoPaciente*[cantidad];
	for (int i = 0; i < cantidad;i++) {
		hospital[i] = NULL;
		cout << "Tipo de paciente\n";
		cout << " 1) Peditria\n";
		cout << " 2) Medicina General\n";
		cout << " 3) Geriatria\n";
		cout << "Ingrese la informacion de paciente numero " << i + 1<<"\n";
			switch (leerInt()) {
			case 1: {
				cout << "Introduzca los datos del paciente de Pediatria\n";
				edad = solicitarEdad(0, 17);
				cout << "Cedula : "; id = leerString();
				cout << "Nombre : "; nombre = leerString();
				cout << "Numero de Telefono : "; numeroTel = leerString();
				cout << "Nombre del Encargado : "; NomEncargado = leerString();
				cout << "Apellidos del Encargado : "; ApeEncargado = leerString();
				cout << "Numero de Telefono del Encargado : "; NomTelefono = leerString();
				hospital[i] = new Paciente_Pediatria(NomEncargado, ApeEncargado, NomTelefono, edad, id, nombre, numeroTel);
				cout << "Paciente ["<<nombre<<"] ingresado con exito en el sistema\n";
				break; 
			}
			case 2: {
				cout << "Introduzca los datos del paciente de Medicina General\n";
				edad = solicitarEdad(18, 64);
				cout << "Cedula : "; id = leerString();
				cout << "Nombre : "; nombre = leerString();
				cout << "Numero de Telefono : "; numeroTel = leerString();;
				cout << "Ocupacion : "; ocupacion = leerString();
				cout << "Patrono: "; patrono = leerString();
				cout << " El paciente presenta incapacidad laboral\n";
				cout << "  0) No\n";
				cout << "  1) Si\n";
				incapacidad = leerInt();
				hospital[i] = new Paciente_General(ocupacion, patrono, incapacidad, edad, id, nombre, numeroTel);
				cout << "Paciente [" << nombre << "] ingresado con exito en el sistema\n";
				break; 
			}
			case 3: {
				cout << "Introduzca los datos del paciente de Pediatria\n";
				edad = solicitarEdad(65);
				cout << "Cedula : "; id = leerString();
				cout << "Nombre : "; nombre = leerString();
				cout << "Numero de Telefono : "; numeroTel = leerString();
				cout << "Nombre del Acompanante : "; NomEncargado = leerString();
				hospital[i] = new Paciente_Geriatria(NomEncargado, edad, id, nombre, numeroTel);
				cout << "Paciente [" << nombre << "] ingresado con exito en el sistema\n";
				break; 
			}
			default: {cout << "Error, Por favor solo digite valores del menu\n"; i--; break; }
			}
	}
	cout << "Los datos han sido ingresados con exito en el sistema\n";
	system("pause");
	for (int i = 0; i < cantidad;i++) {
		if (hospital[i] != NULL) {
			cout<<hospital[i]->toString();
		}
	}
	system("pause");
}