#include "SyncManager.h"



SyncManager::SyncManager(Server* server) : 
	_pServer(server){

}

SyncManager::~SyncManager(){

}

void SyncManager::addObject(SyncObject<int>& obj) {
	_syncObjects[obj.id()] = &obj;
}
int SyncManager::removeObject(int id) {
	sf::Packet packet;
	SyncObject<int>* obj = _syncObjects[id];
	// Send packet that we no longer sync a certain object to clients which has this object.
	if (obj->inControl()) {
		packet << PacketType::TRemoveSyncedObj << obj->id();
		for (auto socket : obj->sockets()) {
			_pServer->send(*socket, packet);
		}
	}
	_syncObjects.erase(id);
	return 1;
}
// TODO: Change to any data type
void SyncManager::syncObject(int id, int newData, sf::TcpSocket* socket) {
	if (_syncObjects[id] == nullptr || _syncObjects[id]->inControl() == true || _syncObjects[id]->sockets()[0] != socket) { // TODO: sockets()[0] is a temporary solution
		cout << "false sync data provided" << endl;
		return;
	}
	_syncObjects[id]->setData(newData);
}

// TODO: Make this function send all objects with one packet per client.
void SyncManager::sendObjects() {
	std::vector<sf::Packet> packetVector;
	for (int i = 0; i < _syncObjects.size(); i++) {
		SyncObject<int>* obj = _syncObjects.at(i);
		if (obj->inControl() == false) {
			continue;
		}
		sf::Packet packet;
		packet << PacketType::TSyncObjects << obj->id() << obj->data();
		for (auto* socket : obj->sockets()) {
			_pServer->send(*socket, packet);
		}
	}
}