#include "Estudiantes.h" //Inclusion de la clase
#include<iostream>       //Inclusion de librerias
#include<sstream>
#include<string>

using namespace std;

int main()
{
	string cedula;
	string nombre;
	float nota1;
	float nota2;          //Declaracion de variables y objetos de la clase
	float nota3;
	float nota4;
	int MenuPrincipal =0;
	Estudiantes est1;
	do{    //entrar al bucle del Menu Principal
		cout<<endl;             //Mandar a la consola los datos del menu
		cout<<"        COLEGIO FORMACION INTEGRAL S.A"<<endl<<endl;
		cout<<" Menu principal"<<endl;
		cout<<" 1) Asignar estudiante"<<endl;
		cout<<" 2) Calcular nota del estudiante"<<endl;
		cout<<" 3) Mostrar estudiante"<<endl;
		cout<<" 4) Salir"<<endl;
		cout<<endl;
		cout<<"Introduzca el numero de la accion a realizar:"<<endl;
		cin>>MenuPrincipal;
		switch (MenuPrincipal) //Menu de opciones principales
		{
			case 1:      //Opcion 1 asignar estudiante
			{
				cout<<system("CLS");
				cout<<"             Asignar Estudiante"<<endl;
				cout<<"Introduzca la cedula: "<<endl;
				cin>>cedula;
				cout<<"Introduzca El nombre: "<<endl;
				cin>>nombre;
				est1.setcedula(cedula);
				est1.setnombre(nombre);
				cout<<system("PAUSE");
				cout<<system("CLS");
				break;
			}
			case 2:     // opcion 2 calcular la nota del estudiante
			{
				cout<<system("CLS");
				cout<<"             Calcular la Nota"<<endl;
				cout<<"  Introduzca las notas del estudiante "<<nombre<<endl;
				cout<<"Nota 1: "<<endl;
				cin>>nota1;
				cout<<"Nota 2: "<<endl;
				cin>>nota2;
				cout<<"Nota 3: "<<endl;
				cin>>nota3;
				cout<<"Nota 4: "<<endl;
				cin>>nota4;
				cout<<endl;
				est1.setnota1(nota1);
				est1.setnota2(nota2);
				est1.setnota3(nota3);
				est1.setnota4(nota4);
				cout<<"El Promedio final del estudiante es: "<<est1.Calcularpromedio()<<endl;
				cout<<system("PAUSE");
				cout<<system("CLS");
				break;
			}
			case 3:     //opcion 3 mostrar estudiante
			{
				cout<<system("CLS");
				cout<<est1.tostring()<<endl;
				cout<<system("PAUSE");
				cout<<system("CLS");
				break;
			}
			default:    // En caso que digito otro numero a exepcion del 4 que termina el bucle
			{
				if(MenuPrincipal!= 4 )
				{
					cout<<"EL numero que ingreso no esta en el Menu"<<endl;
					cout<<system("PAUSE");
					cout<<system("CLS");
					break;
				}
				else
				break;
			}
		}
	} while(MenuPrincipal!=4);
	return 0; //Termina el programa
}	
