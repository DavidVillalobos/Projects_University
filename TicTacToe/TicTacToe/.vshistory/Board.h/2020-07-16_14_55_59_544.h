#ifndef BOARD_H
#define BOARD_H
#include<sstream>
using namespace std;
class Board {
	char matriz[3][3];
	int spaceAvailable;
public:
	Board();
	bool setSimb(int, int, char);
	char getSimb(int, int);
	bool haveWinner();
	bool haveTie();
	string toString();
};
#endif // !BOARD_H