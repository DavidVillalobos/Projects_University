#ifndef PLAYER_H
#define PLAYER_H
#include<string>
using std::string;
class Player{
	string name;
public:
	Player();
	Player(string);
	string getName();
	setName(string);
};
#endif // !PLAYER_H