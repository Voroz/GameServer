#pragma once
#include "SyncManager.h"
#include "Client.h"
#include <vector>

class SyncManager;

template<class T> class SyncObject
{
public:
	SyncObject(std::vector<sf::TcpSocket*>& sockets, int id, int inControl, SyncManager* manager) :
		_clients(clients),
		_id(id),
		_inControl(inControl),
		_managerPtr(manager){
		_managerPtr->addObject(this);
	}
	~SyncObject() {

	}
	int id() {
		return _id;
	}
	std::vector<sf::TcpSocket*>& sockets() {
		return _sockets;
	}
	bool inControl() {
		return _inControl;
	}

private:
	std::vector<sf::TcpSocket*>& _sockets;
	int _id; // Should be same on client and server, 1 id per object.
	bool _inControl; // Only server OR client should be in control of the object.
	SyncManager* _managerPtr;
};

