#ifndef ESTUDIANTES_H
#define ESTUDIANTES_H
#include<iostream>       //Inclusion de librerias
#include<sstream>
#include<string>

using namespace std;

class Estudiantes        //definir la clase
{
private:           //Declarar los atributos en privado
	string cedula;
	string nombre;
	float nota1;
	float nota2;
	float nota3;
	float nota4;
	//Crear los constructores "inicializadores de valores"
	//sin parametros "Valores predefinidos"
public:            
	Estudiantes()          
	{
		cedula = "No ha sido asignada";
		nombre = "No ha sido asignado";
		nota1 = 0;
		nota2 = 0;
		nota3 = 0;
		nota4 = 0;	
	}
	//Constructor con parametros "Valores asignados por el Usuario"
	Estudiantes(string pCedula, string pNombre, float pNota1, float pNota2, float pNota3, float pNota4)   
	{
		cedula = pCedula;
		nombre = pNombre;
		nota1 = pNota1;
		nota2 = pNota2;
		nota3 = pNota3;
		nota4 = pNota4;
	}
	//metodo set para cambiar el valor de una variable
	void setcedula(string pCedula)   
	{
		cedula= pCedula;	
	}
	void setnombre(string pNombre)   
	{
		nombre= pNombre;	
	}
	void setnota1(float pNota1)   
	{
		nota1= pNota1;	
	}
	void setnota2(float pNota2)   
	{
		nota2= pNota2;	
	}
	void setnota3(float pNota3)   
	{
		nota3= pNota3;	
	}
	void setnota4(float pNota4)   
	{
		nota4= pNota4;	
	}
	
	//metodo get para mostrar el valor de una variable
	
	string getcedula()
	{
		return (cedula);
	}
	string getnombre()
	{
		return (nombre);
	}
	float getnota1()        
	{
		return (nota1);
	}   
	float getnota2()        
	{
		return (nota2);
	} 
	float getnota3()        
	{
		return (nota3);
	} 
	float getnota4()        
	{
		return (nota4);
	} 
	
	~Estudiantes(){
		 //Destructor de la clase
	}    
	//Definicion de Metodos
	
	float Calcularpromedio()  //metodo Calcularpromedio()= Nota final
	{
		float Calcularpromedio = (nota1*0.30)+(nota2*0.25)+(nota3*0.35)+(nota4*0.10);
		return Calcularpromedio;
	}
	
	string detResultado() //metodo detResultado() = Estado final del estudiante en el curso
	{
		if (Calcularpromedio()>=70){
			return " APROBADO";
		}
		else {
			if ((Calcularpromedio()<70)&&(Calcularpromedio()>=60)){
				return " EXTRAORDINARIO";
			}
			else return " REPROBADO";
		}
	}
	
	string tostring()   //metodo tostring()
	{
		stringstream s;
		
		s<<"LOS DATOS DEL ESTUDIANTE"<<endl<<endl;
		s<<"Nombre: "<<nombre<<endl;
		s<<"Cedula: "<<cedula<<endl;
		s<<"Nota 1: "<<nota1<<endl;
		s<<"Nota 2: "<<nota2<<endl;
		s<<"Nota 3: "<<nota3<<endl;
		s<<"Nota 4: "<<nota4<<endl;
		s<<"Promedio final: "<<Calcularpromedio()<<endl;
		s<<"Condicion del estudiante"<<detResultado()<<endl;
		
		return s.str();
	}
	
};
#endif
