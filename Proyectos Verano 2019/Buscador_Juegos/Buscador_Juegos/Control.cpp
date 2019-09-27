#include "Control.h"
Control::Control() {
	listJuegos = new juegos;
}

void Control::cargarArchivos() {
	fstream f;
	f.open("../Juegos.txt");
	while (f.good()) {
		etiquetas *listEtiquetas = new etiquetas();
		string etq;
		getline(f, etq, '#');
		while (etq != "*") {
			if (!etq.empty()) {
				listEtiquetas->insertarEtiqueta(etq);
			}
			getline(f, etq, '#');
		}
		string nombre, disponibilidad, descripcion, descripcionAux;
		getline(f, nombre, '*');
		getline(f, disponibilidad, '*');
		getline(f, descripcion, '*');
		while (descripcion != "#") {
			descripcionAux = descripcionAux + "\n\t\t\t" + descripcion;
			getline(f, descripcion, '*');
		}
		if (!nombre.empty() && !disponibilidad.empty() && !descripcionAux.empty()) {
			listJuegos->insertarJuego(nombre, disponibilidad, listEtiquetas, descripcionAux);
		}
		getline(f, descripcion, '\n');
	}
	f.close();
	menu();
}

void Control::menu() {
	setColor(15); setCursor(94, 2); cout << "\251David_Villalobos_2018";
	imprimeMarcoDoble(23, 3, 28, 91, 14, "\260", 12, 6);
	pantallaPrincipal();
	int menu = 4;
	do {
		system("cls");
		setColor(15); setCursor(94, 2); cout << "\251David_Villalobos_2018";
		imprimeMarco(24, 3, 20, 92, 14); setColor(15);
		string a = "\333"; string b = "\337"; string c = "\334";
		string d = "\260"; string e = "\262";
		setCursor(38, 5); imprimeString(a + b + b + a + " " + a + "  " + a + "  " + a + b + b + b + a + "  " + a + b + b + a + "  " + a + b + b + a + "  " + a + b + b + c + "  " + a + b + b + b + a + "  " + a + b + b + a + "     " + a + b + b + c + "  " + a + b + b + b);
		setCursor(38, 6); imprimeString(a + b + b + c + " " + a + "  " + a + "  " + b + b + b + c + c + "  " + a + "     " + a + c + c + a + "  " + a + "  " + a + "  " + a + "   " + a + "  " + a + c + c + b + "     " + a + "  " + a + "  " + a + b + b + b);
		setCursor(38, 7); imprimeString(a + c + c + a + " " + b + c + c + b + "  " + a + c + c + c + a + "  " + a + c + c + a + "  " + a + "  " + a + "  " + a + c + c + b + "  " + a + c + c + c + a + "  " + a + "  " + a + "     " + a + c + c + b + "  " + a + c + c + c);
		setCursor(51, 9); imprimeString("    " + a + "  " + a + "  " + a + "  " + a + b + b + b + "  " + a + b + b + a + "  " + a + b + b + b + a + "  " + a + b + b + b + a);
		setCursor(51, 10); imprimeString(" " + c + "  " + a + "  " + a + "  " + a + "  " + a + b + b + b + "  " + a + " " + c + c + "  " + a + "   " + a + "  " + b + b + b + c + c);
		setCursor(51, 11); imprimeString(" " + a + c + c + a + "  " + b + c + c + b + "  " + a + c + c + c + "  " + a + c + c + a + "  " + a + c + c + c + a + "  " + a + c + c + c + a);
		setCursor(26, 14); cout << "   El siguiente programa se encarga de buscar juegos funciona analizando las";
		setCursor(27, 15); cout << "   etiquetas ingresadas y buscando cual es el juego con mayor compatibilidad y";
		setCursor(28, 16); cout << "   muestra de mayor a menor compatibilidad segun la cantidad que desee mostrar";
		imprimeMarco(46, 17, 5, 46, 14); setColor(15);
		setCursor(47, 18); cout << "         MENU PRINCIPAL";
		setCursor(47, 19); cout << "  1)  Buscar Juego";
		setCursor(47, 20); cout << "  2)  Ver lista de juegos";
		setCursor(47, 21); cout << "  3)  Salir";
		setCursor(47, 22); cout << "  Inserte un numero para realizar una accion"; menu = leerInt();
		switch (menu) {
		case 1: {iniciar(); break; }
		case 2: {cout << endl << endl << endl << endl << listJuegos->toString(); system("pause"); break; }
		case 3: {break; }
		}
	} while (menu != 3);
	saliendo();
}

