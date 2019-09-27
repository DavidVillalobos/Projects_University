#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const int fila=30;
const int col=30;

class Letras{
	
private:
	
	char matriz[fila][col];
	int canFila, canCol;
	bool x=false;
	
public:
	
	Letras(){
		for(int i=0;i<fila;i++){
			for(int j=0;j<col;j++){
				matriz[i][j]=' ';	
			}
		}
		canFila=fila;
		canCol=col;
	}
	
	Letras(int pFila,int pCol){
		canFila=pFila;
		canCol=pCol;
		for(int i=0;i<canFila;i++){
			for(int j=0;j<canCol;j++){
				matriz[i][j]=' ';	
			}
		}
	}	
	
	
	char getLetra(int pFila,int pCol){
		return matriz[pFila][pCol];
	}
	int getCanCol(){
		return canCol;
	}
	int getcanFila(){
		return canFila;
	}
	
	void setLetra(int pFila,int pCol, char letra){
		matriz[pFila][pCol]=letra;
	}
	void setCanCol(int pCol){
		if (pCol < col)
			canCol=pCol;
	}
	void setCanFila(int pFila){
		if (pFila < fila)
			canFila=pFila;
	}
	
	void llenar(){
		matriz[0][0]='X'; matriz[0][1]='P'; matriz[0][2]='F'; matriz[0][3]='T';	matriz[0][4]='U'; matriz[0][5]='D'; matriz[0][6]='G'; matriz[0][7]='I'; matriz[0][8]='T'; matriz[0][9]='Y';
		matriz[1][0]='S'; matriz[1][1]='T'; matriz[1][2]='E'; matriz[1][3]='C'; matriz[1][4]='L'; matriz[1][5]='A'; matriz[1][6]='D'; matriz[1][7]='O'; matriz[1][8]='A'; matriz[1][9]='H';
		matriz[2][0]='T'; matriz[2][1]='M'; matriz[2][2]='R'; matriz[2][3]='H'; matriz[2][4]='M'; matriz[2][5]='U'; matriz[2][6]='W'; matriz[2][7]='M'; matriz[2][8]='M'; matriz[2][9]='G';					
		matriz[3][0]='I'; matriz[3][1]='K'; matriz[3][2]='A'; matriz[3][3]='A';	matriz[3][4]='E'; matriz[3][5]='E'; matriz[3][6]='P'; matriz[3][7]='Z';	matriz[3][8]='O'; matriz[3][9]='F';			
		matriz[4][0]='B'; matriz[4][1]='A'; matriz[4][2]='G'; matriz[4][3]='R'; matriz[4][4]='X'; matriz[4][5]='B'; matriz[4][6]='Q'; matriz[4][7]='C'; matriz[4][8]='N'; matriz[4][9]='A';
		matriz[5][0]='S'; matriz[5][1]='F'; matriz[5][2]='A'; matriz[5][3]='I'; matriz[5][4]='E'; matriz[5][5]='S'; matriz[5][6]='O'; matriz[5][7]='Y'; matriz[5][8]='I'; matriz[5][9]='E';
		matriz[6][0]='W'; matriz[6][1]='O'; matriz[6][2]='H'; matriz[6][3]='L'; matriz[6][4]='S'; matriz[6][5]='U'; matriz[6][6]='S'; matriz[6][7]='B'; matriz[6][8]='T'; matriz[6][9]='R';
		matriz[7][0]='E'; matriz[7][1]='W'; matriz[7][2]='I'; matriz[7][3]='G'; matriz[7][4]='W'; matriz[7][5]='S'; matriz[7][6]='S'; matriz[7][7]='F'; matriz[7][8]='O'; matriz[7][9]='T';
		matriz[8][0]='R'; matriz[8][1]='H'; matriz[8][2]='H'; matriz[8][3]='B'; matriz[8][4]='I'; matriz[8][5]='B'; matriz[8][6]='Y'; matriz[8][7]='B'; matriz[8][8]='R'; matriz[8][9]='I';
		matriz[9][0]='W'; matriz[9][1]='R'; matriz[9][2]='E'; matriz[9][3]='S'; matriz[9][4]='U'; matriz[9][5]='O'; matriz[9][6]='M'; matriz[9][7]='T'; matriz[9][8]='A'; matriz[9][9]='O';
	}
	
