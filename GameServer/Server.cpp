#include "Server.h"


int Client::nextId = 0;

Server::Server(){

}

Server::~Server(){

}

void Server::run() {
	sf::TcpListener listener;

	// bind the listener to a port
	int port = 53000;
	if (listener.listen(port) != sf::Socket::Done)
	{
		cout << "error listening to port " << port << endl;
	}
	else {
		cout << "listening to port " << port << endl;
	}

	// accept a new connection
	while (1) {
		sf::TcpSocket* client = new sf::TcpSocket;
		client->setBlocking(false);
		listener.setBlocking(false);
		if (listener.accept(*client) != sf::Socket::Done)
		{
			delete client;
		}
		else {
			cout << "client " << client->getRemoteAddress() << " accepted" << endl;
			_clients.push_back(client);
		}

		// Ping clients, and check for disconnections
		for (int i = 0; i < _clients.size(); i++) {
			sf::Packet packet;
			packet << '0';
			if (_clients[i].socket->send(packet) == sf::Socket::Disconnected) {
				cout << "client " << _clients[i].socket->getRemoteAddress() << " disconnected" << endl;
				_clients[i].socket->disconnect();
				delete _clients[i].socket;
				_clients.erase(_clients.begin() + i);
			}
		}
	}

	// Disconnect clients upon closing server
	for (int i = 0; i < _clients.size(); i++) {
		sf::Packet packet;
		packet << '0';
		_clients[i].socket->disconnect();
		delete _clients[i].socket;
		_clients.erase(_clients.begin() + i);
	}

	// use "client" to communicate with the connected client,
	// and continue to accept new connections with the listener
}
