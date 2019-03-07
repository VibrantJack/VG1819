#pragma once
#include "networking\dedicated_server/ServerGame.h"
#include <map>

namespace networking
{
	class GameSession
	{
		enum SessionState
		{
			Active,
			Inactive
		};

	private:
		int m_sessionId;
		int m_maxPlayers;
		std::map<int, ClientInfo> m_currentPlayers;

		char m_networkData[MAX_PACKET_SIZE];

	public:
		SessionState m_state;

		GameSession(int p_sessionId, int p_maxPlayers);
		~GameSession();

		void update();

		bool addPlayer(ClientInfo p_info);
		bool removePlayer(ClientInfo p_info);
		void checkPlayers();
	};
}