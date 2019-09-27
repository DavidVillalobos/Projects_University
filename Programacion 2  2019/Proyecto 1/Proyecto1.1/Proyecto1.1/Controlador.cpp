#include "Controlador.h"
#include<fstream>

Controlador::Controlador(){
	modalidadContrato = 1;//Por default por el momento               SE DEBE ARREGLAR
	modalidadPago = true; //Unicamente por mes
	setColor(15);
}

Controlador::~Controlador() { delete empresa; }

void Controlador::iniciarPrograma(){
	cargarDatos();
	menuPrincipal();
	guardarDatos();
}

void Controlador::menuPrincipal() {
	int resp2 = 5;
	string vec2[4] = { "Recursos Humanos","Contabilidad","Gerencia","Salir" };
	string titulo = fuente("  " + empresa->getNombre());
	do {
		cls();
		do {
			print("\n" + titulo + "\n");
			print("     Direccion: " + empresa->getdireccion() + "  Numero De Telefono: ");
			print(empresa->getNumeroTelefono()); print('\n');
			print("\n             Seleccione el area donde desea entrar");
			resp2 = menuSeleccionLista(21, 5, vec2, 4, 10, 240);
			cls();
			switch (resp2) {//Aqui irian las contraseñas posiblemente
			case 1: { menuRecursosHumanos(); break; }
			case 2: { menuContabilidad(); break; }
			case 3: { menuGerencia(); break; }
			default: break;
			}
			cls();
		} while (resp2 != 4);
		print("\n\n\n     \250Seguro que desea salir?\n");
	} while (menuBinario(14, 2, 10, 240) != true);
}

void Controlador::cargarDatos(){
	//Cargando los datos de la empresa
	fstream salida("../datosEmpresa.txt");
	if (!salida.good()) {
		print("   Esta es la primera vez que se inicia el programa, por favor\n");
		print("   para continuar digite los siguientes datos de la empresa\n");
		print("Direccion: "); string direccion = readLine();
		print("Numero de Telefono: "); int numeroTelefono = readInt();
		empresa = new Empresa(" SMART SYSTEM ", direccion, numeroTelefono);
		cleanBuffer();
		cls();
	}
	else {
		string nombre, direccion, num;
		getline(salida, direccion, '\n');
		getline(salida, num, '\n');
		int numeroTelefono = stringToInt(num);
		empresa = new Empresa(" SMART SYSTEM ", direccion, numeroTelefono);
	}
	salida.close();
	//Cargando los datos de los empleados
	salida.open("../datosEmpleados.txt");
	if (salida.good()) {
		string id, nom, ape1, ape2, direc, dia, mes, anno, num;
		while (!salida.eof()) {
			//id	nombre	ape1	ape2	00/00/0000	direc	num	
			getline(salida, id, '\t');
			getline(salida, nom, '\t');
			getline(salida, ape1, '\t');
			getline(salida, ape2, '\t');
			getline(salida, dia, '/');
			getline(salida, mes, '/');
			getline(salida, anno, '\t');
			getline(salida, direc, '\t');
			getline(salida, num, '\n');
			if (!id.empty() && !nom.empty() && !ape1.empty() && !ape2.empty() && !dia.empty() && !mes.empty() && !anno.empty() && !direc.empty() && !num.empty()) {
				int diaNac = stringToInt(dia);
				int mesNac = stringToInt(mes);
				int annoNac = stringToInt(anno);
				int numTelef = stringToInt(num);
				empresa->ingresarEmpleado(new Empleado(id, nom, ape1, ape2, diaNac, mesNac, annoNac, direc, numTelef));
			}
		}
	}
	salida.close();
	//codigo	descripcion	salarioBase
	//Cargando los datos de los Puestos
	salida.open("../datosPuestos.txt");
	if (salida.good()) {
		string cod, descrip, salBas, plaza;
		while (!salida.eof()) {
			getline(salida, cod, '\t');
			getline(salida, descrip, '\t');
			getline(salida, salBas, '\n');
			if (!cod.empty() && !descrip.empty() && !salBas.empty()) {
				int salarioBase = stringToInt(salBas);
				empresa->ingresarPuesto(new Puesto(cod, descrip, salarioBase));
			}
		}
	}
	salida.close();

	//Cargando los datos de los contratos

	//"1	Id	Codigo	Adicional	DiaIngreso/MesIngreso/AnnoIngreso	00/00/0000\n"; contrato profesional
	//"2	Id	Codigo	Adicional	ahorroEscolar	ahorroNavideno	DiaIngreso/MesIngreso/AnnoIngreso	00/00/0000\n"; contrato cortoPlazo*/
	//"3	Id	Codigo	Adicional	ahorroEscolar	ahorroNavideno	vacante	DiaIngreso/MesIngreso/AnnoIngreso	00/00/0000\n"; contrato LargoPlazo
	salida.open("../datosContratos.txt");
	if (salida.good()) {
		string tip, id, codigo, adicional, diaIngreso, mesIngreso, annoIngreso, diaCesantia, mesCesantia, annoCesantia, ahorroEscolar, ahorroNavideno, vacante;
		//Punteros auxiliares
		Contrato *c;
		Empleado *e;
		Puesto *p;
		while (!salida.eof()) {
			//Leyendo datos
			c = NULL;
			e = NULL;
			p = NULL;
			getline(salida, tip, '\t');
			getline(salida, id, '\t');
			getline(salida, codigo, '\t');
			getline(salida, adicional, '\t');
			//		verificando que todos existan
			if (!tip.empty() && !id.empty() && !codigo.empty() && !adicional.empty()) {
					//Conversiones
				int tipo = stringToInt(tip);
				e = empresa->getEmpleado(id);
				if (e) {
					p = empresa->getPuesto(codigo);
					if (p) {
						switch (tipo) {
							case 1: {
								//Creando 
								c = new Profesional(e, p);
								break;
							}
							case 2: {
								//leyendo
								getline(salida, ahorroEscolar, '/');
								getline(salida, ahorroNavideno, '/');
								//		verificando que todos existan
								if (!ahorroEscolar.empty() && !ahorroNavideno.empty()) {
									//Conversiones
									int aE = stringToInt(ahorroEscolar);
									int aN = stringToInt(ahorroNavideno);
									//creando
									c = new  PlanillaCorta(e, p, aE, aN);
								}
								break;
							}
							case 3: {
								//Leyendo
								getline(salida, ahorroEscolar, '/');
								getline(salida, ahorroNavideno, '/');
								getline(salida, vacante, '/');
								// verificando que todos existen
								if (!ahorroEscolar.empty() && !ahorroNavideno.empty() && !vacante.empty()) {
									//conversiones
									int aE = stringToInt(ahorroEscolar);
									int aN = stringToInt(ahorroNavideno);
									Plaza *pl = new Plaza(p, true);
									pl->setVacante((vacante == "Si"));
									//creando
									c = new PlanillaIdefinida(e, pl, aE, aN);
								}
								break;
							}
						}
						//leyendo		
						getline(salida, diaIngreso, '/');
						getline(salida, mesIngreso, '/');
						getline(salida, annoIngreso, '\t');
						getline(salida, diaCesantia, '/');
						getline(salida, mesCesantia, '/');
						getline(salida, annoCesantia, '\n');
						//verificando que todos existen
						if (!diaIngreso.empty() && !mesIngreso.empty() && !annoIngreso.empty() && !diaCesantia.empty() && !mesCesantia.empty() && !annoCesantia.empty()) {
							//realizando conversiones
							int diaIng = stringToInt(diaIngreso);
							int mesIng = stringToInt(mesIngreso);
							int annoIng = stringToInt(annoIngreso);
							int diaCes = stringToInt(diaCesantia);
							int mesCes = stringToInt(mesCesantia);
							int annoCes = stringToInt(annoCesantia);
							int adicionales = stringToInt(adicional);
							// seteando
							c->setAdicionales(adicionales);
							c->setDiaIngreso(diaIng);
							c->setMesIngreso(mesIng);
							c->setAnnoIngreso(annoIng);
							if (diaCes != 0 && mesCes != 0 && annoCes != 0) {
								c->setDiaCesantia(diaCes);
								c->setMesCesantia(mesCes);
								c->setAnnoCesantia(annoCes);
							}
							//Insertando el Contrato en la lista de contratos
							empresa->getListC()->insertarInicio(c);
						}
					}
				}
			}
		}
	}
}

