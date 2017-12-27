#include "Enemy.h"
#include "Position.h"
#include <iostream>

Enemy::Enemy(int id, Position position) : GameObject(position) {
	this->id = id;
}

void Enemy::setBarrier(bool b){
	barrier_on = b;
}

bool Enemy::getBarrier(){
	return barrier_on;
}

int Enemy::getId(){
	return id;
}