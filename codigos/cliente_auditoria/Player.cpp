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

void Player::randomMovement(){
    json action;
    checkCooldown();
    int x = rand() % 6;

    if (x < 4){
        move(x);
        action = getPosition().getJson();
        abstract_delta["position"] = action;
        concrete_delta["position"] = action;
    }     
    if (x == 4) {
        barrier();
    }

    if (x == 5) {
        shoot();
    }

}


void Player::barrier(){
    json action;

    if (can_barrier == true){
        barrier_on = true;
        can_barrier = false;
        action["barrier"] = true;
        abstract_delta = action;
        concrete_delta["barrier"] = true;
        concrete_delta["can_barrier"] = false;
    }
}

void Player::setId(int id){
  this->id = id;
}

void Player::shoot(){
    if (can_shot == true){
        shot = true;
        can_shot = false;
        abstract_delta["shoot"] = true;
        concrete_delta["shoot"] = true;
    }
}

string Player::getConcreteState(){
  json player_info;

  player_info["player_id"] = id;
  player_info["position"] = position.getJson();
  player_info["shoot"] = shot;
  player_info["barrier"] = barrier_on;
  player_info["can_shot"] = can_shot;
  player_info["can_barrier"] = can_barrier;
  player_info["shield_cooldown"] = shield_cooldown;
  player_info["shot_cooldown"] = shot_cooldown;
  player_info["max_shot_cooldown"] = max_shot_cooldown;
  player_info["max_shield_cooldown"] = max_shield_cooldown;

  return player_info.dump();
}

string Player::getAbstractDelta(){
    string delta = abstract_delta.dump();

    abstract_delta.clear();
    return delta;
}

string Player::getConcreteDelta(){
    string delta = concrete_delta.dump();
    concrete_delta.clear();
    return delta;
}

void Player::checkCooldown(){
    if (can_barrier == false){
        shield_cooldown++;
        concrete_delta["shield_cooldown"] = shield_cooldown;
        if (barrier_on && shield_cooldown >= shield_time){
            barrier_on = false;
            concrete_delta["barrier_on"] = false;
        }
        if (shield_cooldown >= max_shield_cooldown){
          can_barrier = true;
          shield_cooldown = 0;
          concrete_delta["shield_cooldown"] = shield_cooldown;
          concrete_delta["can_barrier"] = true;
        }
    }

    if (can_shot == false){
        shot_cooldown++;
        concrete_delta["shot_cooldown"] = shot_cooldown;

        if (shot_cooldown >= max_shot_cooldown){
            shot_cooldown = 0;
            can_shot = true;
            concrete_delta["shot_cooldown"] = shot_cooldown;
            concrete_delta["can_shot"] = can_shot;
        }
    }
}


string Player::getAbstractState(){
  json player_info;

  player_info["player_id"] = id;
  player_info["position"] = position.getJson();
  player_info["shoot"] = shot;
  player_info["barrier_on"] = barrier_on;
  return player_info.dump();
}