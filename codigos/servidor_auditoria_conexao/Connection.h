#ifndef Connection_class
#define Connection_class
#include <iostream>
#include <thread>
#include "ServerSocket.h"
#include "json.hpp"
#include "Position.h"
#include <fstream>

using json = nlohmann::json;
using namespace std;

class Game;


class Connection {
	public:
		Connection(Game*, ServerSocket* server_socket, int a);
		void update();
		void sendToClient(json);
		int getId();
		void closeConnection();
		void newPlayerConnection();
		void writeToLog(json);
	private:
		void updatePlayer(json);
		void createLog();
		
		void LogTest();
		bool msgIsValid(json);

		ofstream* player_log;
		thread* connection_thread;
		ServerSocket* server_socket;
		Game* game;
		int id;
		Position position;
		
};


#endif