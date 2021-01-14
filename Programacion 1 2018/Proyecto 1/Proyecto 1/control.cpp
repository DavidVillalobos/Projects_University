#include "control.h"

control::control() {
	hang =new hangar();
	colR = new coleccionRuta();
	colV = new coleccionVuelo();
}

void control::menuPrincipal() {//MENU PRINCIPAL
	color(15); imprimeString("\n\n                      AERO-VIAJES");
	int salida = 3; int c = 14;
	do {
		int menu = 4;
		do {
			color(c); imprimeString("\n\n        같같같같같같같같같같같같같같같같같같같같\n");
			imprimeString("        같                                    같\n");
			imprimeString("        같           "); color(15); imprimeString("MEN\351 PRINCIPAL"); color(c); imprimeString("           같\n");
			imprimeString("        같                                    같\n");
			imprimeString("        같       "); color(15); imprimeString("1)Pasajero"); color(c); imprimeString("                   같\n");
			imprimeString("        같       "); color(15); imprimeString("2)Administrador"); color(c); imprimeString("              같\n");
			imprimeString("        같       "); color(15); imprimeString("3)Salir"); color(c); imprimeString("                      같\n");
			imprimeString("        같                                    같\n");
			imprimeString("        같같같같같같같같같같같같같같같같같같같같\n");
			color(15); imprimeString("\n          Digite la acci\242n que desea realizar: "); menu = leerInt();
			switch (menu) {
			case 1: {limpiaPantalla(); menuPasajero(); break; }
			case 2: {
				for (int cont = 5; cont > 0; cont--) {
					imprimeString("\n          Para accesar a GESTI\340N ADMINISTRADOR ,debe ingresar la contrase\244a \n");
					imprimeString("           tiene "); imprimeInt(cont); imprimeString(" intentos");
					imprimeString("\n             Contrase\244a: ");
					string resp = leerString();
					if (resp == "admin") {
						limpiaPantalla(); menuAdministrador(); cont = 0;
					}
					else {
						imprimeString("\n\n              	Contrase\244a incorrecta, int\202ntalo de nuevo\n");
						Sleep(1000);limpiaPantalla(); 
					}
				}
				break;
			}
			case 3: {break; }
			default: {opcionIncorrecta(); break; }
			}
			limpiaPantalla();
		} while (menu != 3);
		color(c); imprimeString("\n\n     같같같같같같같같같같같같같같같같같같같같\n");
		imprimeString("     같                                    같\n");
		imprimeString("     같    "); color(15); imprimeString("Est\240 seguro que desea salir"); color(c); imprimeString("     같\n");
		imprimeString("     같                                    같\n");
		imprimeString("     같     "); color(15); imprimeString("1)S\241"); color(c); imprimeString("                           같\n");
		imprimeString("     같     "); color(15); imprimeString("2)No"); color(c); imprimeString("                           같\n");
		imprimeString("     같                                    같\n");
		imprimeString("     같같같같같같같같같같같같같같같같같같같같\n");
		color(15); imprimeString("\n      Digite la opci\242n que desea: ");
		salida = leerInt();
		switch (salida) {
		case 1: {delete hang;delete colV;delete colR;break; }
		case 2: {break; }
		default: {opcionIncorrecta(); break; }
		}
		limpiaPantalla();
	} while (salida != 1);
}

