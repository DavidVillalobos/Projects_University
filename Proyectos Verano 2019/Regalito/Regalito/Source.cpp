#include <windows.h>
#include <iostream>
using std::cout;
void setColor(int color) {
	HANDLE hcon; // Ventanas
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);// Obtener Ventana Actual
	SetConsoleTextAttribute(hcon,color);// cambiar el color de la Ventana
	//Azul Oscuro (1) Verde Oscuro (2) Cian Oscuro (3) Rojo Oscuro (4) Morado Oscuro (5)
	//Amarillo Oscuro (6) Blanco (7) Gris (8) Azul brillante (9) Verde brillante (10) Cian brillante (11)
	//Rojo brillante (12) Morado brillante (13) Amarillo brillante (14) Blanco Brillante (15)
}

void setCursor(int x, int y) {
	HANDLE hcon; //Ventanas
	hcon = GetStdHandle(STD_OUTPUT_HANDLE); //obtener Ventana actual
	COORD dwPos; //Coordenadas
	dwPos.X = x; // Actualice x
	dwPos.Y = y; // Actualice y
	SetConsoleCursorPosition(hcon, dwPos);// Este método recibe una ventana y pone el cursor en la coordenada de esa ventana
}

void Regalo(int X, int Y,int colorCaja, int colorLazo) {
	setCursor(X, Y); setColor(colorLazo); cout << " \333\337\337\337\333  \333\337\337\337\333"; Y++;
	setCursor(X, Y); cout<<" \333\334  \333\334\334\333  \334\333"; Y++;
	setCursor(X, Y); cout<<"  \333\334\334\334\333\333\334\334\334\333";setColor(colorCaja); Y++;
	setCursor(X, Y); cout <<"\333\333\333\333\333\333"; setColor(colorLazo); cout<<"\333\333"; setColor(colorCaja); cout<<"\333\333\333\333\333\333"; Y++;
	setCursor(X, Y); cout << "\333\333\333\333\333\333"; setColor(colorLazo); cout << "\333\333"; setColor(colorCaja); cout << "\333\333\333\333\333\333";setColor(colorLazo); Y++;
	setCursor(X, Y); cout <<"\333\333\333\333\333\333"; cout <<"\333\333"; cout <<"\333\333\333\333\333\333";setColor(colorCaja); Y++;
	setCursor(X, Y); cout << "\333\333\333\333\333\333"; setColor(colorLazo); cout << "\333\333"; setColor(colorCaja); cout << "\333\333\333\333\333\333"; Y++;
	setCursor(X, Y); cout << "\333\333\333\333\333\333"; setColor(colorLazo); cout << "\333\333"; setColor(colorCaja); cout << "\333\333\333\333\333\333"; Y++; setColor(8);
}

void arbol(int X, int Y) {
	
}
void main() {
	Regalo(10,10,12,10);
	system("pause");
}