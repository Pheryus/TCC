#ifndef Game_class
#define Game_class

#include "ServerSocket.h"
#include "SocketException.h"
#include "Connection.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <list>


using namespace std;
using json = nlohmann::json;

class Game {
	public:
		Game();
		void update();
		void sendToClients(json);


	private:
		ServerSocket* server;
		int client_id = 0;
		list<Connection*> client_connections;

};

#endif