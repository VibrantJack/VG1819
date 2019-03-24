/*
* ServerGame
* The Server that handles game data and updates connected
* clients
*/
#include "networking\dedicated_server\ServerGame.h"
#include <algorithm>

namespace networking
{
	//unsigned int ServerGame::client_id;

	ServerGame* ServerGame::sm_serverGameInstance = nullptr;
	bool ServerGame::sm_networkValid = false;

	// Creates the singleton instance.
	void ServerGame::createInstance()
	{
		assert(sm_serverGameInstance == nullptr);
		sm_serverGameInstance = new ServerGame();
	}

	// Destroys the singleton instance.
	void ServerGame::destroyInstance()
	{
		assert(sm_serverGameInstance != nullptr);
		delete sm_serverGameInstance;
		sm_serverGameInstance = nullptr;
		sm_networkValid = false;
		printf("ServerGame shutdown\n");
	}

	// Access to singleton instance.
	ServerGame* ServerGame::getInstance()
	{
		//assert(sm_serverGameInstance);
		return sm_serverGameInstance;
	}

	ServerGame::ServerGame()
		:
		m_shutdown(false),
		m_clientId(0),
		m_polledClientId(0)
	{
		// set up the server network to listen 
		setupNetwork();
	}

	ServerGame::~ServerGame()
	{
		shutdownNetwork();
	}

	void ServerGame::setupNetwork()
	{
		m_network = new ServerNetwork();

		if (!m_network->init())
		{
			printf("Server Network init error: %s\n", m_network->getError().c_str());

			delete m_network;
			m_network = nullptr;

			sm_networkValid = false;
		}
		else
		{
			printf("ServerGame initialized\n");
			sm_networkValid = true;
			setupGameSessions();
		}

	}

	void ServerGame::shutdownNetwork()
	{
		// Shutdown ServerNetwork
		if (m_network != nullptr)
		{
			// Destroy GameSessions first as they need to send packets to players before disconnecting them
			destroyGameSessions();

			delete m_network;
			m_network = nullptr;
		}
		sm_networkValid = false;
	}

	void ServerGame::setupGameSessions()
	{
		for (int i = 0; i < MAX_GAME_SESSIONS; ++i)
		{
			GameSession* session = new GameSession(i, MAX_JOINED_CLIENTS, m_network);
			m_gameSessions.push_back(session);
		}
	}

	void ServerGame::destroyGameSessions()
	{
		for (auto it = m_gameSessions.begin(); it != m_gameSessions.end(); ++it)
		{
			GameSession* session = (*it);
			session->shutdown();
			delete session;
		}
		m_gameSessions.clear();
	}

	void ServerGame::update()
	{
		// get new clients
		if (m_network->acceptNewClient(m_polledClientId))
		{
			printf("[Polled Client: %d] has polled this server\n", m_polledClientId);

			m_polledClientId++;
		}

		receiveFromClients();
		updateGameSessions();

		m_network->removeQueuedRemovals();

		if (m_network->m_serverInfoChanged)
		{
			m_network->sendServerInfo();
			m_network->setServerInfoChanged(false);
		}

		if (m_shutdown)
		{
			shutdownNetwork();
		}
	}

	void ServerGame::receiveFromClients()
	{
		// Go through Polled clients map and receive incoming data
		std::map<unsigned int, ServerNetwork::ClientInfo*>::iterator iter;

		for (iter = m_network->m_sessions.begin(); iter != m_network->m_sessions.end(); /* no increment */)
		{
			// Get the values from the iterator then increment early in the case something is removed from the map
			int polledId = iter->first;
			ServerNetwork::ClientInfo* client = iter->second;
			++iter;

			// If the client is in a GameSession, skip it;
			// the GameSession will update the client
			if (client->m_gameSession != nullptr)
			{
				continue;
			}
			
			int data_length = m_network->receiveData(polledId, m_network_data);

			if (data_length <= 0)
			{
				//no data received
				continue;
			}

			int i = 0;
			while (i < (unsigned int)data_length)
			{
				// Take all incoming packets as Packet initially to read the packetType
				Buffer defaultBuffer;
				defaultBuffer.m_data = &(m_network_data[i]);
				defaultBuffer.m_size = BASIC_PACKET_SIZE;

				Packet defaultPacket;
				defaultPacket.deserialize(defaultBuffer);

				switch (defaultPacket.m_packetType) 
				{
				case QUICKPLAY:
				{
					printf("Server received QUICKPLAY from [Polled Client: %d]\n", polledId);

					if (!findAvailableSession(client))
					{
						char packetData[BASIC_PACKET_SIZE];
						Buffer buffer;
						buffer.m_data = packetData;
						buffer.m_size = BASIC_PACKET_SIZE;

						Packet packet;
						packet.m_packetType = SESSIONS_FULL;
						packet.m_clientId = -1;

						packet.serialize(buffer);
						m_network->sendToClient(polledId, packetData, BASIC_PACKET_SIZE);
					}

					i += BASIC_PACKET_SIZE;
					break;
				}
				case CLIENT_DISCONNECT:
				{
					i += BASIC_PACKET_SIZE;
					printf("Server received CLIENT_DISCONNECT from [Polled Client: %d]\n", polledId);
					m_network->queueClientRemoval(client);
					break;
				}
				case PING_SOCKET:
				{
					i += BASIC_PACKET_SIZE;
					// Server pinged to see if it is still active
					break;
				}
				default:
					printf("error in packet types received from [Polled Client: %d], value: %d\n", polledId, defaultPacket.m_packetType);
					i += (unsigned int)data_length;
					break;
				}
			}
		}
	}

	void ServerGame::updateGameSessions()
	{
		for (GameSession* session : m_gameSessions)
		{
			if (session->m_state == GameSession::SessionState::Active || session->m_state == GameSession::SessionState::Searching)
			{
				session->update();
			}
		}
	}

	// Find an available GameSession to add a player into; the sessions are sorted so Searching sessions are at the front,
	// then Inactive sessions, then Active sessions
	bool ServerGame::findAvailableSession(ServerNetwork::ClientInfo* p_client)
	{
		// Sort not working, getting a Stack Overflow error
		// For now, going to first search for a Searching GameSession, and if none, search for Inactive
		//std::sort(m_gameSessions.begin(), m_gameSessions.end(), GameSession::less_than_key());
		for (GameSession* session : m_gameSessions)
		{
			if (session->m_state == GameSession::SessionState::Searching)
			{
				bool added = session->addPlayer(p_client);
				return added;
			}
		}
		for (GameSession* session : m_gameSessions)
		{
			if (session->m_state == GameSession::SessionState::Inactive)
			{
				bool added = session->addPlayer(p_client);
				return added;
			}
		}
		return false;
	}

	void ServerGame::removeClientFromSession(ServerNetwork::ClientInfo* p_client)
	{
		if (p_client->m_gameSession != nullptr)
		{
			p_client->m_gameSession->removePlayer(p_client);
		}
	}
}