void control::menuPasajero() {
	vuelo *auxV;
	int menu = 4, c = 14;
	do {
		color(c); imprimeString("\n\n     같같같같같같같같같같같같같같같같같같같같같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같          "); color(15); imprimeString("GESTI\340N TIQUETES"); color(c); imprimeString("            같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같     "); color(15); imprimeString("1)Comprar"); color(c); imprimeString("                        같\n");
		imprimeString("     같     "); color(15); imprimeString("2)Eliminar"); color(c); imprimeString("                       같\n");
		imprimeString("     같     "); color(15); imprimeString("3)Volver al men\243 principal"); color(c); imprimeString("       같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같같같같같같같같같같같같같같같같같같같같같\n");
		color(15); imprimeString("\n      Digite la accion que desea realizar: "); menu = leerInt(); limpiaPantalla();
		switch (menu) {
		case 1: {
			colV->toString();
			imprimeString("\n\n Digite el ID del vuelo en el que desea comprar:"); string idV = leerString();
			int aux = colV->buscarVuelo(idV);
			if (aux != -1) {
				auxV = colV->getVuelo(aux);
				imprimeString(" Digite su nombre:"); string nombre = leerString();
				imprimeString(" Digite su c\202dula: "); string idpers = leerString();
				pasajero *pasjNuevo = new pasajero(nombre, idpers);
				colV->getVuelo(aux)->mostrarAsientos();
				imprimeString("\n\n Digite la fila (letra) que desea:"); char fil = leerChar();
				if (auxV->LetraAsiento(fil) != -1) {
					imprimeString(" Digite la columna (n\243mero) que desea:"); int col = leerInt();
					if (auxV->getAv()->getCol() == 6) {
						if ((col < 30) || (col >= 0)) {
							int cantActual = auxV->getCantTyP();
							ruta *auxR = auxV->getRut();
							string nombreRuta = auxR->getOrigen() + " - " + auxR->getDestino();
							string hora =  "";
							string minuto = "";
							hora = static_cast<std::ostringstream*>(&(std::ostringstream() << auxV->getHhoraSalida()))->str();
							minuto = static_cast<std::ostringstream*>(&(std::ostringstream() << auxV->getMhoraSalida()))->str();
							string idTiq = "";
							idTiq = static_cast<std::ostringstream*>(&(std::ostringstream() << cantActual))->str();
							string hsal_lleg = "";
							hsal_lleg= static_cast<std::ostringstream*>(&(std::ostringstream() << hora + " : " + minuto))->str();
							tiquete *tiqNuevo = new tiquete(idTiq, idV, nombreRuta,hsal_lleg, fil, auxV->getPrecio(), col, pasjNuevo);
							if (auxV->insertarTiquete(tiqNuevo)==true) {
								imprimeString("\n\n Este es t\243 tiquete:\n\n");
								auxV->mostrarTiquete(idTiq);
								pausa();
							}
						}
						else {
							imprimeString("\n La columna que ingres\242 no existe");
							Sleep(2000);
						}
					}
					else {
						if ((col < 25) || (col >= 0)) {
							int cantActual = auxV->getCantTyP();
							ruta *auxR = auxV->getRut();
							string nombreRuta = auxR->getOrigen() + " - " + auxR->getDestino();
							string  hora = auxR->getHduracion() + ":" + auxR->getMduracion();
							string idTiq = "";
							idTiq = static_cast<std::ostringstream*>(&(std::ostringstream() << cantActual))->str();
							tiquete *tiqNuevo = new tiquete(idTiq, idV, nombreRuta, hora, fil, auxV->getPrecio(), col, pasjNuevo);
							if (auxV->insertarTiquete(tiqNuevo) == true) {
								imprimeString("\n\n Este es t\243 tiquete:\n\n");
								auxV->mostrarTiquete(idTiq);
								pausa();
							}
						}
						else {
							imprimeString("\n La columna que ingres\242 no existe");
							Sleep(2000);
						}
					}
				}
				else {
					imprimeString("\n La fila que ingres\242 no existe");
					Sleep(2000);
				}
			}
			else {
				imprimeString("\n El vuelo no existe");
				Sleep(2000);
			}
			break; }
		case 2: {imprimeString("\n\n Digite el ID del vuelo:"); string idV = leerString();
			int aux = colV->buscarVuelo(idV);
			string idT;
			if (aux != -1) {
				auxV = colV->getVuelo(aux);
				imprimeString(" Digite el n\243mero del tiquete:"); idT = leerString();
				if (auxV->buscarTiquete(idT)!=-1) {
					auxV->eliminarTiquete(idT);
				}
				else {
					imprimeString(" El tiquete no se encuentra registrado en el vuelo");
					Sleep(2000);
				}
			}
			else {
				imprimeString("\n El vuelo no existe");
				Sleep(2000);
			}
			break; }
		case 3: {break; }
		default: {opcionIncorrecta(); break; }
		}
		limpiaPantalla();
	} while (menu != 3);
}

