#include "Game.h"

Game::Game(){
}

void Game::start(){
	while (true) {
		setColor(10);
		printString("\t\tTic Tac Toe\n\n");
		setColor(15);
		printString(" 1] Jugar\n");
		printString(" 2] Salir\n\n");
		switch (getInt()){
			case 1: play();  break;
			case 2: return;
			default: break;
		}
		system("cls");
	}
}

void Game::play(){
	system("cls");
	bool winner = false;
	int columna, fila;
	while (!winner) {
		printString("Turno de " + j1.getName() + '\n');
		printString("Digite una columna: ");
		columna = getInt();
		printString("Digite una fila: ");
		fila = getInt();
		if (tablero.setSimb(fila, columna, 'O')) {
			printString("Ficha colocada correctamente\n");
		}else {
			printString("Digito un dato fuera de rango\n");
		}
		
		//  j2 --> jugar
		//if --> no exista ganador o no exista empate
		// else break;
	}
	printString(tablero.toString());
	system("pause");
}

void Game::play_player(Player j)
{
}

Game::~Game(){
}