void Controlador::guardarDatos(){
	//Guardando Datos De La Empresa
	ofstream entrada("../datosEmpresa.txt");
	entrada << empresa->getdireccion()<<endl;
	entrada << empresa->getNumeroTelefono()<<endl;
	entrada.close();

	//Guardando Datos De los empleados
	entrada.open("../datosEmpleados.txt");
	empresa->getListE()->guardar(entrada);
	entrada.close();
	
	//Guardando Datos De los puestos
	entrada.open("../datosPuestos.txt");
	empresa->getListP()->guardar(entrada);
	entrada.close();
	
	//Guardando Datos De los Contratos
	entrada.open("../datosContratos.txt");
	empresa->getListC()->guardar(entrada);
	entrada.close();
}

void Controlador::menuGerencia(){
	string vec[3] = { " Direccion "," Telefono ", " Regresar "};
	int resp = 3;
	do {
		print("\n                Gerencia ");
		print("\n Direccion: " + empresa->getdireccion() + "\n");
		print(" Telefono: "); print(empresa->getNumeroTelefono()); print("\n");
		resp = menuSeleccionLista(18, 1, vec, 3, 10, 112);
		cls();
		if (resp == 1) {
			print("Direccion antigua: " + empresa->getdireccion() + "\n");
			while (true) {
				print("Digite la nueva direccion: ");
				string Newdirec = readLine();
				if (Newdirec != empresa->getdireccion()) {
					empresa->setDireccion(Newdirec);
					print("Direccion actualizada correctamente\n");
					pause();
					break;
				}
				else {
					print("Esta direccion es igual a la antigua\n");
				}
			}
		}
		if (resp == 2) {
			print("Telefono antiguo: "); 
			print(empresa->getNumeroTelefono()); 
			print("\n");
			while (true) {
				print("Digite el nuevo telefono: ");
				int nuevoNumero = readInt();
				if (nuevoNumero != empresa->getNumeroTelefono()) {
					empresa->setNumeroTelefono(nuevoNumero);
					print("Telefono actualizado correctamente\n");
					cleanBuffer();
					pause();
					break;
				}
				else {
					print("Este numero de telefono es igual al antiguo\n");
				}
			}
		}
		cls();
	} while (resp != 3);
}

