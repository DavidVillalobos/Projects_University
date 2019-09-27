#ifndef ELECCIONES_H
#define ELECCIONES_H
#include<iostream>
#include <sstream>
#include <time.h>
#include <windows.h>
using namespace std;
class Elecciones
{
private://Declaracion de variables             
	int candidatos;  
	int poblacion;
	int votos[50];
public:  
	//asignación de valores
	Elecciones()    // sin parametros
	{   candidatos = 20;
		poblacion=1000000;
	for(int a=0;a<candidatos;a++){
		votos[a]= 0;
	}
	}
	Elecciones(int pCandidatos, int pPoblacion) //con parametros
	{
		candidatos=pCandidatos;
		poblacion=pPoblacion;
		for(int a=0;a<candidatos;a++){
			votos[a]= 0;
		}
	}
	//		//Metodos Set
	void setcandidatos(int pCandidatos)
	{ 
		candidatos=pCandidatos;
	}
	void setpoblacion(int pPoblacion)
	{ 
		poblacion=pPoblacion; 
	}
	//		//Metodos Get
	int getcandidatos()
	{ 
		return (candidatos); 
	}
	int getpoblacion()
	{ 
		return (poblacion); 
	}
	~Elecciones(){} //Destruir la clase
	// metodos
	void votaciones(){    //Metodo que llena el vector con valores al azar
		//limites para que los votos sean mas altos
		srand(time(NULL)); //semilla
		Sleep(1000);
		int superior=poblacion;  //limite superior
		int inferior=30000; // limite inferior
		for(int a=0;a<candidatos;a++){
			if(superior>0){
				votos[a]=inferior + rand() % (superior-inferior);
				superior=superior-votos[a];
			}
		}
	}
	string toString(){  //Imprime el resultado de las elecciones
		stringstream s;
		for(int e=0; e<candidatos; e++)
			s<<"El candidato "<<e<<" tiene "<<votos[e]<<" votos"<<endl;
		return s.str();
	}
	
	int posmayor(){  //Imprime el candidato con mas votos
		int max=votos[0];
		int posmax=0;
		for(int i=0;i<candidatos;i++)
		{	if(votos[i]>max)
			{	max=votos[i];
				posmax=i;
			}
		}
		return posmax;
	}
	
	string toStringOrdenado(){    //imprime los datos ordenados
		stringstream s;
		int votos2[candidatos];//crear un nuevo vector votos2
		for(int e=0; e<candidatos;e++){//inicializa los datos para evitar valores basura
			votos2[e]=0;
		}
		for(int e=0; e<candidatos;e++){
			votos2[e]=votos[e];//copiar los datos para que los originales no sean modificados
		}
		int aux;
		for(int a=0;a<candidatos;a++){	//Ordena los datos metodo burbuja
			for(int i=0;i<candidatos;i++){
				if(votos2[i]>votos2[i+1]){
					aux=votos2[i];
					votos2[i]=votos2[i+1];
					votos2[i+1]=aux;
				}
			}	
		}
		for(int i=1; i<candidatos;i++){
			s<<""<<votos2[i]<<endl; //Muestra los datos
		}
		s<<endl;
		return s.str();
	}
	
	int emitidos(){     //metodo que calcula los datos emitidos 
		int emitidos=0;
		for(int a=0; a<candidatos; a++){
			emitidos=emitidos+votos[a];
		}
		return emitidos;
	}
	
	string toStringMayor(){ //30% o más del total de los votos emitidos.
		stringstream s;
		int aux=0;
		for(int e=0; e<candidatos; e++){
			if(30<=((votos[e]*100)/emitidos())){
				aux=1;
				s<<e<<" ";
			}
		}
		if(aux==0){
			s<<"Ninguno";
		}
		return s.str();
	}
	bool hayGanador(){ //declara si hay o no un ganador con mas del 40% de votos.
		for(int e=0; e<candidatos; e++){
			if(40<=(votos[e]*100/poblacion)){
				return true;
			}
		}
		return false;
	}
	
	int abstencionismo(){//devuelve el porcentaje de quienes no votaron
		/*int aux=0;
		for(int i=0; i<candidatos; i++){
			aux=aux+votos[i];
		}
		aux=((poblacion-aux)*100/poblacion);*/
		return poblacion-emitidos();
		
	}
	
	string declaracionGanador(){  //devuelve el ganador y sino hay segunda ronda
		stringstream s;
		if(hayGanador()==true){
			s<<posmayor(); //muestra el ganador
		}
		else{
			int posmax2=0;
			int max2=votos[0];
			for(int i=0;i<candidatos;i++)
			{	
				if(i==posmayor()){
					i=i+1;
				}
				if(votos[i]>max2)
				{
					max2=votos[i];
					posmax2=i;
				}
			}
		s<<"Ninguno, deberan ir a segunda ronda el candidato "<<posmax2<<" y el "<<posmayor();
		}
		s<<endl;
		return s.str();
	}
	
	string toStringCompara(Elecciones X){ //muestra los datos comparados con una eleccion anterior
		stringstream s;
		s<<"   Datos de la eleccion pasada:"<<endl;	
		s<<"Candidatos: "<<X.getcandidatos()<<endl;
		s<<"Poblacion: "<<X.getpoblacion()<<endl;
		s<<"Votos emitidos: "<<X.emitidos()<<endl;
		s<<"Candidato ganador: "<<X.posmayor()<<endl;
		s<<"Abstencionismo: "<<X.abstencionismo()<<endl<<endl;
		s<<"   Datos de la eleccion actual"<<endl;
		s<<"Candidatos: "<<getcandidatos()<<endl;
		s<<"Poblacion : "<<getpoblacion()<<endl;
		s<<"Votos emitidos: "<<emitidos()<<endl;
		s<<"Candidato ganador: "<<posmayor()<<endl;
		s<<"Abstencionismo: "<<abstencionismo()<<endl<<endl;
		return s.str();
	}
};
#endif
