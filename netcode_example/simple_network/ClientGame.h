#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"

class ClientGame
{
public:
	ClientGame(void);
	~ClientGame(void);


	void sendActionPackets();

	// Test methods to print packet data
	void storeStartingData(StartingDataPacket packet);
	void receiveInitiativePacket(InitiativeDataPacket packet);
	void receiveStartTurnPacket(StartTurnPacket packet);
	void receiveManipulatedTilePacket(ClientManipulateTile packet);

	// Example method to display how the client can input data and send to server
	void manipulateTile();

	void update();

public:
	ClientNetwork* network;

	char network_data[MAX_PACKET_SIZE];
};

