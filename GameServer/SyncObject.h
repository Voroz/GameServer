#pragma once
#include "SyncManager.h"
#include "Client.h"
#include <vector>

class SyncManager;

template<class T> class SyncObject
{
public:
	// TODO: Make class easier to use. Use of = instead of constructor.
	SyncObject(T data, std::vector<sf::TcpSocket*>& sockets, int id, int inControl, SyncManager* manager) :
		_clients(clients),
		_id(id),
		_inControl(inControl),
		_managerPtr(manager),
		_data(data){
		
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
	T data() {
		return _data;
	}
	void setData(T newData) {
		_data = newData;
	}

private:
	T _data;
	std::vector<sf::TcpSocket*>& _sockets;
	int _id; // Should be same on client and server, 1 id per object.
	const bool _inControl; // Only server OR client should be in control of the object.
	SyncManager* _managerPtr;
};