void control::menuAdministrador() {
	int menu = 5, c = 14;
	do {
		color(c);
		imprimeString("\n\n     같같같같같같같같같같같같같같같같같같같같같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같          "); color(15); imprimeString("GESTI\340N ADMINISTRADOR"); color(c); imprimeString("       같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같     "); color(15); imprimeString("1)Gesti\242n Avi\242n"); color(c); imprimeString("                  같\n");
		imprimeString("     같     "); color(15); imprimeString("2)Gesti\242n Ruta"); color(c); imprimeString("                   같\n");
		imprimeString("     같     "); color(15); imprimeString("3)Gesti\242n Vuelo"); color(c); imprimeString("                  같\n");
		imprimeString("     같     "); color(15); imprimeString("4)Volver al men\243 principal"); color(c); imprimeString("       같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같같같같같같같같같같같같같같같같같같같같같\n");
		color(15); imprimeString("\n      Digite la acci\242n que desea realizar: ");
		menu = leerInt(), limpiaPantalla();
		switch (menu) {
		case 1: {gestionAvion(); break; }
		case 2: {gestionRuta(); break; }
		case 3: {gestionVuelo(); break; }
		case 4: {break; }
		default: {opcionIncorrecta(); break; }
		}
		limpiaPantalla();
	} while (menu != 4);
}

void control::gestionRuta() {
	int menu = 7, c = 14;
	do {
		color(c);
		imprimeString("\n\n     같같같같같같같같같같같같같같같같같같같같같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같            "); color(15); imprimeString("GESTI\340N RUTAS"); color(c); imprimeString("             같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같     "); color(15); imprimeString("1)Ingresar nueva ruta"); color(c); imprimeString("            같\n");
		imprimeString("     같     "); color(15); imprimeString("2)Visualizar ruta"); color(c); imprimeString("                같\n");
		imprimeString("     같     "); color(15); imprimeString("3)Modificar ruta"); color(c); imprimeString("                 같\n");
		imprimeString("     같     "); color(15); imprimeString("4)Eliminar ruta"); color(c); imprimeString("                  같\n");
		imprimeString("     같     "); color(15); imprimeString("5)Ver rutas disponibles"); color(c); imprimeString("          같\n");
		imprimeString("     같     "); color(15); imprimeString("6)Volver"); color(c); imprimeString("                         같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같같같같같같같같같같같같같같같같같같같같같\n");
		color(15); imprimeString("\n      Digite la acci\242n que desea realizar: ");
		menu = leerInt();
		switch (menu) {
		case 1: {string id, origen, destino; int hduracion, mduracion, escala;
			limpiaPantalla(); imprimeString("\n\n    Para ingresar una nueva ruta digite la siguiente informaci\242n\n\n");
			imprimeString("   ID: "), id = leerString();
			imprimeString("   Origen: "), origen = leerString();
			imprimeString("   Destino: "), destino = leerString();
			imprimeString("   Duraci\242n en horas: "); hduracion = leerInt();
			imprimeString("   Duraci\242n en minutos: "); mduracion = leerInt();
			imprimeString("   Cantidad de escalas: "), escala = leerInt();
			ruta *nueva = new ruta(id, origen, destino, hduracion, mduracion, escala);
			imprimeString("\n"); colR->insertarRuta(nueva); break; }
		case 2: {imprimeString("\n\n   Digite el ID de la ruta:"); string id = leerString(); colR->muestraRuta(id); break; }
		case 3: {limpiaPantalla(); modificarRuta(); break; }
		case 4: {imprimeString("\n\n   Digite el ID de la ruta:"); string id = leerString(); colR->eliminarRuta(id); break; }
		case 5: {limpiaPantalla(); imprimeString("\n\n    "); colR->toString(); pausa(); break; }
		case 6: {break; }
		default: {opcionIncorrecta(); break; }
		}
		limpiaPantalla();
	} while (menu != 6);
}