void Controlador::menuRecursosHumanos() {
	int resp;
	string vec[6] = {"Empleados", "Contratos", "Puestos", "Plazas", "Modalidad De Contratacion", "Regresar"};
	do{
		print("\n\n              Recursos Humanos");
		resp = menuSeleccionLista(10, 1, vec, 6, 10, 240);
		cls();
		switch (resp) {
		case 1: { menuEmpleado(); break; }
		case 2: { menuContrato(); break; }
		case 3: { menuPuesto(); break;}
		case 4: { menuPlaza(); break;}
		case 5: { 
			print("MODALIDAD\n");
			print("La modalidad actual de contratacion es : " + modalidadContratacion() + "\n");
			print("    Selecciona una nueva forma de contratacion");
			string opciones[3] = { "Profesional","Planilla Definida","Planilla Indefinida" };
			int res = menuSeleccionLista(5, 5, opciones, 3, 10, 240);
			if (res != modalidadContrato) {
				modalidadContrato= res;
				print("La modalidad de contratacion se ha actualizado correctamente\n");
				print("La nueva modalidad es: " + modalidadContratacion() + "\n");
			}
			else {
				print("La modalidad no se ha cambiado por que has seleccionado la misma que estaba antes");
			}
			pause();
			break; 
		}
		default: break;
		}
		cls();
	} while (resp != 6);	
}

void Controlador::menuContabilidad(){
	if (empresa->getListC()->getK() > 0) {
		int resp;
		string vec[3] = { "Reporte General", "Informe Especifico", "Regresar" };
		do {
			print("\n\n              Contabilidad");
			resp = menuSeleccionLista(10, 1, vec, 3, 10, 240);
			cls();
			switch (resp) {
			case 1: {
				Fecha f;
				string informe;
				Contrato *c;
				informe = "- - - - - -	Reporte General de Pagos del " + f.toString() + "\n\n";
				informe += "ID\tNOMBRE\tCODIGO PUESTO\tSALARIO NETO\n";
				for (int i = 0; i < empresa->getListC()->getK(); i++) {
					c = empresa->getContrato(i);
					if (c) {
						informe += c->informe() + "\n";
					}
				}
				print(informe);
				//Guardando Reporte             General-DD-MM-AAAA.txt
				string nombre = "../ReporteGeneral-" + intToString(f.getDia()) + "-" + intToString(f.getMes()) + "-" + intToString(f.getDia()) + ".txt"; //Creando un archivo para el dia de hoy
				ofstream entrada(nombre);
				entrada << informe;
				entrada.close();
				pause();
				cls();
				break; 
			}
			case 2: {
				Contrato *c;
				print("Digite la cedula del empleado para generar un informe: "); string id = readLine();
				c = empresa->getContrato(id);
				if (c) {
					print("- - - - - -	Informe Especifico de Pago del empleado " + id + "\n\n");
					print(c->toString());
				}
				else {
					print("No existe ningun empleado asociado a esta cedula\n");
				}
				pause();
				cls();
				break;
			}
			default: break;
			}
		} while (resp != 3);
	}
	else {
		print("Lo sentimos aun no existen contratos, por lo tanto\n");
		print("el departamento de contabilidad esta deshabilitado\n");
		pause();
		cls();
	}
}

void Controlador::menuEmpleado() {
	Lista *list = empresa->getListE();
	int resp;
	string vec[6] = { "Ingresar Empleado", "Lista de Empleados", "Ver Empleado", "Modificar Empleado","Despedir Empleado","Regresar" };
	do {
		print("\n\n                Empleados");
		resp = menuSeleccionLista(10, 1, vec, 6, 10, 240);
		cls();
		switch (resp) {
		case 1: {
			IngresarEmpleado();
			break;
		}
		case 2: {
			if (list->getK() > 0) {
				print(" - - - - LISTA GENERAL DE EMPLEADOS - - - - \n\n");
				print(list->toString());
			}
			else {
				print("Aun no existen empleados, ingresa mas empleados");
			}
			pause();
			cls();
			break;
		}
		case 3: {
			if (list->getK() > 0) {
				print(" - - - - - EMPLEADO ESPECIFICO - - - - \n");
				print("Para mostrar un empleado digite su cedula: ");
				string id = readLine();
				Empleado *e = empresa->getEmpleado(id);
				if (e) {
					if (e->getId() == id) {
						print("Mostrando empleado . . .\n");
						print(e->toString() + "\n");
					}
					else {
						print("No existe ningun empleado asociado con esta cedula\n");
						print("Intentalo nuevamente con una cedula distinta\n");
					}
				}
				else {
					print("No existe ningun empleado asociado con esta cedula\n");
					print("Intentalo nuevamente con una cedula distinta\n");
				}
			}
			else{
				print("Aun no existen empleados, no podemos mostrar ninguno");
			}
			pause();
			cls();
			break;
		}
		case 4: {
			if (list->getK() > 0) {
				print(" - - - - - - - MODIFICAR EMPLEADO - - - - - - - \n");
				print("Para modificar un empleado digite su cedula:");
				string id = readLine();
				Empleado *e = empresa->getEmpleado(id);
				if (e) {
					cls();
					modificarEmpleado(e);
				}
				else {
					print("No existe ningun empleado asociado con esta cedula\n");
					print("Intentalo nuevamente con una cedula distinta");
					pause();
					cls();
				}
			}
			else {
				print("Aun no existen empleados, no podemos modificar ninguno");
				pause();
				cls();
			}
			break;
		}
		case 5: {
			Lista *listC = empresa->getListC();
			if (list->getK() > 0) {
				if (listC->getK() > 0) {
					print(" - - - - - - - DESPEDIR EMPLEADO - - - - - - - -\n");
					print("Para despedir un empleado digite su cedula: ");
					string id = readLine();
					Empleado *e = empresa->getEmpleado(id);
					if (e) {
						Contrato *r = empresa->getContrato(id);
						if (r) {
							print("Mostrando empleado . . .\n");
							print(e->toString());
							print("\n\250Esta seguro que desea despedir a este empleado?");
							if (menuBinario(10, 8, 10, 240)) {
								Contrato *c = empresa->getContrato(e->getId());
								print("El empleado ha sido despedido\n Esta es su liquidacion: ");
								print(empresa->despedir(c));
							}
							else {
								print("Ha decidido no despedir al empleado\n");
							}
						}
						else {
							print("Lo sentimos este empleado aun no tiene ningun contrato asignado\n");
						}
					}
					else {
						print("No existe ningun empleado asociado con esta cedula\n");
						print("Intentalo nuevamente con una cedula distinta\n");
					}
				}
				else {
					print("Ningun empleado tiene un contrato asociado\n");
				}
			}
			else {
				print("Aun no existen empleados, no puedes despedir a nadie\n");
			}
			pause();
			cls();
			break;
		}
		default: break;
		}
	} while (resp != 6);
}

