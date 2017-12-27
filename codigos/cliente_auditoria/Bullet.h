#ifndef Bullet_class
#define Bullet_class

#include "Position.h"
#include "GameObject.h"

using namespace std;
#include <string>

class Bullet : public GameObject {
	public:
		Bullet(Position position, int);
		void update();
		bool isDead();
		int getOwner();
	private:
		int owner_id;
		int iterations = 0;
		bool dead = false;
		const int max_iterations = 5;
};

#endif