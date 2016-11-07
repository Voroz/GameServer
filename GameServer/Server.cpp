#include "Server.h"


int Client::nextId = 0;

Server::Server(){

}

Server::~Server(){

}

void Server::send(Client& client, sf::Packet packet) {
	if (client.socket->send(packet) == sf::Socket::Disconnected) {
		cout << "client " << client.socket->getRemoteAddress() << " disconnected" << endl;
		client.socket->disconnect();
		delete client.socket;
		for (int i = 0; i < _clients.size(); i++) {
			if (&client == &_clients[i]) {
				_clients.erase(_clients.begin() + i);
			}
		}
	}
}

void Server::run() {
	sf::TcpListener listener;
	listener.setBlocking(false);

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

		if (listener.accept(*client) != sf::Socket::Done)
		{
			delete client;
		}
		else {
			cout << "client " << client->getRemoteAddress() << " accepted" << endl;
			_clients.push_back(client);
			sf::Packet packet;
			packet << PacketType::TId << _clients.back().id;
			send(_clients.back(), packet);
		}

		// Ping clients
		for (int i = 0; i < _clients.size(); i++) {
			sf::Packet packet;
			packet << PacketType::TPing;
			send(_clients[i], packet);
		}
	}

	// Disconnect clients upon closing server
	for (int i = 0; i < _clients.size(); i++) {
		_clients[i].socket->disconnect();
		delete _clients[i].socket;
		_clients.erase(_clients.begin() + i);
	}

	// use "client" to communicate with the connected client,
	// and continue to accept new connections with the listener
}
