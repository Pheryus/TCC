#include <iostream>
#include <string>
#include <stdlib.h>
#include <klee/klee.h>
#include "json.hpp"
#include <stdio.h>
#include <string.h>

using json = nlohmann::json;

int x = 0, y = 0;
int side = 0
;
int shield_cooldown = 0;
int shot_cooldown = 0;
bool game_start = false;
bool is_dead = false;
FILE* file;
const int max_shot_cooldown = 5;
const int max_shield_cooldown = 15;
const int shield_time = 5;
const int player_movespeed = 3;

int movespeed = 8;

bool barrier_on = false, can_barrier = true;
bool can_shot = true, shot = false;


void checkCooldown(){
  	if (can_barrier == false){
	    shield_cooldown++;

    if (barrier_on && shield_cooldown >= shield_cooldown)
        barrier_on = false;
	  
    if (shield_cooldown >= max_shield_cooldown)
      	can_barrier = true;
    }
}

void barrier(){
  	if (can_barrier == true){
		barrier_on = true;
	    can_barrier = false;
  	}
}

void shoot(){
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



bool randomMovement(int n, char* line){
	checkCooldown();
	if (n == 0){
		y += movespeed;
		side = n;
	}
	else if (n == 1){
		y -= movespeed;
		side = n;
	}
	else if (n == 2){
		x -= movespeed;
		side = n;
	}

	else if (n == 3){
		x += movespeed;
		side = n;	
	}
	
	
	else if (n == 4)
      	barrier();
	else if (n == 5)
  		shoot();
  	else
  		return false;

	int i = 0;

	char barrier[20], shot2[20];
	int x2 = 0, y2 = 0, side2 = 0;
	
	sscanf(line, "%s %s %d %d %d", barrier, shot2, &side2,&x2, &y2);

	bool bbarrier2, bshot2;

	if (strcmp(barrier, "True") == 0)
		bbarrier2 = true;
	else
		bbarrier2 = false;

	if (strcmp(shot2, "True") == 0)
		bshot2 = true;
	else
		bshot2 = false;

  	bool valid = (x2 == x && y2 == y && side2 == side);

	valid &= (barrier_on == bbarrier2);
	valid &= (shot == bshot2);
	//printf("x1 %d y1 %d side %d x2 %d y2 %d side2 %d\n", x, y, side, x2, y2, side2);
	//printf("b1 %d s1 %d b2 %d s2 %d\n", barrier_on, shot, bbarrier2, bshot2);
	return valid;
}




void game(){

	file = fopen("logs/log0", "r");
	char* line = NULL;
    size_t len = 0;
    ssize_t read;
	int i = 0;
	int action;
    
    while ((read = getline(&line, &len, file)) != -1){
      
    	action = klee_range(0, 5, "x");
        bool valid;
        if (randomMovement(action, line) == false)
        	return;
       
    }

	klee_assert(1);
	printf("válido\n");
}

int main ( int argc, char** argv ){   
	game();

    return 0;
}
