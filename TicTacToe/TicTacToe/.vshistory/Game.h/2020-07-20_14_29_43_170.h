#ifndef GAME_H
#define GAME_H
#include"ViewConsole.h"
#include"Player.h"
#include "Board.h"
class Game{
	Board tablero;
	Player j1, j2;
public:
	Game();
	void start();
	void play();
	bool play_player(Player j);
	~Game();
};
#endif GAME_H