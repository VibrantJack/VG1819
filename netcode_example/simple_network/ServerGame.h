#pragma once
#include "ServerNetwork.h"
#include "NetworkData.h"

class ServerGame
{

public:

	struct ArmyData {
		int unit1, unit2, unit3;
		int unit4, unit5, unit6;
		int client_id;
	};

    ServerGame(void);
    ~ServerGame(void);

    void update();

	void receiveFromClients();
	void storeArmyData(ClientArmyPacket packet, int p_iClient_id);

	void sendActionPackets();
	void sendStartingDataPackets();
	void sendInitiativePackets();
	void sendStartTurnPacket();

	void sendManipulateTilePacket(ClientManipulateTile packet);

private:

   // IDs for the clients connecting for table in ServerNetwork 
    static unsigned int client_id;

   // The ServerNetwork object 
    ServerNetwork* network;

	// data buffer
   char network_data[MAX_PACKET_SIZE];

   int m_iArmyData = 0;
   ArmyData client1Data;
   ArmyData client2Data;
   bool m_bClient1DataStored, m_bClient2DataStored;
};