	string toString(){
		stringstream s;
		for(int i=0;i<canFila;i++){
			s<<"   ";
			for(int j=0;j<canCol;j++){
				s<<"| "<<matriz[i][j]<<" ";
			}
			s<<"|"<<endl;
		}	
		return s.str();
	}
	
	string buscaDerecha(string palabra){
		stringstream s;
		for(int i=0, a=0;i<canFila;i++){
			for(int j=0; j<canCol; j++){
				if(matriz[i][j]==palabra[a]){
					a++;
					if(palabra.length()==a){
						s<<" Est\240 en la posici\242n ["<<i<<","<<(j-palabra.length())+1<<"] hacia la derecha."<<endl;
						x=true;
					}
				}
				else{
					a=0;}
			}
			a=0;
		}
		return s.str();
	}
	
	string buscaAbajo(string palabra){
		stringstream s;
		for(int j=0, a=0;j<canCol;j++){
			for(int i=0; i<canFila; i++){
				if(matriz[i][j]==palabra[a]){
					a++;
					if(palabra.length()==a){
						s<<" Est\240 en la posici\242n ["<<(i-palabra.length())+1<<","<<j<<"] hacia abajo."<<endl;
						x=true;
					}
				}
				else{
					a=0;}
			}
			a=0;
		}
		return s.str();
	}
	
	
	string buscaIzquierda(string palabra){
		stringstream s;
		for(int i=canFila-1, a=0;i>=0;i--){
			for(int j=canCol-1; j>=0; j--){
				if(matriz[i][j]==palabra[a]){
					a++;
					if(palabra.length()==a){
						s<<" Est\240 en la posici\242n ["<<i<<","<<(j+palabra.length())-1<<"] hacia la izquierda."<<endl;
						x=true;
					}
				}
				else{
					a=0;}
			}
			a=0;
		}
		return s.str();
	}
	
	string buscaArriba(string palabra){
		stringstream s;
		for(int j=canCol-1, a=0;j>=0;j--){
			for(int i=canFila-1; i>=0; i--){
				if(matriz[i][j]==palabra[a]){
					a++;
					if(palabra.length()==a){
						s<<" Est\240 en la posici\242n ["<<(i+palabra.length())-1<<","<<j<<"] hacia arriba."<<endl;
						x=true;
					}
				}
				else{
					a=0;
				}
			}
			a=0;
		}
		return s.str();
	}
	
	string buscaDiagonalDerechaAbajo(string palabra){
		stringstream s;
		int a=0;
		for(int j=0;j<canCol;j++){
			for(int i=0;i<canFila-j;i++){
				if(matriz[i][j+i]==palabra[a]){
					a++;
					if((palabra.length())==a){
						s<<" Est\240 en la posici\242n ["<<i-palabra.length()+1<<","<<j+i-palabra.length()+1<<"] hacia la derecha y abajo diagonalmente."<<endl;
						x=true;
					}
				} 
				else{
					a=0;}
			}
			a=0;
		}
		for(int i=1;i<canFila;i++){
			for(int j=0;j<canCol-i;j++){
				if(matriz[i+j][j]==palabra[a]){
					a++;
					if((palabra.length())==a){
						s<<" Est\240 en la posici\242n ["<<i+j-palabra.length()+1<<","<<j-palabra.length()+1<<"] hacia la derecha y abajo diagonalmente."<<endl;
						x=true;
					}
				} 
				else{
					a=0;}
			}
			a=0;
		}
		return s.str();
	}
	
