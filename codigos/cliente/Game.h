	#ifndef Game_class
#define Game_class

#include "Player.h"
#include "Bullet.h"	
#include "Position.h"
#include "ClientSocket.h"
#include "Enemy.h"
#include "SocketException.h"
#include <string>
#include <list>

using namespace std;

class Game {
	public:
		Game(ClientSocket* client);
		void update();

	private:
		void move (string);
		void playerEnter(Position, int);
		void playerExit(int);
		bool collision(Bullet*);
		void toServer();
		void getResponse();
		void createBullet(Position, int);
		void setId();
		void opponentAction(json);

		void updateBullets();
		
		bool isColliding(Position, Position);

		list<Enemy*> enemies;
		Player* player;
		ClientSocket* client_socket;

		list<Bullet*> bullets;

		int side;
		int shield_cooldown = 0;
		int shot_cooldown = 0;
		bool game_start = false;
		bool is_dead = false;

		const int max_shot_cooldown = 5;
		const int max_shield_cooldown = 15;
		const int shield_time = 5;
		const int player_movespeed = 3;

};

#endif