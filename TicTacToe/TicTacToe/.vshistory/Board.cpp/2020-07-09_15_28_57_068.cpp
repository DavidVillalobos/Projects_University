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
		return  matriz[i][j];
	}
}
