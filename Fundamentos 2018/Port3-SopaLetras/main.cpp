#include "Letras.h"
int main(){
	Letras sopaDeLetras(10,10);
	string palabra;
	string nombre;
	int pts=0;
	char resp='S';
	string Palabras[9]={"TECLADO","BITS","BIOS","WHILE","MOUSE","MONITOR","RAM","CPU","USB"};
	cout<<endl<<endl<<endl;
	cout<<"  . . . . . JUEGO SOPA DE LETRAS . . . . . "<<endl<<endl<<endl<<endl;
	cout<<"  Bienvenid@ al juego de la SOPA DE LETRAS..."<<endl<<endl;
	cout<<"  La tem\240tica de esta sopa de letras es: INFORM\265TICA"<<endl<<endl<<endl<<endl;
	cout<<"  Para empezar, ingrese su nombre de usuario: ";cin>>nombre;
	cout<<endl<<endl<<"  Ahora s\241, comencemos..."<<endl<<endl<<"  Buena suerte, "<<nombre<<endl;
	cout<<"                                              ______________"<<endl;
	cout<<"                                             | ____________ |"<<endl;
	cout<<"                                             ||            ||"<<endl;
	cout<<"                                             || 0110110101 ||"<<endl;
	cout<<"                                             || 0010101011 ||"<<endl;
	cout<<"                                             ||____________||"<<endl;
	cout<<"                                             |______________|"<<endl;
	cout<<"   . . . . . . . . . . . . . . . . . . . . . . . .|___|      "<<endl<<endl<<endl;
	system("pause");
	system("CLS");
	while(resp=='S'||resp=='s'){
		cout<<"           +--------------------------+"<<endl;
		cout<<" 	   |     SOPA DE LETRAS       |"<<endl;
		cout<<" 	   +--------------------------+"<<endl<<endl;
		cout<<"  INFORM\265TICA        "<<"Usuario: "<<nombre<<"       Pts: "<<pts<<endl<<endl;
		sopaDeLetras.llenar();
		cout<<"   -----------------------------------------"<<endl;
		cout<<sopaDeLetras.toString();
		cout<<"   -----------------------------------------"<<endl<<endl;
		cout<<" Pistas"<<endl;
		cout<<" * Ingresa tus palabras en may\243scula."<<endl;
		cout<<" * Hay 9 palabras diferentes en la sopa de letras."<<endl; 
		cout<<" * Las palabras tienen que ver con: hardware, memorias, tama\244os, ciclos y dispositivos E/S."<<endl;
		cout<<"\255Buena suerte!"<<endl;
		cout<<endl<<" Escriba la palabra que desea buscar:"<<endl;
		cout<<" ";cin>>palabra;
		cout<<sopaDeLetras.buscaPalabra(palabra)<<endl;
		cout<<sopaDeLetras.existe()<<endl;
		for(int i=0;i<9;i++){
			if(palabra==Palabras[i]){
				Palabras[i]=" ";
			    if(palabra=="USB"){
					pts=pts+4;
			    }
			    else 
					pts=pts+1;
			}   
		}
		cout<<" Si desea buscar otra palabra digite S, sino digite N"<<endl;
		cout<<" ";cin>>resp;
		system("CLS");
	}
	cout<<endl<<endl<<"  . . . . . FIN DEL JUEGO . . . . ."<<endl<<endl;
	cout<<"  * Tu puntaje final es de: "<<pts<<endl<<endl;
	int verifica=0;
	for(int e=0;e<9;e++){
		if(Palabras[e]==" "){
		verifica=verifica+1;
		}
	}
	if(verifica==9){
	cout<<"Felicitaciones encontraste todas las palabras...";
	}
	else{
	cout<<"  * No encontraste: "<<endl<<endl;	
	for(int e=0;e<9;e++){
		if(Palabras[e]!=" "){
			cout<<"    - "<<Palabras[e]<<endl;
		}
	}
	}
	cout<<endl<<endl;
	cout<<"                                                 ______________"<<endl;
	cout<<"                                                | ____________ |"<<endl;
	cout<<"     Gracias por jugar, "<<nombre<<"                   ||            ||"<<endl;
	cout<<"                                                || 0110110101 ||"<<endl;
	cout<<"     Esperamos que vuelvas pronto               || 0010101011 ||"<<endl;
	cout<<"                                                ||____________||"<<endl;
	cout<<"     \255Hasta luego!                              |______________|"<<endl;
	cout<<"   . . . . . . . . . . . . . . . . . . . . . . . . . .|___|      "<<endl<<endl;
	system("PAUSE");
	return 0;
}
