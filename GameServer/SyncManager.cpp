#include "SyncManager.h"



SyncManager::SyncManager(Server* server) : 
	_serverPtr(server){

}

SyncManager::~SyncManager(){

}

int SyncManager::addObject(SyncObject<void*>& obj) {
	_syncObjects.push_back(&obj);
}
int SyncManager::removeObject(SyncObject<void*>& obj) {
	sf::Packet packet;
	// Send packet that we no longer sync a certain object to clients which has this object.
	if (obj.inControl()) {
		packet << PacketType::TRemoveSyncedObj << obj.id();
		for (auto socket : obj.sockets()) {
			_serverPtr->send(*socket, packet);
		}
	}
	for (int i = 0; i < _syncObjects.size(); i++) {
		if (_syncObjects[i] == &obj) {
			_syncObjects.erase(_syncObjects.begin() + i);
		}
	}
}
