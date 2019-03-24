#pragma once
#include "networking\dedicated_server\ServerNetwork.h"
#include "networking\dedicated_server\NetworkData.h"
#include "networking\dedicated_server\GameSession.h"
#include <vector>

#define MAX_JOINED_CLIENTS 2
#define MAX_GAME_SESSIONS 2

namespace networking
{
	class ServerGame
	{
	friend class GameSession;
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

		void setupGameSessions();
		void destroyGameSessions();

		void update();
		void receiveFromClients();
		void updateGameSessions();

		bool findAvailableSession(ServerNetwork::ClientInfo* p_info);
		void removeClientFromSession(ServerNetwork::ClientInfo* p_info);

		void sendServerInfo();
		void flagShutdown(bool p_flag) { m_shutdown = p_flag; }

	private:

		// IDs for the clients connecting for table in ServerNetwork 
		unsigned int m_clientId;
		unsigned int m_polledClientId;

		// The ServerNetwork object 
		ServerNetwork* m_network;

		// data buffer
		char m_network_data[MAX_PACKET_SIZE];
		bool m_shutdown;

		static bool sm_networkValid;

		// Vector to hold the starting data of all player's Commanders
		std::vector<UnitPacket> m_commanders;

		// Map of GameSessions to be used by the server
		std::vector<GameSession*> m_gameSessions;

		int m_clientsReadyChecked = 0;
	};
}