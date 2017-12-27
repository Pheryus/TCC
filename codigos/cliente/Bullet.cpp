#include "Bullet.h"
#include <string>
#include <iostream>
using namespace std;


Bullet::Bullet(Position position, int id) : GameObject(position){
	this->movespeed = 200;
	move();
	this->owner_id = id;
}

bool Bullet::isDead(){
	return dead;
}

int Bullet::getOwner(){
	return owner_id;
}

void Bullet::update(){
	if (dead == false){
		move();
		iterations++;
		if (iterations > max_iterations){
			dead = true;
		}
	}
}

