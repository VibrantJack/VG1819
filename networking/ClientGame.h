#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "networking\ClientNetwork.h"
#include "networking\NetworkData.h"

namespace networking
{
	class ClientGame
	{
	private:
		static ClientGame* sm_clientGameInstance;
		ClientGame();
		~ClientGame();
	public:
	
		static void createInstance();
		static void destroyInstance();
		static ClientGame* getInstance();
		static int getClientId() { return sm_iClientId; }

		bool setupNetwork(const std::string &p_strAddr = "127.0.0.1");

		void sendPacket(Packet* p_packet);

		void summonUnit(SummonUnitPacket p_packet);

		// Testing methods below
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
		ClientNetwork* m_network;

		char m_network_data[MAX_PACKET_SIZE];
	private:
		static int sm_iClientId;
	};
}