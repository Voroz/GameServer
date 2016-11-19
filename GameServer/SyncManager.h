#pragma once
#include <vector>
#include "SyncObject.h"
#include "PacketType.h"
#include "Server.h"
#include "Client.h"


class SyncManager
{
public:
	SyncManager(Server* server);
	~SyncManager();
	int addObject(SyncObject<void*>& obj);
	int removeObject(int id);
	void syncObjects(std::vector<SyncObject<void*>*> objectsToSync); // Use this function in server.receive()
	void sendObjects();

private:
	std::map<int, SyncObject<void*>*> _syncObjects;
	Server* _serverPtr;
};