void Control::iniciar() {
	system("cls");
	setColor(15); setCursor(116, 2); cout << "\251David_Villalobos_2018";
	imprimeMarcoDoble(14, 3, 21, 122, 1, "\260", 4, 6);
	
	int y = 8; int x = 25;
	setColor(14); 
		 setCursor(x, y); imprimeString("                                            LISTA DE ETIQUETAS"); setColor(15);
	y=y+2;setCursor(x, y);imprimeString("[1] -> ["); setColor(14); imprimeString("360\370"); setColor(15); imprimeString("]         [2] -> ["); setColor(14); imprimeString("Accion"); setColor(15); imprimeString("]          [3] -> ["); setColor(14); imprimeString("Antropomorfico"); setColor(15); imprimeString("]   [4] -> ["); setColor(14); imprimeString("Apocalipsis"); setColor(15); imprimeString("]");
	y++; setCursor(x, y); imprimeString("[5] -> ["); setColor(14); imprimeString("Asesinato"); setColor(15); imprimeString("]    [6] -> ["); setColor(14); imprimeString("Aventura"); setColor(15); imprimeString("]        [7] -> ["); setColor(14); imprimeString("Aviones"); setColor(15); imprimeString("]          [8] -> ["); setColor(14); imprimeString("Batalla"); setColor(15); imprimeString("]");
	y++; setCursor(x, y); imprimeString("[9] -> ["); setColor(14); imprimeString("Castillo"); setColor(15); imprimeString("]     [10] -> ["); setColor(14); imprimeString("CienciaFiccion"); setColor(15); imprimeString("] [11] -> ["); setColor(14); imprimeString("Combate"); setColor(15); imprimeString("]         [12] -> ["); setColor(14); imprimeString("Crear"); setColor(15); imprimeString("]");
	y++; setCursor(x, y); imprimeString("[13] -> ["); setColor(14); imprimeString("Crimen"); setColor(15); imprimeString("]      [14] -> ["); setColor(14); imprimeString("Cyberpunk"); setColor(15); imprimeString("]      [15] -> ["); setColor(14); imprimeString("Dinero"); setColor(15); imprimeString("]          [16] -> ["); setColor(14); imprimeString("Dinosaurios"); setColor(15); imprimeString("]");
	y++; setCursor(x, y); imprimeString("[17] -> ["); setColor(14); imprimeString("Drogas"); setColor(15); imprimeString("]      [18] -> ["); setColor(14); imprimeString("Estrategia"); setColor(15); imprimeString("]     [19] -> ["); setColor(14); imprimeString("Explorar"); setColor(15); imprimeString("]        [20] -> ["); setColor(14); imprimeString("Extraterrestres"); setColor(15); imprimeString("]");
	y++; setCursor(x, y); imprimeString("[21] -> ["); setColor(14); imprimeString("Fantasia"); setColor(15); imprimeString("]    [22] -> ["); setColor(14); imprimeString("Gestionar"); setColor(15); imprimeString("]      [23] -> ["); setColor(14); imprimeString("Gobernar"); setColor(15); imprimeString("]        [24] -> ["); setColor(14); imprimeString("Investigar"); setColor(15); imprimeString("]");
	y++; setCursor(x, y); imprimeString("[25] -> ["); setColor(14); imprimeString("Maldicion"); setColor(15); imprimeString("]   [26] -> ["); setColor(14); imprimeString("Mapas"); setColor(15); imprimeString("]          [27] ->["); setColor(14); imprimeString("Masacre"); setColor(15); imprimeString("]          [28] ->["); setColor(14); imprimeString("Misiones]"); setColor(15);
	y++; setCursor(x, y); imprimeString("[29] -> ["); setColor(14); imprimeString("Misterio"); setColor(15); imprimeString("]    [30] -> ["); setColor(14); imprimeString("Monstruos"); setColor(15); imprimeString("]      [31] -> ["); setColor(14); imprimeString("NavesEspaciales"); setColor(15); imprimeString("] [32] -> ["); setColor(14); imprimeString("MultijugadorMasivo"); setColor(15); imprimeString("]");
	y++; setCursor(x, y); imprimeString("[33] -> ["); setColor(14); imprimeString("Niveles"); setColor(15); imprimeString("]     [34] -> ["); setColor(14); imprimeString("Plataforma"); setColor(15); imprimeString("]     [35] -> ["); setColor(14); imprimeString("PostApocaliptico"); setColor(15); imprimeString("][36] -> ["); setColor(14); imprimeString("ParqueDeAtracciones"); setColor(15); imprimeString("]");
	y++; setCursor(x, y); imprimeString("[37] -> ["); setColor(14); imprimeString("Robots"); setColor(15); imprimeString("]      [38] -> ["); setColor(14); imprimeString("Rol"); setColor(15); imprimeString("]            [39] -> ["); setColor(14); imprimeString("Sangriento"); setColor(15); imprimeString("]      [40] -> ["); setColor(14); imprimeString("Supervivencia"); setColor(15); imprimeString("]");
	y++; setCursor(x, y); imprimeString("[41] -> ["); setColor(14); imprimeString("Terror"); setColor(15); imprimeString("]      [42]->["); setColor(14); imprimeString("TerrorPsicologico"); setColor(15); imprimeString("][43] -> ["); setColor(14); imprimeString("Vampiros"); setColor(15); imprimeString("]        [44] -> ["); setColor(14); imprimeString("Zombies"); setColor(15); imprimeString("]");
	setColor(15);
	y = y + 7; setCursor(x, y); imprimeString("Digite el numero de la etiqueta que desea, para finalizar digite 0: "); int num = leerInt();
	etiquetas *listBusc = new etiquetas();
	while (num != 0) {
		string nueva;
		switch (num) {
		case 1: {nueva = "360Grados"; break; }
		case 2: {nueva = "Accion"; break; }
		case 3: {nueva = "Antropomorfico"; break; }
		case 4: {nueva = "Apocalipsis"; break; }
		case 5: {nueva = "Asesinato"; break; }
		case 6: {nueva = "Aventura"; break; }
		case 7: {nueva = "Aviones"; break; }
		case 8: {nueva = "Batalla"; break; }
		case 9: {nueva = "Castillo"; break; }
		case 10: {nueva = "CienciaFiccion"; break; }
		case 11: {nueva = "Combate"; break; }
		case 12: {nueva = "Crear"; break; }
		case 13: {nueva = "Crimen"; break; }
		case 14: {nueva = "Cyberpunk"; break; }
		case 15: {nueva = "Dinero"; break; }
		case 16: {nueva = "Dinosaurios"; break; }
		case 17: {nueva = "Drogas"; break; }
		case 18: {nueva = "Estrategia"; break; }
		case 19: {nueva = "Explorar"; break; }
		case 20: {nueva = "Extraterrestres"; break; }
		case 21: {nueva = "Fantasia"; break; }
		case 22: {nueva = "Gestionar"; break; }
		case 23: {nueva = "Gobernar"; break; }
		case 24: {nueva = "Investigar"; break; }
		case 25: {nueva = "Maldicion ";break; }
		case 26: {nueva = "Mapas";break; }
		case 27: {nueva = "Masacre";break; }
		case 28: {nueva = "Misiones";break; }
		case 29: {nueva = "Misterio";break; }
		case 30: {nueva = "Monstruos";break; }
		case 31: {nueva = "NavesEspaciales";break; }
		case 32: {nueva = "MultijugadorMasivo";break; }
		case 33: {nueva = "Niveles";break; }
		case 34: {nueva = "Plataforma"; break; }
		case 35: {nueva = "PostApocaliptico";break; }
		case 36: {nueva = "ParqueDeAtracciones";break; }
		case 37: {nueva = "Robots"; break; }
		case 38: {nueva = "Rol";break; }
		case 39: {nueva = "Sangriento"; break; }
		case 40: {nueva = "Supervivencia"; break; }
		case 41: {nueva = "Terror";break; }
		case 42: {nueva = " TerrorPsicologico"; break; }
		case 43: {nueva = "Vampiros"; break; }
		case 44: {nueva = "Zombies"; break; }
		default: {nueva = "*"; break; }
		}
		if (nueva == "*") { y++; setCursor(x, y); imprimeString("   Favor ingresar numeros unicamente que esten en la lista"); }
		else { y++; setCursor(x, y); imprimeString("   La etiqueta --> ["); setColor(14); imprimeString(nueva); setColor(15); imprimeString("] ha sido ingresada correctamente en la lista");listBusc->insertarEtiqueta(nueva); }
		y++; setCursor(x, y); imprimeString("   Digite el numero de la etiqueta que desea, para finalizar digite 0: "); num = leerInt();
	}
	if(listBusc->cuentaEtiquetas()!=0){
		x = 10; y = 3;
		system("cls");
		setCursor(20, 3); setColor(14);imprimeString("Usted ha ingresado la siguiente lista de etiquetas");
	y++; setCursor(x, y); imprimeString(listBusc->toString());
	y = y + 2; setCursor(x, y); imprimeString(" Iniciando sistema de busqueda por etiquetas");
	y++; cargando(x, y, 1, 64, 4, 15,"\260",2);
	setColor(14);
	y = y + 4; setCursor(x, y); imprimeString(" Compatibilidad encontrada :) , ten en cuenta que si un juego obtuvo 0% de compatibilidad el juego no sera mostrado");
	y++; setCursor(x, y); imprimeString(" Digite el numero con el que desea limitar la lista de busqueda encontrada "); int num = leerInt();
	setColor(15);
	juegos *listaDeCompatibles = listJuegos->lista_Juegos_Compatibles(listBusc);
		if (num > 0) {
			listaDeCompatibles->limitarLista(num);
			imprimeString(listaDeCompatibles->toStringCompatibles(listBusc));
		}
		else {
			y++; y++; setColor(14); setCursor(x, y); imprimeString(" Limitaste la lista a menor o igual que 0 no podemos mostrar ninguna recomendacion :(");
			y++; setCursor(x, y);
		}
	system("pause");
	}
	else {
		y++; setColor(14);setCursor(x, y); cout << " No ha ingresado etiquetas, volviendo al menu principal . . .";
		Sleep(3000);
	}
}

