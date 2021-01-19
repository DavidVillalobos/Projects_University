#include "control.h"

Control::Control() {
	gym = new Gimnasio*[3];
	for (int i = 0; i < 3;i++) {
		gym[i] = NULL;
	}
	menuAdministrador();
	iniciar();
}
void Control::iniciar() {
	bool bandera = true; 
	while (bandera) {
		setColor(15);
		system("cls");
		cout << " 1) Comprar\n";
		cout << " 2) Administrador\n";
		cout << " 3) Salir\n";
		cout << "digita una opcion: ";
		switch (leerInt()) {
		case 1: { Compra(); break; }
		case 2: {
			cout << "Para acceder al menu administrador debe ingresar la contrase\244a: ";
			string contra; cin >> contra;
			if (contra == "admin") {
				menuAdministrador();
			}
			else {
				cout << "Contrase\244a incorrecta vuelva a intentarlo\n"; Sleep(2000);
			}
			break; }
		case 3: {bandera = false; break; }
		}
	}
}
void Control::Compra() {
	system("cls");
	cout << "CONCIERTO NAVIDE\245O\n"; limpiarBuffer();
	cout << "Digite su nombre: "; string nom = leerString();
	cout << "  DIAS DEL CONCIERTO\n";
	for (int i = 0; i<3;i++){
	cout << i+1 << ") " << gym[i]->getDia() << " a las " << gym[i]->getHora()<<"\n";
	}
	cout << "Digite el un numero: "; int dia = leerInt() - 1;
	if (gym[dia]->getCantidad() < gym[dia]->getTamanno()) {
		bool bandera = true; int aux = 0;
		for (int i = 0; i < gym[dia]->getCantidad();i++) {
			if (gym[dia]->getTiquete(i)->getNombre()==nom) {
				aux++;
			}
		}
		if (aux>=5) {
			bandera = false;
			cout << "Lo sentimos no se puede comprar mas de 5 asientos por persona";
			Sleep(2000);
		}
		while (bandera) {
			system("cls");
			int col= gym[dia]->getColumnas();int fil=gym[dia]->getFilas();
			gym[dia]->toStringMatriz(5,5);
			menuSeleccionAsiento(5,5,fil,col);
			if (gym[dia]->getAsiento(fil - 1, col - 1)) {
				string columna = conLetraNum(col-1);
				int precio=gym[dia]->getPrecioBoleto();
				bool tipo = false; if (fil < 20) { 
					tipo = true; 
					precio = precio + (precio * 0.5); 
				}
				string asiento = columna + "-" +convertirString(fil);
				int Hora, Segundo;
				//time_t t = time(NULL);
				//struct tm today = *localtime_s;
				Hora = 18;
				Segundo = 50;
				string sHora = convertirString(Hora);
				sHora += ":"+ convertirString(Segundo);
				(Hora > 12) ? Hora-= 12, sHora += " pm": sHora += " am";
				Tiquete *nuevo = new Tiquete(nom,asiento,gym[dia]->getDia(),gym[dia]->getHora(),precio,gym[dia]->getPrecioImpresion(),tipo,sHora); 
				precio = precio + (precio * 0.13);
				nuevo->setPrecio(precio);
				//se crea con todos los atributos
				system("cls");
			    imprimeString(nuevo->toString()); //mostramos su tiquete
				cout << "\250Desea confirmar su compra?\n";
				cout << " 1) Si\n";
				cout << " 2) No\n";
				cout << "Digita un numero: ";
				if (leerInt()==1) {
					gym[dia]->insertarTiquete(nuevo); //se llama un metodo que inserte el tiquete nuevo
					gym[dia]->setAsiento(fil - 1, col - 1, false);

					cout << "Su compra ha sido realizada con exito\n\n";
					Sleep(1500);
				}
				else {
					delete nuevo; // borramos la memoria del tiquete que no quiere
				}
				bandera = false;
			}
			else {
				cout << "Lo sentimos este asiento se encuentra ocupado, elige otro\n\n";
				Sleep(2000);
			}
		}
	}
	else {
		cout << " Lo sentimos, los boletos para este concierto se encuentran agotados  \250Que deseas hacer?\n";
		cout << "1) Elegir otro Concierto\n";
		cout << "2) Salir\n";
		cout << "Digite un numero"; int opcion = leerInt();
		if (opcion==1) {
			Compra();
		}
	}
}
void Control::menuAdministrador() {
	if (gym[0]!=NULL && gym[1] != NULL && gym[2] != NULL) {
		int dia = 4;
		do {
			system("cls");
			cout << "MENU ADMINISTRADOR\n";
			cout << "  SELECCIONE UN CONCIERTO\n";
			for (int i = 0; i < 3; i++) {
				cout << i + 1 << ") " << gym[i]->getDia() << " a las " << gym[i]->getHora() << "\n";
			}
			cout << "4)Salir\n";
			cout << "Digite un numero: ";  dia = leerInt() - 1;
			if (dia != 3) {
				bool bandera = true;
				do {
					system("cls");
					cout << "MENU DE MODIFICACION DEL CONCIERTO " << gym[dia]->getDia() << " a las " << gym[dia]->getHora() << "\n";
					cout << "1) Cambiar Dia\n";
					cout << "2) Cambiar Hora\n";
					cout << "3) Cambiar Precio de los boletos\n";
					cout << "4) Cambiar Costo de Impresion\n";
					cout << "5) Ver Tiquetes Vendidos\n";
					cout << "6) Visualizar Distribucion de asientos\n";
					cout << "7) Visualizar Distribucion de tiquetes por asiento\n";
					cout << "8) Salir\n";
					cout << "Digita un numero: "; int admin = leerInt();
					switch (admin) {
					case 1: {
						cout << "Digita el nuevo dia :"; string nuevoDia = leerString();
						gym[dia]->setDia(nuevoDia);
						cout << "El dia ha sido cambiado con Exito"; Sleep(2000);
						break; }
					case 2: {
						cout << "Digita la nuevo hora:"; string nuevoHora = leerString();
						gym[dia]->setHora(nuevoHora);
						cout << "La hora ha sido cambiado con Exito"; Sleep(2000);
						break; }
					case 3: {
						cout << "Digita el nuevo precio de los boletos:"; int nuevoPrecio = leerInt();
						gym[dia]->setPrecioBoleto(nuevoPrecio);
						for (int i = 0; i < gym[dia]->getCantidad(); i++) {
							cout << "El precio anterior es" << gym[dia]->getTiquete(i)->getPrecio() << "\n";
							if (gym[dia]->getTiquete(i)->getTipo()) {
								nuevoPrecio = nuevoPrecio + nuevoPrecio * 0.5;
								cout << "El Nuevo precio con VIP " << nuevoPrecio << "\n";
							}
							nuevoPrecio = nuevoPrecio + nuevoPrecio * 0.13;
							cout << "El Nuevo precio con Impuesto " << nuevoPrecio << "\n";
							gym[dia]->getTiquete(i)->setPrecio(nuevoPrecio);
						}
						system("pause");
						cout << "El precio ha sido cambiado con Exito"; Sleep(2000);
						break; }
					case 4: {
						cout << "Digita el nuevo precio de impresion de los boletos:"; int nuevoPrecioImpresion = leerInt();
						gym[dia]->setPrecioImpresion(nuevoPrecioImpresion);
						for (int i = 0; i < gym[dia]->getCantidad(); i++) {
							gym[dia]->getTiquete(i)->setPrecioImpresion(nuevoPrecioImpresion);
						}
						cout << "El precio ha sido cambiado con Exito"; Sleep(2000);
						break; }
					case 5: {system("cls"); imprimeString(gym[dia]->toStringTiquetes()); imprimeString("\n\n  "); system("pause"); break; }
					case 6: {system("cls"); gym[dia]->toStringMatriz(5, 5); setColor(15); imprimeString("\n\n  "); system("pause"); break; }
							cout << "6) Visualizar Distribucion de asientos\n";
					case 7: {bool aux = true;
						while (aux) {
							system("cls");
							int fil = gym[dia]->getFilas(); int col = gym[dia]->getColumnas();
							cout << "\n\n        SELECCIONA UN ESPACIO DEL CONCIERTO";
							gym[dia]->toStringMatriz(5, 5);
							menuSeleccionAsiento(5, 5, fil, col);
							if (!gym[dia]->getAsiento(fil - 1, col - 1)) {
								string asiento = conLetraNum(col - 1) + convertirString(fil);
								Tiquete *encontrado = gym[dia]->buscarTiquete(asiento); system("cls");
								cout << "ESTE ASIENTO ESTA FACTURADO A NOMBRE DE " << encontrado->getNombre() << "\n";
								cout << "       FACTURA\n" << encontrado->toString() << "\n\n    "; system("pause");
								aux = false;
							}
							else {
								imprimeString("Este Asiento aun no se ha vendido, \250Que deseas hacer?\n");
								cout << "1)Elegir otro\n";
								cout << "2)Salir\n";
								if (leerInt() == 2) {
									aux = false;
								}
							}
						}
						break; }
					case 8: {bandera = false; break; }
					}
					system("cls");
				} while (bandera);
			}
		} while (dia != 3);
	}
	else {
		gym[0] = new Gimnasio(20, 25,0, 0, " ", " ");
		gym[1] = new Gimnasio(25, 40, 0, 0, " ", " ");
		gym[2] = new Gimnasio(40, 50, 0, 0, " ", " ");
		imprimeString("Para iniciar el programa debes ingresar los datos de todos los conciertos\n");
		int espacios = 500; int filas=25; int columnas = 20;
		for (int i = 0; i < 3;i++) {
			imprimeString("Concierto "); imprimeInt(i + 1); imprimeString(" Con capacidad para "); 
			imprimeInt(espacios);imprimeString(" personas\n");
			imprimeString("Ingrese la fecha: "); string fecha = leerString();
			imprimeString("Ingrese la hora: "); string hora = leerString();
			imprimeString("Ingrese el precio del boleto: "); int precio = leerInt();
			imprimeString("Ingrese el costo de impresion de cada boleto: "); int costoImpresion = leerInt();
			gym[i]->setDia(fecha);
			gym[i]->setDia(fecha);
			gym[i]->setPrecioBoleto(precio);
			gym[i]->setPrecioImpresion(costoImpresion);
			espacios *= 2;
			imprimeString(" El concierto ha sido ingresado con exito\n"); Sleep(1500); limpiarBuffer();
		}
	}
}