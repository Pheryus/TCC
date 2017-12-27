#ifndef Player_class
#define Player_class

#include "Position.h"
#include "GameObject.h"

#include <string>

using namespace std;
using json = nlohmann::json;

using namespace std;

class Player : public GameObject {
	public:
		Player();
		void randomMovement();
		string getPlayerInfo();
		void setId(int);
		int getId();
		void setShot(bool);
		bool isShooting();

		string getAbstractDelta();
		string getConcreteDelta();
		string getConcreteState();
		string getAbstractState();

	private:
		void toServer();
		void shoot();
		void barrier();
		void checkCooldown();
		void createBullet();

		json abstract_delta, concrete_delta;

		int id;
		bool is_dead = false;
		bool barrier_on = false, can_barrier = true;
		bool can_shot = true, shot = false;

		int shield_cooldown = 0;
		int shot_cooldown = 0;

		const int max_shot_cooldown = 5;
		const int max_shield_cooldown = 15;
		const int shield_time = 5;
		const int player_movespeed = 3;
};

#endif