void Control::saliendo() {
	system("cls");
	setColor(15); setCursor(94, 2); cout << "\251David_Villalobos_2018";
	imprimeMarcoDoble(23, 3, 28, 91, 14, "\260", 12, 15);
	string a="\333";
	string b="\334";
	string c="\337";
	setCursor(55,13); setColor(15);imprimeString(a + "  " + a + " " + a + c + c + a + "  " + a + c + c + c + a + " " + c + c + a + c + c + "  " + a + c + c + a);
	setCursor(55, 14); imprimeString(a+c+c+a+" "+a+b+b+a+"  "+c+c+c+b+b+"   "+a+"    "+a+b+b+a);
	setCursor(55, 15); imprimeString(a+"  "+a+" "+a+"  "+a+"  "+a+b+b+b+a+"   "+a+"    "+a+"  "+a);
	setCursor(51, 17); imprimeString(a+c+c+a+" "+a+c+c+a+"  "+a+c+c+c+a+"  "+a+b+"  "+a+" "+c+c+a+c+c+"  "+a+c+c+c+a);
	setCursor(51, 18); imprimeString(a+b+b+a+" "+a+b+b+c+"  "+a+"   "+a+"  "+a+" "+a+" "+a+"   "+a+"    "+a+"   "+a);
	setCursor(51, 19); imprimeString(a+"    "+a+"  "+a+"  "+a+b+b+b+a+"  "+a+"  "+c+a+"   "+a+"    "+a+b+b+b+a);
	cargando(48,21,1,45,3,14,"\260",2);
}

Control::~Control(){

}
