#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>

#include "Game.h"


int main ( int argc, int argv[] ){   
    try {
        ClientSocket* client_socket = new ClientSocket("localhost", 30000);

        Game* game = new Game(client_socket);
        while (true){
            game->update();
        }
    }
    catch ( SocketException& e ){
        std::cout << "Exception was caught:" << e.description() << "\n";
    }

    return 0;
}
