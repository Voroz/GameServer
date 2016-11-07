#include "Server.h"


int Client::nextId = 0;

Server::Server(){

}

Server::~Server(){

}

sf::Socket::Status Server::send(Client& client, sf::Packet packet) {
	sf::Socket::Status status = client.socket->send(packet);
	if (status == sf::Socket::Disconnected) {
		cout << "client " << client.socket->getRemoteAddress() << ", Id " << client.id() << " disconnected" << endl;
		client.socket->disconnect();
		delete client.socket;
		for (int i = 0; i < _clients.size(); i++) {
			if (&client == &_clients[i]) {
				_clients.erase(_clients.begin() + i);
			}
		}
	}
	return status;
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
	sf::Clock clock;
	while (1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		sf::TcpSocket* client = new sf::TcpSocket;
		sf::Socket::Status status = listener.accept(*client);

		if (status != sf::Socket::Done)
		{
			delete client;
		}
		else if (status == sf::Socket::Done){
			// Create client
			cout << "client " << client->getRemoteAddress() << " accepted" << endl;
			_clients.push_back(client);
			// Send client his id
			sf::Packet packet;
			packet << PacketType::TId << _clients.back().id();
			send(_clients.back(), packet);
		}

		// Ping clients every second
		sf::Time time = clock.getElapsedTime();
		if (time.asSeconds() >= 1) {
			for (int i = 0; i < _clients.size(); i++) {
				sf::Packet packet;
				packet << PacketType::TPing;
				send(_clients[i], packet);
			}
			clock.restart();
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
