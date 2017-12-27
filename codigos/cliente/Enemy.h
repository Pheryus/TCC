#ifndef Enemy_class
#define Enemy_class

#include "GameObject.h"
#include <string>
#include "Position.h"


using namespace std;

class Enemy : public GameObject{
	public:
		Enemy(int, Position);
		int getId();
		void setBarrier(bool);
		bool getBarrier();

	private:
		int id;
		bool barrier_on = false;
};

#endif