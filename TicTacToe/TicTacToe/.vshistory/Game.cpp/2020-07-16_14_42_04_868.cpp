#include "Game.h"

Game::Game(){
}

void Game::start(){
	while (true) {
		printString("\t\tTic Tac Toe\n\n");
		printString(" 1] Jugar\n");
		printString(" 2] Salir\n");
		break;
	}
}

Game::~Game(){
}
