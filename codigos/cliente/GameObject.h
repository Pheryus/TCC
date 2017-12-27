#ifndef GameObject_class
#define GameObject_class

#include "Position.h"
#include <string>

using namespace std;


class GameObject {
	public:
		GameObject(Position position);
		GameObject();
		Position getPosition();
		void setPosition(Position);

	protected:
		void move();
		void move(int);
		Position position;
		int movespeed = 0;
};

#endif