void Controlador::menuPuesto() {
	int resp;
	string vec[6] = { "Ingresar Puesto", "Lista de Puestos", "Mostrar Puesto","Modificar Puesto", "Eliminar Puesto", "Regresar" };
	Lista *listP = empresa->getListP();
	do {
		print("\n\n                Puesto");
		resp = menuSeleccionLista(10, 1, vec, 6, 10, 240);
		cls();
		switch (resp) {
			case 1: {
				IngresarPuesto();
				break;
			}
			case 2: {
				if (listP->getK() > 0) {
					print(" - - - - Lista de Puestos - - - - \n\n");
					print(listP->toString() + "\n\n");
				}
				else {
					print("Lo sentimos no existen puestos aun para mostrar\n");
				}
				pause();
				cls();
				break;
			}
			case 3: {
				if (listP->getK() > 0) {
					print("Para mostrar un puesto digite el codigo del puesto :");
					string cod = readLine();
					Puesto *p = empresa->getPuesto(cod);
					if (p) {
						print(p->toString() + "\n\n");
					}
					else {
						print("Lo sentimos no existe ningun puesto asociado a este codigo\n");
					}
				}
				else {
					print("Lo sentimos no existen puestos para mostrar\n");
				}
				pause();
				cls();
				break;
			}
			case 4: {
				if (listP->getK() > 0) {
					print("Para modificar un puesto digite el codigo del puesto :");
					string cod = readLine();
					Puesto *p = empresa->getPuesto(cod);
					if (p) {
						cls();
						modificarPuesto(p);
					}
					else {
						print("Lo sentimos no existe ningun puesto asociado a este codigo\n");
						pause();
						cls();
					}
				}
				else {
					print("Lo sentimos aun no existen puestos para modificar\n");
					pause();
					cls();
				}
				break;
			}
			case 5: {
				if (listP->getK() > 0) {
					print(listP->toString() + "\n");
					print("Para eliminar un puesto digite el codigo del puesto :");
					string cod = readLine(); print("\n");
					Puesto *p = empresa->getPuesto(cod);
					if (p) {
						print("Se eliminara este puesto\n");
						print(p->toString() + "\n");
						Lista *list = empresa->getContrato_Puesto(cod);
						if (list->getK() > 0) {
							print("Con el codigo del puesto " + cod + " estan asociados los siguientes contratos\n");
							print(list->toString() + "\n");
							print("Si asi lo desea se eliminara el puesto, pero debes tomar en cuenta que los empleados\n");
							print("asociados con los contratos anteriores se van a despediran por carecer de un puesto\n");
							print("de trabajo y los contratos quedaran inhabilitados\n\n");
							print("Ademas la fecha de cesantia queda registrada como el dia de hoy\n");
						}
						print("\250Estas seguro que desea continuar con la eliminacion del puesto?\n");
						print(" 1) Si\n");
						print(" 2) No\n");
						int resp;
						while (true) {
							print("Digite un numero de la lista: "); resp = readInt();
							if (resp == 1 || resp == 2) {
								break;
							}
							print("Digite unicamente numeros de la lista\n");
						}
						if (resp == 1) {
							Fecha f;
							string informe;
							informe = "   El dia " + f.toString() + " se elimino el siguiente puesto\n";
							informe += p->toString() + "\n";
							if (list->getK() > 0) {
								informe += "Ademas se despidieron los siguientes empleados\n";
								Contrato *c;
								for (int i = 0; i < list->getK(); i++) {
									c = dynamic_cast<Contrato*>(list->getElemento(i));
									if (c) {
										informe += c->informe() + floatToString(empresa->despedir(c)) + "\n";
									}
								}
							}
							print(informe);
							ofstream entrada("../PuestosEliminados.txt", ios::app);
							entrada << informe;
							entrada.close();
							empresa->eliminarPuesto(cod);
						}
					}
					else {
						print("Lo sentimos no existe ningun puesto asociado a este codigo\n");
					}
				}
				else {
					print("Lo sentimos no existen puestos para mostrar");
				}
				pause();
				cls();
				break;
			}
			default: break;
		}
	} while (resp != 6);
}