void control::gestionVuelo() {
	int menu = 7, c = 14;
	do {
		color(c);
		imprimeString("\n\n     같같같같같같같같같같같같같같같같같같같같같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같            "); color(15); imprimeString("GESTI\340N VUELOS"); color(c); imprimeString("            같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같     "); color(15); imprimeString("1)Ingresar nuevo vuelo"); color(c); imprimeString("           같\n");
		imprimeString("     같     "); color(15); imprimeString("2)Visualizar vuelo"); color(c); imprimeString("               같\n");
		imprimeString("     같     "); color(15); imprimeString("3)Modificar vuelo"); color(c); imprimeString("                같\n");
		imprimeString("     같     "); color(15); imprimeString("4)Eliminar vuelo"); color(c); imprimeString("                 같\n");
		imprimeString("     같     "); color(15); imprimeString("5)Ver vuelos disponibles"); color(c); imprimeString("         같\n");
		imprimeString("     같     "); color(15); imprimeString("6)Volver"); color(c); imprimeString("                         같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같같같같같같같같같같같같같같같같같같같같같\n");
		color(15); imprimeString("\n      Digite la acci\242n que desea realizar: ");
		menu = leerInt();
		switch (menu) {
		case 1: {
			limpiaPantalla(); imprimeString("\n\n    Para ingresar un nuevo vuelo digite la siguiente informaci\242n\n\n");
			imprimeString("   ID del Vuelo: "); string id = leerString();
			imprimeString("   ID del Avi\242n: "); string idAvion = leerString();
			int auxA = hang->buscarAvion(idAvion);
			if (auxA != -1) {
				imprimeString("   ID de la Ruta: "); string idrut = leerString();
				int auxR = colR->buscarRuta(idrut);
				if (auxR != -1) {
					imprimeString("   Aereopuerto de llegada: "); string aeroLlegada = leerString();
					imprimeString("   Aereopuerto de salida: "); string aeroSalida = leerString();
					imprimeString("   Fecha con formato (DD/MM/AAAA) : "); string fecha = leerString();
					imprimeString("   Piloto: "); string piloto = leerString();
					imprimeString("   Hora de salida, favor utilizar la hora Militar (00:00 - 24:00)\n");
					imprimeString("   Hora: "); int hSalida = leerInt();
					imprimeString("   Minuto: "); int mSalida = leerInt();
					imprimeString("   Precio del tiquete: "); int precio = leerInt();
					vuelo *vNuevo = new vuelo(id, fecha, aeroLlegada, aeroSalida, piloto, hSalida, mSalida, precio, hang->getAvion(auxA), colR->getRuta(auxR));
					colV->insertarVuelo(vNuevo);
				}
				else {
					imprimeString("\n La Ruta no est\240 registrada"); Sleep(1000);
				}
			}
			else {
				imprimeString("\n El Avi\242n no est\240 registrado"); Sleep(1000);
			}
			break; }
		case 2: {imprimeString("\n\n   Digite el ID del Vuelo:"); string id = leerString();  int aux = colV->buscarVuelo(id) ;
			if (aux != -1) {
				int vuelo = 5;
				do {limpiaPantalla(); colV->mostrarVuelo(id);
					color(c); imprimeString("\n\n        같같같같같같같같같같같같같같같같같같같같같\n");
					imprimeString("        같                                      같\n");
					imprimeString("        같          "); color(15); imprimeString("VISUALIZAR VUELO"); color(c); imprimeString("            같\n");
					imprimeString("        같                                      같\n");
					imprimeString("        같      "); color(15); imprimeString("1)Ver lista de pasajeros"); color(c); imprimeString("        같\n");
					imprimeString("        같      "); color(15); imprimeString("2)Ver lista de tiquetes"); color(c); imprimeString("         같\n");
					imprimeString("        같      "); color(15); imprimeString("3)Ver distribuci\242n de asientos"); color(c); imprimeString("  같\n");
					imprimeString("        같      "); color(15); imprimeString("4)Salir"); color(c); imprimeString("                         같\n");
					imprimeString("        같                                      같\n");
					imprimeString("        같같같같같같같같같같같같같같같같같같같같같\n");
					color(15); imprimeString("\n          Digite la acci\242n que desea realizar: "); vuelo = leerInt();
					switch (vuelo) {
					case 1: {colV->getVuelo(aux)->listaPasajeros(); pausa(); break; }
					case 2: {colV->getVuelo(aux)->listaTiquetes(); pausa(); break; }
					case 3: {colV->getVuelo(aux)->mostrarAsientos(); pausa(); break; }
					case 4: {break; }
					default: {opcionIncorrecta(); break; }
					}limpiaPantalla();
				} while (vuelo != 4);
			}
			else {
				imprimeString("\n El vuelo que ha ingresado no se encuentra registrado en el sistema\n");
				Sleep(1000);
			}
			break;
		}
		case 3: {limpiaPantalla(); modificarVuelo(); break; }
		case 4: {imprimeString("\n\n   Digite el ID del Vuelo:"); string id = leerString(); colV->eliminarVuelo(id);
			break; }
		case 5: {limpiaPantalla(); imprimeString("\n\n    "); colV->toString(); pausa(); break; }
		case 6: {break; }
		default: {opcionIncorrecta(); break; }
		}
		limpiaPantalla();
	} while (menu != 6);
}

