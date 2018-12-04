#pragma once
#include "networking/ServerNetwork.h"
#include "networking/NetworkData.h"
#include <vector>

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
		static bool isNetworkValid() { return sm_networkValid; }

		void setupNetwork();
		void shutdownNetwork();

		void update();
		void receiveFromClients();
		
		void sendSummonedUnitPacket(unsigned int p_iClientId, SummonUnitPacket p_packet);

	private:

		// IDs for the clients connecting for table in ServerNetwork 
		unsigned int client_id;

		// The ServerNetwork object 
		ServerNetwork* m_network;

		// data buffer
		char m_network_data[MAX_PACKET_SIZE];

		static bool sm_networkValid;

		// Vector to hold the starting data of all player's Commanders
		std::vector<SummonUnitPacket> m_commanders;
	};
}