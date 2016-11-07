#pragma once
#include <vector>
#include "SyncObject.h"
#include "PacketType.h"
#include "Server.h"


class SyncManager
{
public:
	SyncManager(Server* server);
	~SyncManager();
	int addObject(SyncObject<void*>& obj);
	int removeObject(SyncObject<void*>& obj);

private:
	std::vector<SyncObject<void*>*> _syncObjects;
	Server* _serverPtr;
};