void Controlador::menuPlaza() {
	int resp;
	string vec[4] = { "Ingresar Plaza", "Lista de Plazas", "Mostrar Plaza", "Regresar"};
	Lista *listP = empresa->getListP();
	do {
		print("       PLAZAS");
		resp = menuSeleccionLista(5, 5, vec, 4, 10, 240);
		cls();
		switch (resp) {
			case 1: {
				if (listP->getK() > 0) {
					print("Para ingresar una plaza primero debes asociarla con un puesto ya existente\n");
					print(" - - - - - -- LISTA DE PUESTOS - - - - - - ");
					print(listP->toString());
					print("\n  Digita un codigo de puesto: ");
					string codigo = readLine();
					Puesto *puesto = empresa->getPuesto(codigo);
					if (puesto) {
						Plaza *plaza = new Plaza(puesto,true); //Puesto asociado
						empresa->ingresarPlaza(plaza);
						print("Se ha ingresado la plaza correctamente\n");
					}
					else {
						print("Este codigo no esta asociado con ningun puesto, intentalo nuevamente\n");
					}
				}
				else {
					print("No existen puestos, Antes ingresar una plaza debe existir un puesto\n");
					print("con el que asociarlo previamente\n");
				}
				break;
			}
			case 2: {
				Lista *listPl = empresa->getListPl();
				if (listPl) {
					print(" - - - - - - - - LISTA DE PLAZAS - - - - - - - \n\n");
					print(listPl->toString());
				}
				else {
					print("Lo sentimos pero no hay plazas ingresadas aun\n");
				}
				break;
			}
			case 3: {
				if (listP->getK() > 0) {
					print("\nPara mostrar la plaza asociado a un puesto\n");
					print("digite el codigo del puesto: ");
					string cod = readLine();
					Plaza *plaza = empresa->getPlaza(cod);
					if (plaza) {
						print("PLAZA DEL PUESTO: " + cod + "\n");
						print(plaza->toString());
					}
					else {
						print("Este codigo no esta asociada con ninguna\n");
						print("plaza, intentalo nuevamente\n");
					}
				}
				else {
					print("No existe ningun puesto aun, por lo tanto\n");
					print("no existen plazas que mostrar\n");
				}
				break;
			}
			default: break;
		}
		pause();
		cls();
	} while (resp != 4);
}

void Controlador::menuContrato() {
	Lista *listE = empresa->getListE();
	if (listE->getK() > 0) { //Si existen empleados
		string vec[4] = {"Lista de Contratos", "Mostrar Contrato", "Modificar Contrato", "Regresar"};
		int resp;
		do {
			print(" - - - - - - MENU CONTRATOS - - - - - - ");
			resp = menuSeleccionLista(10, 1, vec, 4, 10, 240);
			cls();
			switch (resp) {
				case 1: {
					if (empresa->getListC() > 0) {
						print(" - - - - - - LISTA DE CONTRATOS - - - - - - - \n");
						print(empresa->getListC()->toString());
					}
					else {
						print("Lo sentimos no existen contratos aun\n");
					}
					pause();
					cls();
					break;
				}
				case 2: {
					if (empresa->getListC() > 0) {
						print("Para mostrar un contrato debes digitar la cedula del empleado asociado a esta\n");
						print("Cedula: "); string id = readLine();
						Contrato *c = empresa->getContrato(id);
						if (c) {
							print(c->toString());
						}
						else {
							print("Lo sentimos no existen ningun contrato asociados a un empleado con esa cedula\n");
						}
					}
					else {
						print("Lo sentimos aun no existen contratos\n");
					}
					pause();
					cls();
					break;
				}
				case 3: {
					if (empresa->getListC() > 0) {
						print("Para modificar un contrato debes digitar la cedula del empleado asociado a esta\n");
						print("Cedula: "); string id = readLine();
						Contrato *c = empresa->getContrato(id);
						if (c) {
							modificarContrato(c);
						}
						else {
							print("Lo sentimos no existen contratos asociados a un empleado con esa cedula");
						}
					}
					else {
						print("Lo sentimos no existen contratos aun\n");
					}
					pause();
					cls();
					break;
				}
			default: break;
			}
		} while (resp != 4);
	}
	else{
		print("No Puedes entrar en esta area aun, porque aun no exiten empleados\n por lo tanto no puedes generar contratos\n");
		pause();
		cls();
	}
	
}

