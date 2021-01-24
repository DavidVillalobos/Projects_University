#include "Player.h"

//Scope metodo(Parametros)
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

//Scope metodo()
Player::~Player(){

}
