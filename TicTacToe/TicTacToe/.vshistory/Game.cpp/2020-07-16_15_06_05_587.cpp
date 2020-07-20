#include "Game.h"

Game::Game(){
}

void Game::start(){
	while (true) {
		printString("\t\tTic Tac Toe\n\n");
		printString(" 1] Jugar\n");
		printString(" 2] Salir\n\n");
		switch (getInt()){
			case 1: play();  break;
			case 2: return;
			default: break;
		}
		system("cls");
		break;
	}
}

void Game::play(){
	printString(tablero.toString());
}

Game::~Game(){
}