void Controlador::modificarEmpleado(Empleado *e) {
	string vec[7] = { "Nombre", "Primer Apellido", "Segundo Apellido", "Fecha de Nacimiento","Direccion","Telefono","Regresar" };
	int resp;
	int resp2;
	string vec2[4] = { "Dia","Mes","A\244o","Regresar" };
	cls();
	do {
		print("\n\n            Empleado [ " + e->getId() + "] ");
		resp = menuSeleccionLista(10, 1, vec, 7, 10, 240);
		cls();
		switch (resp) {
			case 1: {
				print("Nombre:" + e->getnombre() + "\n");
				print("Digite el Nuevo nombre: "); string nom = readLine();
				e->setNombre(nom);
				print("El nombre se ha cambiado por " + nom); print('\n');
				pause();
				cls();
				break;
			}
			case 2: {
				print("Primer Apellido: " + e->getApellido1() + "\n");
				print("Digite el Nuevo Primer Apellido : "); string ape1 = readLine();
				e->setApellido1(ape1);
				print("El Primer Apellido se ha cambiado por " + ape1); print('\n');
				pause();
				cls();
				break;
			}
			case 3: {
				print("Segundo Apellido: " + e->getApellido2() + "\n");
				print("Digite el Nuevo Segundo Apellido : "); string ape2 = readLine();
				e->setApellido2(ape2);
				print("El Segundo Apellido se ha cambiado por " + ape2); print('\n');
				pause();
				cls();
				break;
			}
			case 4: {
				do {
					cls();
					print("Fecha de Nacimiento actual: " + e->getFechaNacimiento() + "\n");
					print(" Seleccione que desea cambiar");
					resp2 = menuSeleccionLista(10, 1, vec2, 4, 10, 240);
					switch (resp2) {
					case 1: {
						print("Dia de Nacimiento: "); print(e->getDiaNac()); print("\n");
						print("Digite el nuevo Dia : "); int dia = readInt();
						e->setDiaNac(dia);
						print("El Dia de nacimiento se ha cambiado por "); print(dia);
						print("\n");
						pause();
						cls();
						break;
					}
					case 2: {
						print("Mes de Nacimiento: "); print(e->getMesNac()); print("\n");
						print("Digite el nuevo Numero del Mes: "); int mes = readInt();
						e->setMesNac(mes);
						print("El Mes de nacimiento se ha cambiado por "); print(mes);
						print('\n');
						pause();
						cls();
						break;
					}
					case 3: {
						print("Mes de Nacimiento: "); print(e->getAnnoNac()); print("\n");
						print("Digite el nuevo A\244o : "); int anno = readInt();
						e->setAnnoNac(anno);
						print("El A\244o de nacimiento se ha cambiado por "); print(anno);
						print('\n');
						pause();
						cls();
						break;
					}
					default: cls(); break;
					}
				} while (resp2 != 4);
				break;
			}
			case 5: {
				print("Direccion Actual: "); print(e->getDireccion()); print("\n");
				print("Digite la nueva direccion : "); string direccion = readLine();
				e->setDireccion(direccion);
				print("La direccion se ha cambiado por "); print(direccion);
				pause();
				cls();
				break;
			}
			case 6: {
				print("Numero de telefono actual: "); print(e->getNumeroTelefono()); print("\n");
				print("Digite el nuevo A\244o : "); int num = readInt();
				e->setNumeroTelefono(num);
				print("El Numero de Telefono se ha cambiado por "); print(num);
				pause();
				cls();
				break;
			}
		default: break;
		}
	} while (resp != 7);
}

void Controlador::modificarPuesto(Puesto *p){
	string vec[4] = { "Codigo", "Descripcion", "Salario Base","Regresar"};
	int resp;
	do {
		print(" - - - - - -	MODIFICAR PUESTO - - - - -- \n");
		print("Seleccione que desea modificar del Puesto");
		resp = menuSeleccionLista(10, 1, vec, 4, 10, 240);
		cls();
		switch (resp){
			case 1: { 
				print("Codigo actual: " +  p->getCodigo() + "\n");
				string cod;
				while (true) {
					print("Digite el nuevo codigo: "); cod = readLine();
					p = empresa->getPuesto(cod);
					if(p){
						if (p->getCodigo() == cod) {
							print("Este codigo ya existe para otro puesto\n");
							print("Elige otro,   \n");
							continue;
						}
					}
					break;
				}
				p->setCodigo(cod);
				print("El codigo se ha cambiado por: " + cod + "\n"); 
				pause();
				cls();
				break; 
			}
			case 2: { 
				print("Descripcion actual\n " + p->getDescripcion() + "\n");
				print("Digite la nueva descripcion: "); string descripcion = readLine();
				p->setDescripcion(descripcion);
				print("La descripcion se ha cambiado por: \n" + descripcion + "\n");
				pause();
				cls();
				break; 
			}
			case 3: { 
				print("Salario Base actual: "); print(p->getSalarioBase());
				print("\nDigite el nuevo Salario Base: "); int salarioBase= readInt();
				p->setSalarioBase(salarioBase);
				print("El Salario Base se ha cambiado por: "); print(p->getSalarioBase());
				print("\n");
				pause();
				cls();
				break; 
			}
			default:  break;
		}
	} while (resp != 4);
}

