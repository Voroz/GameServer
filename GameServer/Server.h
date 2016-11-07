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

struct PendingPacket {
	Client* client;
	sf::Packet packet;
};

class Server
{
public:
	Server();
	~Server();

	void run();

private:
	vector<Client> _clients;
	std::vector<PendingPacket> _pendingPackets;

	void send(Client& client, sf::Packet packet);
	void sendPendingPackets();
};

