#pragma once
#include "networking/ServerNetwork.h"
#include "networking/NetworkData.h"

namespace networking
{
	class ServerGame
	{

	private:
		static ServerGame* sm_serverGameInstance;
		ServerGame();
		~ServerGame();
	public:

		static void createInstance();
		static void destroyInstance();
		static ServerGame* getInstance();

		bool setupNetwork();

		void update();
		void receiveFromClients();
		
		void sendSummonedUnitPacket(unsigned int p_iClientId, SummonUnitPacket p_packet);

	private:

		// IDs for the clients connecting for table in ServerNetwork 
		static unsigned int client_id;

		// The ServerNetwork object 
		ServerNetwork* m_network;

		// data buffer
		char m_network_data[MAX_PACKET_SIZE];

		int m_iArmyData = 0;
		bool m_bClient1DataStored, m_bClient2DataStored;
	};
}