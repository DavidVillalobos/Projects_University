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
		//if --> no exista ganador o no exista empate
		//  j1 --> jugar
		// else break;
		//if --> no exista ganador o no exista empate
		//  j2 --> jugar
		// else break;
	}
	printString(tablero.toString());
	system("pause");
}

Game::~Game(){
}
