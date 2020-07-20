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
		matriz[i][j] = simb;
		return true;
	}
	return false;
}
