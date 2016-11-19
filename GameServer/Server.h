#pragma once
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "Client.h"
#include "PacketType.h"
#include "SyncManager.h"

using namespace std;

struct PendingPacket {
	sf::TcpSocket* socket;
	sf::Packet packet;
};

class Server
{
public:
	Server();
	~Server();

	void run();
	void send(sf::TcpSocket& socket, sf::Packet packet);
	sf::Socket::Status receive(sf::TcpSocket* socket);
	void linkSyncManager(SyncManager& syncManager);

private:
	vector<Client> _clients;
	std::vector<PendingPacket> _pendingPackets;

	void sendPendingPackets();
	SyncManager* _pSyncManager;
};

