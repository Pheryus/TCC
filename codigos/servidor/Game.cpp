#include "Game.h"
#include <string>
#include <iostream>

Game::Game() {
	server = new ServerSocket(30000);

	try {
		while (true){
			ServerSocket* new_sock = new ServerSocket();
			server->accept (*new_sock);

	  		try {
	  			Connection* con = new Connection(this, new_sock, client_id);
				client_connections.push_back(con);
				cout << "Cliente " << client_id  << " conectado!" << endl;
				con->newPlayerConnection();
				client_id++;

	    	}
	  		catch (SocketException&) {
	  			cout << "Erro na conexão com cliente" << endl;
	  		}
		}
    }
	catch (SocketException& e){
		std::cout << "Erro no servidor: " << e.description() << "\nDesligando...\n";
  	}
}


void Game::sendToClients(json message){
	cout << "chegou aqui" << endl;
	for (auto it = client_connections.begin(); it != client_connections.end(); it++){
		if (message.find("new_player") == message.end() && message["player_id"] != (*it)->getId()){
			(*it)->writeToLog(message);
		}
		(*it)->sendToClient(message);
	}
}
