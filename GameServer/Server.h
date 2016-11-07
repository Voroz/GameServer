#pragma once
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

using namespace std;

struct Data {

};

struct Client {
	Client(sf::TcpSocket* socket) : 
		socket(socket),
		id(nextId++){

	};
	sf::TcpSocket* socket;
	int id;

private:
	static int nextId;
};

class Server
{
public:
	Server();
	~Server();

	void run();

private:
	vector<Client> _clients;
};

