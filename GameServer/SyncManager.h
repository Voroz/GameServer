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
	int removeObject(SyncObject<void*>& obj);
	std::vector<SyncObject<void*>&> inControlObjects(Client* client); // TODO: Send these objects to their clients if values were changed
	std::vector<SyncObject<void*>&> toBeSyncedObjects(); // TODO: in client.receive(), sync the objects where client ids and obj ids match
	void syncObjects(); // Use this function in server.receive()

private:
	std::vector<SyncObject<void*>*> _syncObjects;
	Server* _serverPtr;
};