void Controlador::modificarContrato(Contrato* c) {
	cls();
	if (typeid(*c).name() == "class Profesional") {
		int resp;
		string vec[3] = { "Fecha de Ingreso","Adicionales","Regresar" };
		do {
			Profesional* p = empresa->getContratoProfesional(c);
			print(" - - - - - - -- MODIFICAR CONTRATO DEL EMPLEADO - - - - - - - - -\n");
			print("\t\t" + c->getEmpleado()->getNombreCompleto() + "\n");
			print("Selecciona una opcion a modificar");
			resp = menuSeleccionLista(10, 1, vec, 3, 10, 240);
			switch (resp) {
			case 1: {
				int dia, mes, anno;
				print("Fecha de ingreso actual : " + c->fechaIngreso());
				print("Ingrese la nueva fecha: ");
				pedirFecha(dia, mes, anno);
				c->setAnnoIngreso(anno);
				c->setMesIngreso(mes);
				c->setDiaIngreso(dia);
				print("\nLa nueva fecha de ingreso es: " + c->fechaIngreso());
			}
			case 2: {
				print("La suma de los adicionales actuales es de: ");  print(p->getAdicionales());
				print("Ingrese la nueva suma de adicionales: ");
				int value = readInt();
				p->setAdicionales(value);
				print("La nueva suma de los adicionales es de : "); print(value); print('\n');
				empresa->CalcularSalarioBruto(p);
				empresa->CalcularSalarioNeto(p);
				break;
			}
			default: break;
			}
		} while (resp != 3);
	}
	else {
		int resp;
		string vec[5] = { "Fecha de Ingreso","Ahorro Navide\244o","Ahorro Escolar","Adicionales","Regresar" };
		do {
			Planilla* p = empresa->getContratoPlanilla(c);
			print(" - - - - - - -- MODIFICAR CONTRATO DEL EMPLEADO - - - - - - - - -\n");
			print("\t\t" + c->getEmpleado()->getNombreCompleto() + "\n");
			print("Selecciona una opcion a modificar");
			resp = menuSeleccionLista(10, 1, vec, 5, 10, 240);
			switch (resp) {
			case 1: {
				int dia, mes, anno;
				print("Fecha de ingreso actual : " + c->fechaIngreso());
				print("Ingrese la nueva fecha: ");
				pedirFecha(dia, mes, anno);
				c->setAnnoIngreso(anno);
				c->setMesIngreso(mes);
				c->setDiaIngreso(dia);
				if (typeid(*c).name() == "class PlanillaCorta") {
					int fdia, fmes, fanno;
					c->Tdif_Tactual(fdia, fmes, fanno);
					if ( fanno <= 1 || 90 <= fmes * 30 + fdia) {
						//Debo hacer el cambio automatico
						Plaza *aux = new Plaza(c->getPuesto(), false);
						empresa->ingresarPlaza(aux);
						PlanillaIdefinida(c->getEmpleado(), aux, p->getAhorroNavideno(), p->getAhorroEscolar());
					}
				}
				print("\nLa nueva fecha de ingreso es: " + c->fechaIngreso());
			}
			case 2: {
				print("El porcentaje de ahorro navide\244o actual es de: ");  print(p->getAhorroNavideno());
				print("Ingrese el nuevo porcentaje del ahorro navide\244o: ");
				int value = readInt();
				p->setAhorroNavideno(value);
				print("El nuevo porcentaje de ahorro navideno es de : "); print(value); print('\n');
				empresa->CalcularSalarioBruto(p);
				empresa->CalcularSalarioNeto(p);
				break;
			}
			case 3: {
				print("El porcentaje de ahorro escolar actual es de: ");  print(p->getAhorroEscolar());
				print("Ingrese el nuevo porcentaje del ahorro escolar: ");
				int value = readInt();
				p->setAhorroEscolar(value);
				print("El nuevo porcentaje de ahorro escolar es de : "); print(value); print('\n');
				empresa->CalcularSalarioBruto(p);
				empresa->CalcularSalarioNeto(p);
				break;
			}
			case 4: {
				print("La suma de los adicionales actuales es de: ");  print(p->getAdicionales());
				print("Ingrese la nueva suma de adicionales: ");
				int value = readInt();
				p->setAdicionales(value);
				print("La nueva suma de los adicionales es de : "); print(value); print('\n');
				empresa->CalcularSalarioBruto(p);
				empresa->CalcularSalarioNeto(p);
				break;
			}
			default: break;
			}
		} while (resp != 5);
	}
}

string Controlador::modalidadContratacion() {
	switch (modalidadContrato) {
		case 1: return "Profesional";
		case 2:  return "Plantilla Definida (corto plazo)";
		case 3: return "Plantilla Idefinida (largo plazo)";
		default: return "Sin asignar";
	}
}

void Controlador::IngresarEmpleado() {
	if (empresa->getListP()->getK() > 0) { //Si existen puestos
		Empleado *nuevo;
		string id, nombre, apellido1, apellido2, direccion;
		int diaNac, mesNac, annoNac, numeroTelefono;
		while (true) {
			cls();
			print(" - - - - - - - INGRESAR NUEVO EMPLEADO- - - - - - - - \n");
			print("Ingrese los siguientes Datos del empleado\n");
			while (true) {
				print("Identificacion: "); id = readLine();
				Empleado *aux = empresa->getEmpleado(id);
				if (aux) {
					if (aux->getId() == id) {
						print("Ya existe un empleado con esta cedula\n");
						print(aux->toString() + "\n");
						print("Intentalo de nuevo\n");
						continue;
					}
				}
				break;
			}
			print("Primer Apellido: "); apellido1 = readLine();
			print("Segundo Apellido: "); apellido2 = readLine();
			print("Nombre: "); nombre = readLine();
			print("Direccion: "); direccion = readLine();
			print("Fecha de nacimiento\n");
			pedirFecha(diaNac,mesNac,annoNac);
			print("Numero de telefono: "); numeroTelefono = readInt();  cleanBuffer();
			nuevo = new Empleado(id, nombre, apellido1, apellido2, diaNac, mesNac, annoNac, direccion, numeroTelefono);
			cls();
			print("\n\t  EMPLEADO NUEVO\n");
			print(nuevo->toString());
			print("\n\t\250Todos los datos del empleado son correctos?");
			if (menuBinario(18, 8, 10, 240) == false) {
				delete nuevo;
				continue;
			}
			cls();
			if (IngresarContrato(nuevo)) {
				empresa->ingresarEmpleado(nuevo);
				print("\nEl contrato y el empleado se han creado e insertado exitosamente\n");
				break;
			}
			else {
				delete nuevo;
			}
		}
	}
	else {
		print("No puedes contratar personas si aun no existen puestos\n");
	}
	pause();
	cls();
}