void control::gestionAvion() {
	int menu = 5, c = 14;
	do {
		color(c);
		imprimeString("\n\n     같같같같같같같같같같같같같같같같같같같같같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같            "); color(15); imprimeString("MEN\351 AVI\340N"); color(c); imprimeString("                같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같     "); color(15); imprimeString("1)Ingresar nuevo avi\242n"); color(c); imprimeString("           같\n");
		imprimeString("     같     "); color(15); imprimeString("2)Visualizar Avi\242n"); color(c); imprimeString("               같\n");
		imprimeString("     같     "); color(15); imprimeString("3)Modificar Avi\242n"); color(c); imprimeString("                같\n");
		imprimeString("     같     "); color(15); imprimeString("4)Eliminar Avi\242n"); color(c); imprimeString("                 같\n");
		imprimeString("     같     "); color(15); imprimeString("5)Ver aviones disponibles"); color(c); imprimeString("        같\n");
		imprimeString("     같     "); color(15); imprimeString("6)Volver"); color(c); imprimeString("                         같\n");
		imprimeString("     같                                      같\n");
		imprimeString("     같같같같같같같같같같같같같같같같같같같같같\n");
		color(15); imprimeString("\n      Digite la acci\242n que desea realizar: ");
		menu = leerInt();
		switch (menu) {
		case 1: {string id, modelo, marca; int anno; char tam;
			limpiaPantalla(); imprimeString("\n\n    Para ingresar un nuevo avi\242n digite la siguiente informaci\242n\n\n");
			imprimeString("   ID: "); id = leerString();
			imprimeString("   Modelo: "); modelo = leerString();
			imprimeString("   Marca: "); marca = leerString();
			imprimeString("   A\244o: "); anno = leerInt();
			imprimeString("   Tama\244o del Avion\n");
			imprimeString("   G para grande y P para peque\244o: "); bool aux = false;
			while (aux != true) {
				tam = leerChar();
				if (tam == 'G' || tam == 'g' || tam == 'P' || tam == 'p') {
					limpiarBuffer(); aux = true;
				}
				else {
					imprimeString("\n  Este valor es incorrecto, por favor digita una de las opciones: G o P\n");
					limpiarBuffer(); aux = false;
				}
			}
			avion *nuevo = new avion(id, modelo, marca, anno, tam); hang->insertAvion(nuevo); break; }
		case 2: {imprimeString("\n\n   Digite el ID del Avi\242n:\n"); string id = leerString(); hang->muestraAvion(id); break; }
		case 3: {limpiaPantalla(); modificarAvion(); break; }
		case 4: {imprimeString("\n\n   Digite el ID del avi\242n:"); string id = leerString(); hang->eliminarAvion(id); break; }
		case 5: {limpiaPantalla(); imprimeString("\n\n    "); hang->toString(); pausa(); break; }
		case 6: {break; }
		default: {opcionIncorrecta(); break; }
		}
		limpiaPantalla();
	} while (menu != 6);
}

