#pragma once

enum PacketType {
	TPing = 0,
	TId, // Followed by client id
	TRemoveSyncedObj, // Followed by object id
};