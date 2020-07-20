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
	while (!winner) {
		play_player(j1);
		play_player(j2);
	}
	printString(tablero.toString());
	system("pause");
}

void Game::play_player(Player j){
	int columna, fila;
	while (true) {
		printString("Turno de " + j.getName() + '\n');
		printString("Digite una fila: ");
		fila = getInt();
		printString("Digite una columna: ");
		columna = getInt();
		if (tablero.setSimb(fila, columna, 'O')) {
			printString("Ficha colocada correctamente\n");
			break;
		}
		printString("Digito un dato fuera de rango o ya esta ocupado\n");
	}
	if (tablero.haveWinner()) {
		printString("El jugador " + j.getName() + " ha ganado!");
	}
}

Game::~Game(){
}
