#include "control.h"
void imprimeMatriz() {
	setColor(15);
	string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	cout << "  ";
	for (int x = 0; x < 25; x++){
		cout<<
" "<<abc[x]<<" ";
	}
	cout << "\n";
	for (int i = 0; i < 25; i++){
		cout << i + 1;
		if (i<9) {
			cout << " ";
		}
		setColor(10);
		for (int j = 0; j < 25; j++){
			cout << "[ ]";
		}
		setColor(15);
		cout << "\n";
	}
}

void main() {
	system("cls");
	setCursor(0, 8);
	imprimeMatriz();
	Regalo(78, 8, 10, 12);
	Regalo(78, 23, 8, 14);
	Regalo(23, 0, 14, 9);
	system("pause");
	system("cls");
	setCursor(0, 8);
	imprimeMatriz();
	Regalo(78, 8, 10, 12);
	Regalo(78, 23, 8, 14);
	Regalo(23, 0, 14, 9);
	system("pause");
	//Control *app = new Control();
	//delete app;

}