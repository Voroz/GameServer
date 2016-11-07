#include "Client.h"



Client::Client(sf::TcpSocket* socket) :
	socket(socket),
	_id(nextId++) {

};
int Client::id() {
	return _id;
}
