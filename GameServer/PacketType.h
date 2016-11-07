#pragma once

enum PacketType {
	TPing = 0,
	TId, // Followed by client id
	TSyncObjects, // Followed by synced objects in control
	TRemoveSyncedObj, // Followed by object id
};