	string buscaDiagonalIzquierdaAbajo(string palabra){
		stringstream s;
		int iAux;
		int a=0;
		for(int j=canCol-1;j>=0;j--){
			for(int i=0;i<j+1;i++){
				if(matriz[i][j-i]==palabra[a]){
					a++;
					if((palabra.length())==a){
						s<<" Est\240 en la posici\242n ["<<i-palabra.length()+1<<","<<j-i+palabra.length()-1<<"] hacia la izquierda y abajo diagonalmente."<<endl;
						x=true;
					}
				} 
				else{
					a=0;}
			}
			a=0;
		}
		for(int i=1;i<canFila;i++){
			iAux=i;
			for(int j=canCol-1;j>0;j--){
				if(matriz[iAux++][j]==palabra[a]){
					a++;
					if((palabra.length())==a){
						s<<" Est\240 en la posici\242n ["<<iAux-palabra.length()<<","<<j+palabra.length()-1<<"] hacia la izquierda y abajo diagonalmente."<<endl;
						x=true;
					}
				} 
				else{
					a=0;}
			}
			a=0;
		}
		return s.str();
	}
	
	string buscaDiagonalIzquierdaArriba(string palabra){
		stringstream s;
		int jAux, iAux=0;
		int a=0;
		for(int j=canCol-1;j>=0;j--, iAux++){
			jAux=0;
			for(int i=canFila-1;i>=iAux;i--, jAux++){
				if(matriz[i][j-jAux]==palabra[a]){
					a++;
					if((palabra.length())==a){
						s<<" Est\240 en la posici\242n ["<<i+palabra.length()-1<<","<<(j-jAux)+1+palabra.length()-2<<"] hacia la izquierda y arriba diagonalmente."<<endl;
						x=true;
					}
				} 
				else{
					a=0;}
			}
			a=0;
		}
		jAux=0;
		for(int i=canFila-2;i>=0;i--, jAux++){
			iAux=i;
			for(int j=canCol-1;j>jAux;j--){
				if(matriz[iAux--][j]==palabra[a]){
					a++;
					if((palabra.length())==a){
						s<<" Est\240 en la posici\242n ["<<iAux+palabra.length()<<","<<j+palabra.length()-1<<"] hacia la izquierda y arriba diagonalmente."<<endl;
						x=true;
					}
				} 
				else{
					a=0;}
			}
			a=0;
		}
		return s.str();
	}
	
	string buscaDiagonalDerechaArriba(string palabra){
		stringstream s;
		int jAux;
		int a=0;
		for(int j=0;j<canCol;j++){
			jAux=j;
			for(int i=canFila-1;i>=j;i--){
				if(matriz[i][jAux++]==palabra[a]){
					a++;
					if((palabra.length())==a){
						s<<" Est\240 en la posici\242n ["<<i+palabra.length()-1<<","<<jAux-1-palabra.length()+1<<"] hacia la derecha y arriba diagonalmente."<<endl;
						x=true;
					}
				} 
				else{
					a=0;}
			}
			a=0;
		}
		for(int i=canFila-2;i>=0;i--){
			for(int j=0;j<canCol-i;j++){
				if(matriz[i-j][j]==palabra[a]){
					a++;
					if(palabra.length()==a){
						s<<" Est\240 en la posici\242n ["<<i-j+palabra.length()-1<<","<<j-palabra.length()+1<<"] hacia la derecha y arriba diagonalmente."<<endl;
						x=true;
					}
				} 
				else{
					a=0;}
			}
			a=0;
		}
		return s.str();
	}
	
	string buscaPalabra(string palabra){
		stringstream s;
		s<<buscaAbajo(palabra);
		s<<buscaArriba(palabra);
		s<<buscaDerecha(palabra);
		s<<buscaIzquierda(palabra);
		s<<buscaDiagonalDerechaAbajo(palabra);
		s<<buscaDiagonalDerechaArriba(palabra);
		s<<buscaDiagonalIzquierdaAbajo(palabra);
		s<<buscaDiagonalIzquierdaArriba(palabra);
		return s.str();
	}
	
	string existe(){
		stringstream s;
		if(!x)
			s<<" La palabra no est\240 en la sopa de letras."<<endl;
		x=false;
		return s.str();	
	}
	
	~Letras(){}
	
};