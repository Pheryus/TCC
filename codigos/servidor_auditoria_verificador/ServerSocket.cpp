#include "ServerSocket.h"
#include "SocketException.h"


ServerSocket::ServerSocket (int port){
    if (!Socket::create()){
        throw SocketException("Nao conseguiu criar o serverSocket.");
    }

    if (!Socket::bind(port)){
        throw SocketException ( "Nao conseguiu conectar com a porta" );
    }

    if (!Socket::listen()){
        throw SocketException ("Nao consegue ouvir o socket");
    }

}

ServerSocket::~ServerSocket(){
}


const ServerSocket& ServerSocket::operator << ( const std::string& s ) const {
    if (! Socket::send(s)){
        throw SocketException("Não consegue escrever no socket.");
    }

    return *this;

}


const ServerSocket& ServerSocket::operator >> ( std::string& s ) const{
    if (!Socket::recv(s)){
        throw SocketException("Não consegue ler do socket.");
    }

    return *this;
}

void ServerSocket::accept(ServerSocket& sock){
    if (!Socket::accept (sock)){
        throw SocketException("Não conseguiu aceitar o socket.");
    }
}
