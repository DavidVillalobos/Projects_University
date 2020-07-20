#include "Board.h"

Board::Board(){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			matriz[i][j] = ' ';
		}
	}
	spaceAvailable = 9;
}

bool Board::setSimb(int i, int j, char simb){
	if (0 < spaceAvailable) {
		if (-1 < i && i < 3 && -1 < j && j < 3) {
			matriz[i][j] = simb;
		}
		return true;
	}
	return false;
}

char Board::getSimb(int i, int j){
	if (-1 < i && i < 3 && -1 < j && j < 3) {
		return matriz[i][j];
	}
}

bool Board::haveWinner(){
	for (int i = 0; i < 3; i++) {
		if (matriz[i][0] != ' ' && matriz[i][0] == matriz[i][1] && matriz[i][1] == matriz[i][2]) {
			return true;
		}
	}
	// [0,0][0,1][0,2]
	// [1,0][1,1][1,2]
	// [2,0][2,1][2,2]
	
	return false;
}

bool Board::haveTie(){
	return false;
}
