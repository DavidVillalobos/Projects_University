#include "Player.h"

Player::Player(){
	this->name = "";
}

Player::Player(string name){
	this->name = name;
}

string Player::getName(){
	return name;
}
