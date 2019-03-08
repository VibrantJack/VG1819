#pragma once
#include "networking\dedicated_server/ServerGame.h"
#include <map>

namespace networking
{
	class GameSession
	{
		
	private:
		ServerNetwork* m_network;
		int m_sessionId;
		int m_sessionClientId;
		int m_maxPlayers;
		std::map<int, ClientInfo*> m_currentPlayers;

		char m_networkData[MAX_PACKET_SIZE];

		// Vector to hold the starting data of all player's Commanders
		std::vector<UnitPacket> m_commanders;
		int m_clientsReadyChecked = 0;

		void sendToClient(ClientInfo* p_client, char* p_packets, int p_totalSize);
		void sendToOthers(ClientInfo* p_client, char* p_packets, int p_totalSize);
		void sendToAll(char* p_packets, int p_totalSize);

	public:
		struct less_than_key
		{
			inline bool operator() (const GameSession p_session1, const GameSession p_session2)
			{
				printf("sorting\n");
				return ((p_session1.m_state <= p_session2.m_state) && (p_session1.m_sessionId < p_session2.m_sessionId));
			}
		};
		enum SessionState
		{
			Searching,
			Inactive,
			Active
		};

		SessionState m_state;

		GameSession(int p_sessionId, int p_maxPlayers, ServerNetwork* p_network);
		~GameSession();
		
		void shutdown();
		void update();
		void receiveDataFromPlayers();

		bool addPlayer(ClientInfo* p_info);
		bool removePlayer(ClientInfo* p_info);
		void removeAllPlayers();
		void checkPlayers();
		
	};
}