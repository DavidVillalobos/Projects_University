#ifndef VIEWCONSOLE
#define VIEWCONSOLE
#include <iostream>
#include <sstream>
#include<Windows.h>
using namespace std;
void printString(string);
int getInt();
string getString();
void setColor(int);
void setCursorPosition(int, int);
void setConsoleSize(int, int);
int wherey();
int wherex();
int stringToInt(string);
#endif // !VIEWCONSOLE

