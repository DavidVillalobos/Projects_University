#include "Board.h"

Board::Board() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matriz[i][j] = ' ';
		}
	}
	spaceAvailable = 9;
}

bool Board::setSimb(int i, int j, char simb){
	if (0 < spaceAvailable) {
		if (-1 < i && i < 3 && -1 < j && j < 3) {
			if (matriz[i][j] == ' ') {
				matriz[i][j] = simb;
				spaceAvailable--;
				return true;
			}
		}
	}
	return false;
}

char Board::getSimb(int i, int j){
	if (-1 < i && i < 3 && -1 < j && j < 3) {
		return matriz[i][j];
	}
	return ' ';
}

bool Board::haveWinner(){
	// Revisando Filas
	for (int i = 0; i < 3; i++) {
		if (matriz[i][0] != ' ' && matriz[i][0] == matriz[i][1] && matriz[i][1] == matriz[i][2]) {
			return true;
		}
	}
	// Revisando Columnas
	for (int i = 0; i < 3; i++) {
		if (matriz[0][i] != ' ' && matriz[0][i] == matriz[1][i] && matriz[1][i] == matriz[2][i]) {
			return true;
		}
	}

	if (matriz[0][0] != ' ' && matriz[0][0] == matriz[1][1] && matriz[1][1] == matriz[2][2]) {
		return true;
	}
	if (matriz[0][2] != ' ' && matriz[0][2] == matriz[1][1] && matriz[1][1] == matriz[2][0]) {
		return true;
	}
	return false;
}

bool Board::haveTie(){
	return !haveWinner() && spaceAvailable == 0;
}


string Board::toString() {
	stringstream s;
	for (int i = 0; i < 3; i++) {
		s.width(5);
		s << i+1;
	}
	s << '\n';
	for (int i = 0; i < 3; i++){
		s << i+1 << " |";
		for (int j = 0; j < 3; j++){
			s.width(5);
			s << matriz[i][j] << " |";
		}
		s << '\n';
	}
	return s.str();
}

void Board::clean(){
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matriz[i][j] = ' ';
		}
	}
	spaceAvailable = 9;
}
