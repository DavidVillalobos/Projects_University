#include "tablero.h"

tablero::tablero(){
	tab = new string*[3];
	int i;
	for (i = 0; i < 3;i++) {
		tab[i] = new string[3];
	}
	for (i = 0; i < 3;i++) {
		for (int a = 0; a < 3;a++) {
			tab[i][a] = " ";
		}
	}
}

tablero::~tablero(){
	for (int i = 0; i < 3;i++) {
		delete[] tab[i];
	}
	delete[] tab;
}

string tablero::getPos(int pos) {
	switch (pos) {
	case 0: {return tab[0][0]; }
	case 1: {return tab[0][1]; }
	case 2: {return tab[0][2]; }
	case 3: {return tab[1][0]; }
	case 4: {return tab[1][1]; }
	case 5: {return tab[1][2]; }
	case 6: {return tab[2][0]; }
	case 7: {return tab[2][1]; }
	case 8: {return tab[2][2]; }
	}
}

void tablero::setPos(int pos, string marca) {
	switch (pos) {
	case 0: { tab[0][0] = marca; break; }
	case 1: { tab[0][1] = marca; break; }
	case 2: { tab[0][2] = marca; break; }
	case 3: { tab[1][0] = marca; break; }
	case 4: { tab[1][1] = marca; break; }
	case 5: { tab[1][2] = marca; break; }
	case 6: { tab[2][0] = marca; break; }
	case 7: { tab[2][1] = marca; break; }
	case 8: { tab[2][2] = marca; break; }
	}
}
void tablero::toString(int x, int y) {
	imprimeGATO(x+1, y); setColor(15);
	y += 7;
	setCursor(x, y); imprimeString("\311\315\315\315\315\315\315\315\315\315\313\315\315\315\315\315\315\315\315\315\313\315\315\315\315\315\315\315\315\315\273"); y++;
	setCursor(x, y); imprimeString("\272  \311\315\315\315\273  \272  \311\315\315\315\273  \272  \311\315\315\315\273  \272"); y++;
	setCursor(x, y); imprimeString("\272  \272 " + tab[0][0] + " \272  \272  \272 "+tab[0][1]+" \272  \272  \272 " + tab[0][2] + " \272  \272"); y++;
	setCursor(x, y); imprimeString("\272  \310\315\315\315\274  \272  \310\315\315\315\274  \272  \310\315\315\315\274  \272"); y++;
	setCursor(x, y); imprimeString("\314\315\315\315\315\315\315\315\315\315\316\315\315\315\315\315\315\315\315\315\316\315\315\315\315\315\315\315\315\315\271"); y++;
	setCursor(x, y); imprimeString("\272  \311\315\315\315\273  \272  \311\315\315\315\273  \272  \311\315\315\315\273  \272"); y++;
	setCursor(x, y); imprimeString("\272  \272 " + tab[1][0] + " \272  \272  \272 " + tab[1][1] + " \272  \272  \272 " + tab[1][2] + " \272  \272"); y++;
	setCursor(x, y); imprimeString("\272  \310\315\315\315\274  \272  \310\315\315\315\274  \272  \310\315\315\315\274  \272"); y++;
	setCursor(x, y); imprimeString("\314\315\315\315\315\315\315\315\315\315\316\315\315\315\315\315\315\315\315\315\316\315\315\315\315\315\315\315\315\315\271"); y++;
	setCursor(x, y); imprimeString("\272  \311\315\315\315\273  \272  \311\315\315\315\273  \272  \311\315\315\315\273  \272"); y++;
	setCursor(x, y); imprimeString("\272  \272 " + tab[2][0] + " \272  \272  \272 " + tab[2][1] + " \272  \272  \272 " + tab[2][2] + " \272  \272"); y++;
	setCursor(x, y); imprimeString("\272  \310\315\315\315\274  \272  \310\315\315\315\274  \272  \310\315\315\315\274  \272"); y++;
	setCursor(x, y); imprimeString("\310\315\315\315\315\315\315\315\315\315\312\315\315\315\315\315\315\315\315\315\312\315\315\315\315\315\315\315\315\315\274"); y++;
}