#include "Server.h"
#include "SyncManager.h"



int main() {
	Server server;
	SyncManager syncManager(&server);
	server.linkSyncManager(syncManager);

	server.run();

	while (1) {

	}

	return 0;
}