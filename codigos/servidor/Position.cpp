#include "Position.h"
#include <iostream>


using namespace std;

Position::Position (int x, int y){
	this->x = x;
	this->y = y;
	this->side = 0;
}

Position::Position(){
	this->x = 0;
	this->y = 0;
	this->side = 0;
}

void Position::setPosition(json pos){
	this->x = pos["x"];
	this->y = pos["y"];
	this->side = pos["side"];
}

json Position::getJson(){
	json position;
	position["x"] = x;
	position["y"] = y;
	position["side"] = side;
	return position;
}

int Position::getX(){
	return x;
}

int Position::getY(){
	return y;
}

bool Position::isEqual(Position pos){

	cout << "x:" << x << " y:" << y << endl;

	return (x == pos.getX() && y == pos.getY());
}

void Position::move(int amount){
	if (side == 0)
		y += amount;
	else if (side == 1)
		y -= amount;
	else if (side == 2)
		x -= amount;
	else if (side == 3)
		x += amount;
}

void Position::move(int amount, int direction){
	side = direction;
	move(amount);
}

string Position::getPosition(){
	string pos = "GET POSITION x:" + to_string(x) + " y" + to_string(y);
	cout << pos << endl;
	return pos;
}