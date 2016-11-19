#pragma once
#include <vector>
#include "SyncObject.h"
#include "PacketType.h"
#include "Server.h"
#include "Client.h"

class Server;

class SyncManager
{
public:
	SyncManager(Server* server);
	~SyncManager();
	void addObject(SyncObject<int>& obj);
	int removeObject(int id);
	void syncObject(int id, int newData, sf::TcpSocket* socket); // Use this function in server.receive()
	void sendObjects();

private:
	std::map<int, SyncObject<int>*> _syncObjects; // TODO: Change to any data type
	Server* _pServer;
};

