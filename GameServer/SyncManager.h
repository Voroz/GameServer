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
	SyncObject<void*>& inControlObjects(Client* client); // TODO: Send these objects to their clients if values were changed
	SyncObject<void*>& toBeSyncedObjects(Client* client); // TODO: in client.receive(), sync the objects where client ids and obj ids match

private:
	std::vector<SyncObject<void*>*> _syncObjects;
	Server* _serverPtr;
};

