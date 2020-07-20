#ifndef BOARD_H
#define BOARD_H
class Board {
	char matriz[3][3];
	int spaceAvailable;
public:
	Board();
	bool setSimb(int, int, char);
	char getSimb(int, int);
};
#endif // !BOARD_H