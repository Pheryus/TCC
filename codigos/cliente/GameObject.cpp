#include "GameObject.h"
#include <string>
#include <iostream>
using namespace std;


GameObject::GameObject(Position position){
	this->position = position;
}

GameObject::GameObject(){
	
}

void GameObject::setPosition(Position pos){
	this->position = pos;
}

Position GameObject::getPosition(){
	return this->position;
}

void GameObject::move(){
	position.move(movespeed);
}

void GameObject::move(int direction){
	position.move(movespeed, direction);
}