#pragma once
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

using namespace std;

enum PacketType{
	TPing = 0,
	TId
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

	void send(Client& client, sf::Packet packet);
};

