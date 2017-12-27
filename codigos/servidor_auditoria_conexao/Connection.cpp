#include "Connection.h"

#include <iostream>
#include <sstream>
#include "Game.h"

Connection::Connection (Game* game, ServerSocket* server_socket, int id){
	this->game = game;
	this->server_socket = server_socket;
	this->id = id;

	connection_thread = new thread(&Connection::update, this);
	createLog();
}

void Connection::newPlayerConnection(){
	json new_client;
	new_client["new_player"]["player_id"] = id;
	new_client["position"] = position.getJson();
	game->sendToClients(new_client);
}

void Connection::writeToLog(json msg){
	*(player_log) << msg << endl;
}

void Connection::createLog(){
	player_log = new ofstream(); 
	player_log->open("logs/log" + to_string(id));
}

int Connection::getId(){
	return this->id;
}

void Connection::update(){
	while (true){
		try {
			std::string received_msg;
			*(server_socket) >> received_msg;
			auto msg_json = json::parse(received_msg);
			cout << "recebeu " << msg_json << endl;
			writeToLog(msg_json);
			cout << "a" << endl;
			*(server_socket) << "aaa";
		}
  		catch (SocketException& e) {
  			cout << e.description() << endl;
  			cout << "Erro na conexão com cliente" << endl;
  		}
		
	}
}


void Connection::closeConnection(){
	player_log->close();
}

bool Connection::msgIsValid(json msg){
	return msg["player_id"] == id && msg["new_player"].is_null();
}

void Connection::sendToClient(json msg){
	cout << "enviou pro cliente" << msg << endl;
	*(server_socket) << msg.dump();
	cout << "dps de enviar" << endl;
}

void Connection::updatePlayer(json msg){
	position.setPosition(msg["position"]);
}


