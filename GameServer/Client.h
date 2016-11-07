#pragma once
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class Client {
public:
	Client(sf::TcpSocket* socket);
	sf::TcpSocket* socket;
	int id();

private:
	int _id;
	static int nextId;
};