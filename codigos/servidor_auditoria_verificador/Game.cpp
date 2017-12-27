#include "Game.h"
#include <string>
#include <iostream>
#include <fstream>


Game::Game(int cicle) {
	cout << cicle << endl;
 	std::clock_t start;
    double duration;

	readStates(cicle);
    start = std::clock();
	step4();
	step5();
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
}



void Game::readStates(int cicle){
	ifstream file("logs/log0");
	string line;
	if (file.is_open() == false)
		return;
	int i;

    while (getline(file, line) && i < cicle){	
    	json msg_json = json::parse(line);
    	abstract_delta.push_back(msg_json);

    	getline(file, line);

    	json msg_json2 = json::parse(line);
    	concrete_delta.push_back(msg_json2);	
		
		getline(file, line);
		json msg_json3 = json::parse(line);
		concrete_states.push_back(msg_json3);	
		i++;
    }
    cout << i << endl;
    file.close();
}


void Game::step4(){
	
	auto a = concrete_states.begin();

	next_states.push_back((*a));

	auto delta = concrete_delta.begin();
	string actions[] = {"position", "barrier", "can_barrier", "shield_cooldown", 
	"shoot", "can_shot", "shot_cooldown"};

	for (delta; delta != concrete_delta.end(); delta++){
		json new_state;

		json delta_json = (*delta);

		for (string s : actions){
			if (delta_json.count(s) != 0){
				new_state[s] = delta_json[s];
			}
		}

		next_states.push_back(new_state);
	}
}

void Game::step7(){
	string actions[] = {"position", "barrier", "can_barrier", "shield_cooldown", "shoot", "can_shot", "shot_cooldown"};

	json j1 = concrete_states.back();
	json j2 =  next_states.back();

	bool error = false;

	for (string a: actions){
		if (j2.find(a) != j2.end() && j1[a] != j2[a]){
			error = true;
			break;
		}
	}
	if (error == false){
		cout << "válido" << endl;
	}
	else
		cout << "inválido" << endl;

}

void Game::step5(){

	auto it_con = concrete_delta.begin();
	string actions[] = {"position", "barrier", "can_barrier", "shield_cooldown", "shoot", "can_shot", "shot_cooldown"};

	bool error = false;
	int i=0;
	for (auto it = abstract_delta.begin(); it != abstract_delta.end(); it++){

		json j = (*it_con);
		update();

		for (string a : actions){

			if ((*it).find(a) != (*it).end() && (*it)[a] != j[a]){
				error = true;
				return;
			}
			if (j.find(a) != j.end()){

				if (a == "position"){
					Position pos;
	    			pos.setPosition(j["position"]);
	    			bool find = false;
			        for (int i = 0; i < 4; i++){
			            Position aux = position;
			            aux.move(8, i);
			            if (aux.isEqual(pos)){
			            	position = aux;
			            	find = true;
			            }
			        }

			        if (find == false){
			        	error = true;

			        }

				}
				else if (a == "barrier"){
					if (j[a] == true){
						if (can_barrier)
							barrier();
						else
							error = true;
					}

					if (j[a] == false && can_barrier)
						error = true;
				}
				else if (a == "shield_cooldown"){
					if (j[a] != shield_cooldown)
						error = true;
				}
				else if (a == "shot_cooldown"){
					if (j[a] != shot_cooldown){
						error = true;
					}
				}
				else if (a == "shoot"){
					if (j[a] == true){
						if(can_shot)
							shoot();
						else
							error = true;
					}

					if (j[a] == false && can_shot)
						error = true;
					
				}
			}
		if (error){
			cout << "ERRO " << i << endl;
			return;
		}

		}

		it_con++;
		i++;
	}
	step7();
}

void Game::barrier(){
    barrier_on = true;
    can_barrier = false;
}

void Game::shoot(){
    if (can_shot == true){
        shot = true;
        can_shot = false;
    }
}


void Game::update(){
  	if (can_barrier == false){
	    shield_cooldown++;

	    if (barrier_on && shield_cooldown >= shield_cooldown)
	        barrier_on = false;
	  
	    if (shield_cooldown >= max_shield_cooldown){
	    	shield_cooldown = 0;
	    	can_barrier = true;
	    }
	}
    if (can_shot == false){
        shot_cooldown++;
        if (shot_cooldown >= max_shot_cooldown){
        	shot_cooldown = 0;
            can_shot = true;
        }
    }

}
