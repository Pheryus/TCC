#include "Player.h"

#include "json.hpp"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;
using json = nlohmann::json;


Player::Player() : GameObject(){
  srand(time(0));
  movespeed = 8;
}

int Player::getId(){
  return id;
}

void Player::setShot(bool shot){
  this->shot = shot;
}

bool Player::isShooting(){
    return this->shot;
}

bool Player::randomMovement(json msg){
    checkCooldown();

    Position pos;
    pos.setPosition(msg["position"]);

    bool act = false, error = false;

    if (pos.isEqual(position) == false){
        for (int i = 0; i < 3; i++){
            Position aux = position;
            aux.move(i);
            if (aux.isEqual(pos)){
                act = true;
                break;
            }
        }
        if (act == false){
            error = true;
            return error;
        }
    }

    if (msg["barrier_on"] == true && can_barrier == true){
        if (act == true){
            error = true;
           return error;
        }
        else{
            act = true;
            barrier();
        }
    }

    if (msg["shoot"] == true && can_shot == true){
        if (act == true){
            error = true;
            return error;
        }
        else{
            act = true;
            shoot();
        }
    }
    return false;
}

bool Player::barrierIsOn(){
  return barrier_on;
}

void Player::setPlayerInfo(json msg){
  
}

void Player::barrier(){
  if (can_barrier == true){
    barrier_on = true;
    can_barrier = false;
  }
}

void Player::setId(int id){
  this->id = id;
}

  void Player::shoot(){
  if (can_shot == true){
    shot = true;
    can_shot = false;
  }
  else {
    shot_cooldown++;
    if (shot_cooldown >= max_shot_cooldown)
      can_shot = true;
  }
}


void Player::checkCooldown(){
  if (can_barrier == false){
    shield_cooldown++;

    if (barrier_on && shield_cooldown >= shield_cooldown)
        barrier_on = false;
  
    if (shield_cooldown >= max_shield_cooldown)
      can_barrier = true;
  }
}


string Player::getPlayerInfo(){
  json player_info;

  player_info["player_id"] = id;
  player_info["position"] = position.getJson();
  player_info["shoot"] = shot;
  player_info["barrier_on"] = barrier_on;
  return player_info.dump();
}