void control::modificarAvion() {
	avion *auxA;
	int menu = 6, aux = 0, c = 14;
	imprimeString("   Digite el ID del avi\242n: "); string id = leerString();
	aux = hang->buscarAvion(id);
	if (aux != -1) {
		auxA = hang->getAvion(aux);
		do {
			color(c);
			imprimeString("\n\n     같같같같같같같같같같같같같같같같같같같\n");
			imprimeString("     같                                  같\n");
			imprimeString("     같         "); color(15); imprimeString("MODIFICAR AVI\340N"); color(c); imprimeString("          같\n");
			imprimeString("     같                                  같\n");
			imprimeString("     같       "); color(15); imprimeString("1)Cambiar ID"); color(c); imprimeString("               같\n");
			imprimeString("     같       "); color(15); imprimeString("2)Cambiar A\244o"); color(c); imprimeString("              같\n");
			imprimeString("     같       "); color(15); imprimeString("3)Cambiar Modelo"); color(c); imprimeString("           같\n");
			imprimeString("     같       "); color(15); imprimeString("4)Cambiar Marca"); color(c); imprimeString("            같\n");
			imprimeString("     같       "); color(15); imprimeString("5)Volver"); color(c); imprimeString("                   같\n");
			imprimeString("     같                                  같\n");
			imprimeString("     같같같같같같같같같같같같같같같같같같같\n");
			color(15); imprimeString("\n      Digite la accion que desea realizar: ");
			menu = leerInt(); imprimeString("\n");
			switch (menu) {
			case 1: {imprimeString("   Digite la nueva identificaci\242n del avi\242n: "); string id = leerString(); auxA->setId(id); break; }
			case 2: {imprimeString("   Digite el a\244o del avi\242n: "); int anno = leerInt(); auxA->setAnno(anno); break; }
			case 3: {imprimeString("   Digite el modelo del avi\242n:"); string modelo = leerString(); auxA->setModelo(modelo); break; }
			case 4: {imprimeString("   Digite la marca del avi\242n:"); string marca = leerString(); auxA->setMarca(marca); break; }
			case 5: {break; }
			default: {opcionIncorrecta(); break; }
			}
			limpiaPantalla();
		} while (menu != 5);
	}
	else { imprimeString("\n El n\243mero de identificaci\242n no se encuentra registrado"); Sleep(2000); }
}

void control::modificarVuelo() {
	vuelo *auxV;
	int menu = 11, aux = 0, c = 14;
	string id;
	cout << "   Digite la identificaci\242n del Vuelo: " << endl;
	id = leerString();
	aux = colV->buscarVuelo(id);
	if (aux != -1) {
		auxV = colV->getVuelo(aux);
		do {
			color(c);
			imprimeString("\n\n     같같같같같같같같같같같같같같같같같같같같같\n");
			imprimeString("     같                                      같\n");
			imprimeString("     같           "); color(15); imprimeString("MODIFICAR VUELO"); color(c); imprimeString("            같\n");
			imprimeString("     같                                      같\n");
			imprimeString("     같   "); color(15); imprimeString("1)Cambiar ID"); color(c); imprimeString("                       같\n");
			imprimeString("     같   "); color(15); imprimeString("2)Cambiar Aereopuerto de llegada"); color(c); imprimeString("   같\n");
			imprimeString("     같   "); color(15); imprimeString("3)Cambiar Aereopuerto de salida"); color(c); imprimeString("    같\n");
			imprimeString("     같   "); color(15); imprimeString("4)Cambiar Piloto"); color(c); imprimeString("                   같\n");
			imprimeString("     같   "); color(15); imprimeString("5)Cambiar Precio"); color(c); imprimeString("                   같\n");
			imprimeString("     같   "); color(15); imprimeString("6)Cambiar Ruta"); color(c); imprimeString("                     같\n");
			imprimeString("     같   "); color(15); imprimeString("7)Cambiar Avion"); color(c); imprimeString("                    같\n");
			imprimeString("     같   "); color(15); imprimeString("8)Cambiar Fecha"); color(c); imprimeString("                    같\n");
			imprimeString("     같   "); color(15); imprimeString("9)Cambiar Hora"); color(c); imprimeString("                     같\n");
			imprimeString("     같   "); color(15); imprimeString("10)Volver"); color(c); imprimeString("                          같\n");
			imprimeString("     같                                      같\n");
			imprimeString("     같같같같같같같같같같같같같같같같같같같같같\n");
			color(15); imprimeString("\n      Digite la acci\242n que desea realizar: ");
			menu = leerInt(), imprimeString("\n");
			switch (menu) {
			case 1: {imprimeString("   Digite el nuevo ID: "); string id = leerString(); auxV->setId(id); break; }
			case 2: {imprimeString("   Digite el Aereopuerto de llegada: "); string aeropLlegada = leerString(); auxV->setAeroLlegada(aeropLlegada); break; }
			case 3: {imprimeString("   Digite el Aereopuerto de salida: "); string aeropSalida = leerString(); auxV->setAeroSalida(aeropSalida); break; }
			case 4: {imprimeString("   Digite el Piloto: "); string piloto = leerString(); auxV->setPiloto(piloto); break; }
			case 5: {imprimeString("   Digite el Precio del tiquete: "); int precio = leerInt(); auxV->setPrecio(precio); break; }
			case 6: {imprimeString("   Digite el ID de la Ruta: "); string idRut = leerString(); int aux = colR->buscarRuta(idRut);
				if (aux != -1) { auxV->setRut(colR->getRuta(aux)); }
				else { imprimeString("   Esta ruta no se encuentra registrada "); Sleep(1000); }
				break;
			}
			case 7: {imprimeString("   Digite el ID del Avion: "); string idAv = leerString(); int aux = hang->buscarAvion(idAv);
				if (aux != -1) { auxV->setAv(hang->getAvion(aux)); }
				else { imprimeString("   Este avion no se encuentra registrado "); Sleep(1000); }
				break;
			}
			case 8: {imprimeString("   Fecha con formato (DD/MM/AAAA): "); string fecha= leerString(); auxV->setFecha(fecha); break; }
			case 9: {
				imprimeString("   Hora de salida, favor utilizar la hora Militar (00:00 - 24:00)\n");
				imprimeString("   Hora: "); int hSalida = leerInt();
				imprimeString("   Minuto: "); int mSalida = leerInt();
				auxV->setHhoraSalida(hSalida);auxV->setHhoraLlegada();
				auxV->setMhoraSalida(mSalida);auxV->setMhoraLlegada();
				break; }
			case 10: {break; }
			default: {opcionIncorrecta(); break; }
			}
			limpiaPantalla();
		} while (menu != 10);
	}
	else { imprimeString("\n Este ID no se encuentra registrado en el sistema"); Sleep(1000); }
}

