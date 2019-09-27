#include "Elecciones.h"
using namespace std;
int main(){
	Elecciones ELECCION_PROCESO1_XXXX;
	Elecciones ELECCION_PROCESO1_2018;
	ELECCION_PROCESO1_2018.votaciones();
	ELECCION_PROCESO1_XXXX.votaciones();
	cout<<"                      Elecciones presidenciales ENSUENO"<<endl;
	cout<<"Los resultados de las elecciones 2018: "<<endl<<ELECCION_PROCESO1_2018.toString()<<endl;
	cout<<"El Candidato con mas votos: "<<ELECCION_PROCESO1_2018.posmayor()<<endl<<endl;
	cout<<"Los resultados de menor a mayor son:"<<endl<<ELECCION_PROCESO1_2018.toStringOrdenado();
	cout<<"Los candidatos con 30 % o mas de votos: "<<ELECCION_PROCESO1_2018.toStringMayor()<<endl<<endl;
	cout<<"Existe un ganador: "<<ELECCION_PROCESO1_2018.hayGanador()<<endl<<endl;
	cout<<"El abstencionismo: "<<ELECCION_PROCESO1_2018.abstencionismo()<<endl<<endl;
	cout<<"El ganador: "<<ELECCION_PROCESO1_2018.declaracionGanador()<<endl;
	Elecciones ELECCION_PROCESO2_2018;
	if(ELECCION_PROCESO1_2018.hayGanador()==false){
		ELECCION_PROCESO2_2018.votaciones();
		cout<<"          SEGUNDO PROCESO DE ELECCIONES 2018"<<endl<<endl;
		cout<<"El Candidato Ganador: "<<ELECCION_PROCESO2_2018.posmayor()<<endl<<endl;
		cout<<"El abstencionismo es: "<<ELECCION_PROCESO2_2018.abstencionismo()<<endl<<endl;
	}
	cout<<"     DATOS COMPARATIVOS"<<endl<<endl;
	if(ELECCION_PROCESO1_2018.hayGanador()==true){
		cout<<ELECCION_PROCESO1_2018.toStringCompara(ELECCION_PROCESO1_XXXX);
	}
	if(ELECCION_PROCESO1_2018.hayGanador()==false){
		cout<<ELECCION_PROCESO2_2018.toStringCompara(ELECCION_PROCESO1_XXXX);
	}

	return 0;
};


	
	
