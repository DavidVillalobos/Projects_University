#include <Windows.h> 
#include <iostream>
#include <string>
using std::string;
using std::cout;
void setColor(int col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
	//Azul Oscuro (1) Verde Oscuro (2) Cian Oscuro (3) Rojo Oscuro (4) Morado Oscuro (5)
	//Amarillo Oscuro (6) Blanco (7) Gris (8) Azul brillante (9) Verde brillante (10) Cian brillante (11)
	//Rojo brillante (12) Morado brillante (13) Amarillo brillante (14) Blanco Brillante (15)
	//BACKGROUND_GREEN    BACKGROUND_GREEN    BACKGROUND_RED
}
void setCursor(int x, int y) {
	HANDLE hcon; //Variable de ventanas
	hcon = GetStdHandle(STD_OUTPUT_HANDLE); //obtener Ventana actual
	COORD dwPos; //Variable de coordenadas
	dwPos.X = x; //guarde la x
	dwPos.Y = y; // guarde la y
	SetConsoleCursorPosition(hcon, dwPos);
	// Este método recibe una ventana y pone el cursor en la coordenada
}
void imprimeAbecedario() {
	string a = "\311";//╔
	string b = "\273";//╗
	string c = "\274";//╝
	string d = "\310";//╚
	string e = "\313";//╦
	string f = "\271";//╣
	string g = "\316";//╬
	string h = "\312";//╩
	string i = "\314";//╠
	string j = "\272";//║	
	string k = "\315";//═   
	//A
	cout << a + k + k + k + k + k + b + "\n";
	cout << j + " " + a + k + b + " " + j + "\n";
	cout << j + " " + d + k + c + " " + j + "\n";
	cout << j + " " + a + k + b + " " + j + "\n";
	cout << j + " " + j + " " + j + " " + j + "\n";
	cout << d + k + c + " " + d + k + c + "\n\n";
	//B
	cout << a + k + k + k + k + k + b + "\n";
	cout << j + " " + a + k + b + " " + j + "\n";
	cout << j + " " + d + k + c + " " + d + b + "\n";
	cout << j + " " + a + k + k + b + " " + j + "\n";
	cout << j + " " + d + k + k + c + " " + j + "\n";
	cout << d + k + k + k + k + k + k + c + "\n\n";
	//C
	cout << a + k + k + k + k + k + b + "\n";
	cout << j + " " + a + k + b + " " + j + "\n";
	cout << j + " " + j + " " + d + k + c + "\n";
	cout << j + " " + j + " " + a + k + b + "\n";
	cout << j + " " + d + k + c + " " + j + "\n";
	cout << d + k + k + k + k + k + c + "\n\n";
	//D
	cout << a + k + k + k + k + k + b + "\n";
	cout << j + " " + a + k + b + " " + d + b + "\n";
	cout << j + " " + j + " " + d + b + " " + j + "\n";
	cout << j + " " + j + " " + a + c + " " + j + "\n";
	cout << j + " " + d + k + c + " " + a + c + "\n";
	cout << d + k + k + k + k + k + c + "\n\n";
	//E
	cout << a + k + k + k + k + k + b + "\n";
	cout << j + " " + a + k + k + k + c + "\n";
	cout << j + " " + d + k + k + k + b + "\n";
	cout << j + " " + a + k + k + k + c + "\n";
	cout << j + " " + d + k + k + k + b + "\n";
	cout << d + k + k + k + k + k + c + "\n\n";
	//F
	cout << a + k + k + k + k + k + b + "\n";
	cout << j + " " + a + k + k + k + c + "\n";
	cout << j + " " + d + k + k + k + b + "\n";
	cout << j + " " + a + k + k + k + c + "\n";
	cout << j + " " + j + "\n";
	cout << d + k + c + "\n\n";
	//G
	cout << a + k + k + k + k + k + b + "\n";
	cout << j + " " + a + k + b + " " + j + "\n";
	cout << j + " " + j + " " + d + k + c + "\n";
	cout << j + " " + j + a + k + k + b + "\n";
	cout << j + " " + j + d + b + " " + j + "\n";
	cout << j + " " + d + k + c + " " + j + "\n";
	cout << d + k + k + k + k + k + c + "\n\n";
	//H
	cout << a + k + b + " " + a + k + b + "\n";
	cout << j + " " + j + " " + j + " " + j + "\n";
	cout << j + " " + d + k + c + " " + j + "\n";
	cout << j + " " + a + k + b + " " + j + "\n";
	cout << j + " " + j + " " + j + " " + j + "\n";
	cout << d + k + c + " " + d + k + c + "\n\n";
	//I
	cout << a + k + k + k + k + k + b + "\n";
	cout << d + k + b + " " + a + k + c + "\n";
	cout << "  " + j + " " + j + "\n";
	cout << "  " + j + " " + j + "\n";
	cout << a + k + c + " " + d + k + b + "\n";
	cout << d + k + k + k + k + k + c + "\n\n";
	//J
	cout << a + k + k + k + k + k + b + "\n";
	cout << d + k + k + b + " " + a + c + "\n";
	cout << "   "+j + " " + j + "\n";
	cout << a + k + b + j + " " + j + "\n";
	cout << j + " " + d + c + " " + j + "\n";
	cout << d + k + k + k + k + c + "\n\n";
	//O
	cout << a + k + k + k + k + k + b + "\n";
	cout << j + " " + a + k + b + " " + j + "\n";
	cout << j + " " + j + " " + j + " " + j + "\n";
	cout << j + " " + j + " " + j + " " + j + "\n";
	cout << j + " " + d + k + c + " " + j + "\n";
	cout << d + k + k + k + k + k + c + "\n\n";
	//T
	cout << a + k + k + k + k + k + b + "\n";
	cout << d + k + b + " " + a + k + c + "\n";
	cout << "  "+j + " " + j + "\n";
	cout << "  "+j + " " + j + "\n";
	cout << "  "+j + " " + j + "\n";
	cout << "  "+d + k + c + "\n";
}
int main() {
	imprimeAbecedario();
	system("pause");
	return 0;
}