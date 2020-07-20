#include "Player.h"

Player::Player(){
	this->name = "";
}

Player::Player(string name){
	this->name = name;
}

//Tipo Scope metodo(Parametros)
string Player::getName(){
	return name;
}

void Player::setName(string name) {
	this->name = name;
}