void control::modificarRuta() {
	ruta *auxR;
	int menu = 7; imprimeString("   Digite el ID de la Ruta: "); string id = leerString();
	int aux = colR->buscarRuta(id), c = 14;
	if (aux != -1) {
		auxR = colR->getRuta(aux);
		do {color(c);
			imprimeString("\n\n     같같같같같같같같같같같같같같같같같같같같\n");
			imprimeString("     같                                    같\n");
			imprimeString("     같          "); color(15); imprimeString("MODIFICAR RUTA"); color(c); imprimeString("            같\n");
			imprimeString("     같                                    같\n");
			imprimeString("     같     "); color(15); imprimeString("1)Cambiar ID"); color(c); imprimeString("                   같\n");
			imprimeString("     같     "); color(15); imprimeString("2)Cambiar Origen"); color(c); imprimeString("               같\n");
			imprimeString("     같     "); color(15); imprimeString("3)Cambiar Destino"); color(c); imprimeString("              같\n");
			imprimeString("     같     "); color(15); imprimeString("4)Cambiar Duraci\242n"); color(c); imprimeString("             같\n");
			imprimeString("     같     "); color(15); imprimeString("5)Cambiar cantidad de Escalas"); color(c); imprimeString("  같\n");
			imprimeString("     같     "); color(15); imprimeString("6)Volver"); color(c); imprimeString("                       같\n");
			imprimeString("     같                                    같\n");
			imprimeString("     같같같같같같같같같같같같같같같같같같같같\n");
			color(15); imprimeString("\n      Digite la acci\242n que desea realizar: ");
			menu = leerInt(), imprimeString("\n");
			switch (menu) {
			case 1: {imprimeString("   Digite el nuevo ID: "); string iden = leerString(); auxR->setId(iden); break; }
			case 2: {imprimeString("   Digite el nuevo origen: "); string origen = leerString(); auxR->setOrigen(origen); break; }
			case 3: {imprimeString("   Digite el nuevo destino: "); string destino = leerString(); auxR->setDestino(destino); break; }
			case 4: {imprimeString("   Digite la  nueva duraci\242n, favor utilizar el formato militar (00:00 - 24:00) \n");
				imprimeString("   Horas: "); int hDuracion = leerInt(); auxR->setHduracion(hDuracion);
				imprimeString("   Minutos: "); int mDuracion = leerInt(); auxR->setMduracion(mDuracion);
				break; }
			case 5: {imprimeString("   Digite la nueva cantidad de escalas: "); int cant = leerInt(); auxR->setEscala(cant); break; }
			case 6: {break; }
			default: {opcionIncorrecta(); break; }
			}
			limpiaPantalla();
		} while (menu != 6);
	}
	else { imprimeString("\n Este ID no se encuentra registrado en el sistema\n"); Sleep(1000); }
}

control::~control() {}