void Controlador::IngresarPuesto() {
	string codigo, descripcion;
	int salarioBase;
	while (true) {
		print(" - - - - - - - INGRESAR PUESTO  - - - - - - - - \n");
		print("Para ingresar un puesto nuevo, favor de ingresar los\n");
		print("Siguientes datos\n");
		print("Genera un codigo unico: ");
		while (true) {
			codigo = readLine();
			Puesto *p = empresa->getPuesto(codigo);
			if (p) {
				if (p->getCodigo() == codigo) {
					print("Este codigo ya es utilizado por otro puesto, intentalo de nuevo\n");
					print("\tCodigo: ");
					continue;
				}
			}
			break;
		}
		print("Escribe una descripcion del puesto: "); descripcion = readLine();
		print("Digita el Salario Base: "); salarioBase = readInt();
		Puesto *p = new Puesto(codigo, descripcion, salarioBase);
		print(p->toString() + '\n');
		print("\t\250Todos los datos del contrato son correctos?");
		if (menuBinario(26, 11, 10, 240)) {
			empresa->ingresarPuesto(p);
			print("\nEl puesto ha sido ingresado exitosamente\n");
			pause();
			cls();
			break;
		}
		cls();
		delete p;
		continue;
	}
}

bool Controlador::IngresarContrato(Empleado *e) {
	while (true) {
		print("   INGRESAR UN NUEVO CONTRATO\n");
		print("Todo empleado debe de tener un puesto\n");
		print(empresa->getListP()->toString() + "\n");
		print("Por favor ingrese un codigo de puesto de los anteriores: ");
		string cod = readLine();
		Puesto *p = empresa->getPuesto(cod);
		if (p) {
			print("Ingrese los siguientes datos del contrato\n\n");
			print("La modalidad de contratacion actual es de tipo " + modalidadContratacion() + "\n\n");
			int diaIngreso, mesIngreso, annoIngreso;
			print("\250Desea que la fecha de ingreso se registre como el dia de hoy?");
			Fecha f;
			if (menuBinario(25, 12, 10, 240) == true) {
				print("\n");
				diaIngreso = f.getDia();
				mesIngreso = f.getMes();
				annoIngreso = f.getAnno();
				print("La fecha fue ingresada automaticamente como\n");
			}
			else {
				print("\nDigite los siguientes datos de la fecha de ingreso\n");
				pedirFecha(diaIngreso, mesIngreso, annoIngreso);
				f.setDia(diaIngreso);
				f.setMes(mesIngreso);
				f.setAnno(annoIngreso);
			}
			print(f.toString() + "\n");
			pause();
			cls();
			Contrato *c = NULL;
			switch (modalidadContrato) {//Dependiendo del modo de contratacion se piden diferentes datos
			case 1: {
				c = new Profesional(e, p);
				break;
			}
			case 2: {
				int ahorroEscolar = 0;
				int ahorroNavideno = 0;
				print("\250El empleado desea realizar ahorro escolar?");
				if (menuBinario(10, 1, 10, 250)) {
					print("Este procentaje es una deduccion a el salario bruto\n");
					print("Digite un porcentaje de ahorro escolar: ");
					while (true) {
						ahorroEscolar = readInt();
						if (0 <= ahorroEscolar && ahorroEscolar <= 100) {
							break;
						}
						print("El porcentaje no puede exceder a 100 ni ser menor que 0");
					}
				}
				print("\250El empleado desea realizar ahorro navide\244o?");
				if (menuBinario(10, 1, 10, 250)) {
					print("Digite el porcentaje de ahorro navide\244o: ");
					ahorroNavideno = readInt();

				}
				cls();
				Fecha m;
				m = m - f;
				if ( m.getAnno() <= 1 || 90 <= m.getMes() * 30 + m.getDia()) {
					//Debo hacer el cambio automatico
					Plaza *aux = new Plaza(p, false);
					empresa->ingresarPlaza(aux);
					PlanillaIdefinida(e, aux, ahorroNavideno,ahorroEscolar);
				}
				else {
					c = new PlanillaCorta(e, p, ahorroNavideno, ahorroEscolar);
				}
				break;
			}
			case 3: {
				int ahorroEscolar = 0;
				int ahorroNavideno = 0;
				print("\250El empleado desea realizar ahorro escolar?");
				if (menuBinario(10, 1, 10, 250)) {
					cls();
					print("Digite el porcentaje de ahorro escolar: ");
					ahorroEscolar = readInt();
				}
				cls();
				print("\250El empleado desea realizar ahorro navide\244o?");
				if (menuBinario(10, 5, 10, 250)) {
					cls();
					print("Digite el porcentaje de ahorro navide\244o: ");
					ahorroNavideno = readInt();
				}
				cls();
				c = new PlanillaIdefinida(e, new Plaza(p, true), ahorroNavideno, ahorroEscolar);
				break;
			}
			default: c = NULL; //Sin asignar modo de contratacion
			}
			int add = 0;
			print("\250El empleado recibe algun adicional, extra o regalia?");
			if (menuBinario(20, 1, 10, 250)) {
				print("\n");
				print("Digite la suma de todos los adicionales: ");
				add = readInt();
			}
			if (c) {
				c->setAdicionales(add);
			}
			string tipo;
			tipo = typeid(*c).name();
			if (tipo == "class PlanillaCorta" || tipo == "class PlanillaIdefinida") {
				empresa->CalcularSalarioBruto(c);
				empresa->CalcularSalarioNeto(c);
			}
			else {
				c->setSalarioBruto(c->getAdicionales() + c->getPuesto()->getSalarioBase());
				c->setSalarioNeto(c->getSalarioBruto());
			}
			cls();
			print(c->toString() + "\n");
			print("\n\t\250Todos los datos del contrato son correctos?");
			if (menuBinario(26, 18, 10, 240) == false) {
				cls();
				delete c;
				continue;
			}			
			empresa->ingresarContrato(c);
			return true;
		}
		else {
			print("No existe ningun puesto asociado con ese codigo\n");
			return false;
		}
	}
}