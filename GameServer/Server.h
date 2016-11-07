#pragma once
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

enum PacketType{
	TPing = 0,
	TId
};

struct Client {
	Client(sf::TcpSocket* socket) : 
		socket(socket),
		_id(nextId++){

	};
	sf::TcpSocket* socket;
	int id() {
		return _id;
	}

private:
	int _id;
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

	sf::Socket::Status send(Client& client, sf::Packet packet);
};

