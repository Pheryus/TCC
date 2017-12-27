#ifndef Game_class
#define Game_class

#include "ServerSocket.h"
#include "SocketException.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <list>
#include "Position.h"

using namespace std;
using json = nlohmann::json;

class Game {
	public:
		Game(int);
		void update();
		void sendToClients(json);


	private:
		void readStates(int);
		void step4();
		void step5();
		void step7();
		void barrier();
		void shoot();
		bool barrier_on = false, can_barrier = true;
		bool can_shot = true, shot = false;

		int shield_cooldown = 0;
		int shot_cooldown = 0;

		const int max_shot_cooldown = 5;
		const int max_shield_cooldown = 15;
		const int shield_time = 5;
		const int player_movespeed = 3;

		list<json> abstract_delta;
		list<json> concrete_delta;

		list<json> concrete_states;

		list<json> next_states;

		Position position;
};

#endif