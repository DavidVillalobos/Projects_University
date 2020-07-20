#ifndef BOARD_H
#define BOARD_H
class Board {
	char matriz[3][3];
	int spaceAvailable;
public:
	Board();
	bool putSimb(int, int, char);
};
#endif // !BOARD_H