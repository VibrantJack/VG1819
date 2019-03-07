#include "GameSession.h"

namespace networking
{
	GameSession::GameSession(int p_sessionId, int p_maxPlayers)	
		: 
		m_sessionId(p_sessionId), 
		m_maxPlayers(p_maxPlayers),
		m_state(SessionState::Inactive)
	{

	}

	GameSession::~GameSession()
	{

	}

	void GameSession::update()
	{
		for (auto it = m_currentPlayers.begin(); it != m_currentPlayers.end(); ++it)
		{
			int dataLength = ServerGame::getInstance()->m_network->receiveData(it->second, m_networkData);
			if (dataLength <= 0)
			{
				// No data received
				continue;
			}

			int i = 0;
			while (i < (unsigned int)dataLength)
			{
				Buffer defaultBuffer;
				defaultBuffer.m_data = &(m_networkData[i]);
				defaultBuffer.m_size = BASIC_PACKET_SIZE;

				Packet defaultPacket;
				defaultPacket.deserialize(defaultBuffer);

				switch (defaultPacket.m_packetType)
				{
					case JOIN_GAME:
					{
						printf("JOIN_GAME packet\n");
					}
				}
			}
		}
	}

	// Returns true if player added, or false if already in session or no space in session
	bool GameSession::addPlayer(ClientInfo p_info)
	{
		if (m_currentPlayers.size() < m_maxPlayers)
		{
			auto result = m_currentPlayers.insert(std::make_pair(p_info.m_clientId, p_info));
			checkPlayers();
			return result.second;
		}
		else
		{
			return false;
		}
	}

	bool GameSession::removePlayer(ClientInfo p_info)
	{
		int erased = m_currentPlayers.erase(p_info.m_clientId);
		checkPlayers();
		return erased;
	}

	void GameSession::checkPlayers()
	{
		if (m_currentPlayers.size() == m_maxPlayers)
		{
			m_state = SessionState::Active;
		}
		else if (m_state == SessionState::Active && m_currentPlayers.size() < m_maxPlayers)
		{
			// TODO: Kick all remaining players from this session
			m_state = SessionState::Inactive;
		}
	}
}