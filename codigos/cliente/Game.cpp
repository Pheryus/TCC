#include "Game.h"
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

Game::Game(ClientSocket* client_socket) {
	this->client_socket = client_socket;
	player = new Player();


}

void Game::update(){
	if (game_start == true){
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	    player->randomMovement();
	    try {
	    	toServer();
	        getResponse();
	    }
	    catch ( SocketException& ) {}

	    updateBullets();

    }
    else{
    	setId();
    }
}

void Game::updateBullets(){

	if (player->isShooting()){
		createBullet(player->getPosition(), player->getId());
	}

	list<list<Bullet*>::iterator> bullets_to_remove;

	for (auto it = bullets.begin(); it != bullets.end(); it++){

		Bullet* bullet = (*it);
		bullet->update();
		if (bullet->isDead() || collision(bullet) == true){
			bullets_to_remove.push_back(it);
		}
	}

	for (auto &it : bullets_to_remove){
		bullets.erase(it);
	    delete (*it);
    }
}

void Game::setId(){
	string id;
	try {
		*(client_socket) >> id;
		json response = json::parse(id);
		if (response.is_null() == false){
			int new_id = response["new_player"]["player_id"];
			cout << "id " << new_id << endl;
			player->setId(new_id);
			player->getPosition().setPosition(response["position"]);
			game_start = true;
		}		
	}
	catch ( SocketException& ) {}
  
}

void Game::playerEnter(Position position, int id){
	enemies.push_back(new Enemy(id, position));
}

void Game::playerExit(int id){
	auto enemy_it = enemies.end();

	for (auto it = enemies.begin(); it != enemies.end(); it ++){
		if ((*it)->getId() == id){
			enemy_it = it;
		}
	}

	if (enemy_it != enemies.end())
		enemies.erase(enemy_it);
}

bool Game::collision(Bullet* bullet){


	list<GameObject*> targets(enemies.begin(), enemies.end());
	targets.push_back(player);

	for (auto it = targets.begin(); it != targets.end(); it++){

		(*it)->getPosition().getPosition();

		if (isColliding(bullet->getPosition(), (*it)->getPosition()) == true){
			cout << "alvo atingido por tiro de " << bullet->getOwner() << endl; 
			return true;
		}
	}

	return false;

}

bool Game::isColliding(Position pos1, Position pos2){
	return (pos1.isEqual(pos2));
}

void Game::toServer(){
  string info = player->getPlayerInfo();

  *(client_socket) << info;
  //cout << "enviou" << info << endl;
}


void Game::opponentAction(json msg){

	if (msg["new_player"].is_null()){
		Position player_pos;
		player_pos.setPosition(msg["new_player"]["position"]);
		playerEnter(player_pos, msg["new_player"]["player_id"]);
	}
	else {
		for (auto it = enemies.begin(); it != enemies.end(); it++){

			Enemy* enemy = (*it);

			if (enemy->getId() == msg["player_id"]){
				enemy->getPosition().setPosition(msg["position"]);
				enemy->setBarrier(msg["barrier_on"]);
				if (msg["shoot"] == true){
					createBullet(enemy->getPosition(), enemy->getId());
				}
				break;
			}
		}	
	}
}


void Game::createBullet(Position pos, int id){
	bullets.push_back(new Bullet(pos, id));
}

void Game::getResponse(){
	string a;
	try {
		*(client_socket) >> a;
		json response = json::parse(a);
		if (response["player_id"] != player->getId()){
			opponentAction(response);
		}

	}
    catch ( SocketException& ) {
    	cout << "Erro na mensagem" << endl;
    }
	//cout << "recebeu: " << a << endl;
	

}