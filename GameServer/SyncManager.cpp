#include "SyncManager.h"



SyncManager::SyncManager(Server* server) : 
	_serverPtr(server){

}

SyncManager::~SyncManager(){

}

int SyncManager::addObject(SyncObject<void*>& obj) {
	_syncObjects[obj.id()] = &obj;
}
int SyncManager::removeObject(int id) {
	sf::Packet packet;
	SyncObject<void*>* obj = _syncObjects[id];
	// Send packet that we no longer sync a certain object to clients which has this object.
	if (obj->inControl()) {
		packet << PacketType::TRemoveSyncedObj << obj->id();
		for (auto socket : obj->sockets()) {
			_serverPtr->send(*socket, packet);
		}
	}
	_syncObjects.erase(id);
}
void SyncManager::syncObjects(std::vector<SyncObject<void*>*> objectsToSync) {
	for (auto &obj : objectsToSync) {
		_syncObjects[obj->id()]->setData(obj->data());
	}
}

// TODO: Make this function send all objects with one packet per client.
void SyncManager::sendObjects() {
	std::vector<sf::Packet> packetVector;
	for (int i = 0; i < _syncObjects.size(); i++) {
		SyncObject<void*>* obj = _syncObjects.at(i);
		if (obj->inControl() == false) {
			continue;
		}
		sf::Packet packet;
		packet << PacketType::TSyncObjects << obj->id() << obj->data();
		for (auto* socket : obj->sockets()) {
			_serverPtr->send(*socket, packet);
		}
	}
}