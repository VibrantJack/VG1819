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
			m_playerCount++;
			m_serverInfoChanged = true;
		}

		receiveFromPolledClients();
		//receiveFromClients();
		updateGameSessions();

		m_network->removeQueuedRemovals();

		if (m_shutdown)
		{
			shutdownNetwork();
		}
	}

	void ServerGame::receiveFromPolledClients()
	{
		// Go through Polled clients map and receive incoming data
		std::map<unsigned int, ServerNetwork::ClientInfo*>::iterator iter;

		for (iter = m_network->m_polledSessions.begin(); iter != m_network->m_polledSessions.end(); /* no increment */)
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
			
			int data_length = m_network->receiveDataFromPolled(polledId, m_network_data);

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
						m_network->sendToPolledClient(polledId, packetData, BASIC_PACKET_SIZE);
					}

					i += BASIC_PACKET_SIZE;
					break;
				}
				case CLIENT_DISCONNECT:
				{
					i += BASIC_PACKET_SIZE;
					printf("Server received CLIENT_DISCONNECT from [Polled Client: %d]\n", polledId);
					m_network->queuePolledClientRemoval(client);
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

	void ServerGame::receiveFromClients()
	{
		// go through all clients to see if they are trying to send data
		std::map<unsigned int, ServerNetwork::ClientInfo*>::iterator iter;

		for (iter = m_network->m_sessions.begin(); iter != m_network->m_sessions.end(); /* no increment */)
		{
			// Get the values and then increment early in the case that something is removed from the map
			int clientId = iter->first;
			ServerNetwork::ClientInfo* client = iter->second;
			++iter;

			int data_length = m_network->receiveData(clientId, m_network_data);
			if (data_length <= 0)
			{
				//no data recieved
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

				switch (defaultPacket.m_packetType) {
					case JOIN_GAME:
					{
						i += BASIC_PACKET_SIZE;
						printf("Server received JOIN_GAME packet from [Client: %d]\n", clientId);

						// Send a packet to the client to notify them what their ID is
						char packetData[BASIC_PACKET_SIZE];

						Buffer buffer;// = NetworkServices::createBuffer(BASIC_PACKET_SIZE);
						buffer.m_data = packetData;
						buffer.m_size = BASIC_PACKET_SIZE;

						Packet packet;
						packet.m_packetType = JOIN_GAME;
						packet.m_clientId = clientId;

						packet.serialize(buffer);
						m_network->sendToClient(clientId, packetData, BASIC_PACKET_SIZE);
						break;
					}
					case INIT_CONNECTION:
					{
						i += BASIC_PACKET_SIZE;
						printf("Server received init packet from [Client: %d]\n", clientId);

						// Send a packet to the client to notify them what their ID is
						char packetData[BASIC_PACKET_SIZE];

						Buffer buffer;// = NetworkServices::createBuffer(BASIC_PACKET_SIZE);
						buffer.m_data = packetData;
						buffer.m_size = BASIC_PACKET_SIZE;

						Packet packet;
						packet.m_packetType = SEND_CLIENT_ID;
						packet.m_clientId = clientId;

						packet.serialize(buffer);
						m_network->sendToClient(clientId, packetData, BASIC_PACKET_SIZE);
						break;
					}
					case CLIENT_DISCONNECT:
					{
						i += BASIC_PACKET_SIZE;
						printf("Server received CLIENT_DISCONNECT from [Client: %d]\n", clientId);
						m_network->queueClientRemoval(client);

						break;
					}
					case ABILITY_PACKET:
					{
						printf("Server received ABILITY_PACKET from [Client: %d]\n", clientId);
						Buffer buffer;
						buffer.m_data = &(m_network_data[i]);
						buffer.m_size = MAX_PACKET_SIZE;

						AbilityPacket packet;
						packet.deserialize(buffer);
						int packetTotalBytes = packet.getBytes();
						i += packetTotalBytes;

						char* data = new char[packetTotalBytes];
						Buffer newBuffer;
						newBuffer.m_data = data;
						newBuffer.m_size = packetTotalBytes;
						packet.serialize(newBuffer);
						m_network->sendToOthers(clientId, data, packetTotalBytes);
						delete[] data;

						break;
					}
					case CAST_TIME_ABILITY_PACKET:
					{
						printf("Server received CAST_TIME_ABILITY_PACKET from [Client: %d]\n", clientId);
						Buffer buffer;
						buffer.m_data = &(m_network_data[i]);
						buffer.m_size = MAX_PACKET_SIZE;

						AbilityPacket packet;
						packet.deserialize(buffer);
						int packetTotalBytes = packet.getBytes();
						i += packetTotalBytes;

						char* data = new char[packetTotalBytes];
						Buffer newBuffer;
						newBuffer.m_data = data;
						newBuffer.m_size = packetTotalBytes;
						packet.serialize(newBuffer);
						m_network->sendToOthers(clientId, data, packetTotalBytes);
						delete[] data;

						break;
					}
					case SUMMON_UNIT:
					{
						printf("Server received SUMMON_UNIT packet from [Client: %d]\n", clientId);
						Buffer buffer;
						buffer.m_data = &(m_network_data[i]);
						buffer.m_size = UNIT_PACKET_SIZE;

						UnitPacket summonUnitPacket;
						summonUnitPacket.deserialize(buffer);
						i += UNIT_PACKET_SIZE;
						printf("Server sending Unit index: %d, posX: %d, posY: %d\n", summonUnitPacket.m_unitId, summonUnitPacket.m_posX, summonUnitPacket.m_posY);
						
						char data[UNIT_PACKET_SIZE];
						Buffer newBuffer;
						newBuffer.m_data = data;
						newBuffer.m_size = UNIT_PACKET_SIZE;
						summonUnitPacket.serialize(newBuffer);
						m_network->sendToOthers(clientId, data, UNIT_PACKET_SIZE);

						break;
					}
					case READY_CHECK:
					{
						printf("Server received READY_CHECK packet from [Client: %d]\n", clientId);

						if (m_clientsReadyChecked < MAX_JOINED_CLIENTS)
						{
							m_clientsReadyChecked++;

							if (m_clientsReadyChecked == MAX_JOINED_CLIENTS)
							{
								char data[BASIC_PACKET_SIZE];
								Buffer newBuffer;
								newBuffer.m_data = data;
								newBuffer.m_size = BASIC_PACKET_SIZE;

								Packet basicPacket;
								basicPacket.m_packetType = READY_CHECK;
								basicPacket.m_clientId = -1;

								basicPacket.serialize(newBuffer);
								m_network->sendToAll(data, BASIC_PACKET_SIZE);
							}
						}
						i += BASIC_PACKET_SIZE;
						break;
					}
					case STARTING_COMMANDER_DATA:
					{
						printf("Server received STARTING_COMMANDER_DATA packet from [Client: %d]\n", clientId);
						Buffer buffer;
						buffer.m_data = &(m_network_data[i]);
						buffer.m_size = UNIT_PACKET_SIZE;

						UnitPacket commanderDataPacket;
						commanderDataPacket.deserialize(buffer);

						m_commanders.push_back(commanderDataPacket);
						if (m_commanders.size() == 2)
						{
							char data[STARTING_COMMANDERS_PACKET_SIZE];
							Buffer newBuffer;
							newBuffer.m_data = data;
							newBuffer.m_size = STARTING_COMMANDERS_PACKET_SIZE;

							StartingCommandersPacket commandersPacket;
							commandersPacket.m_packetType = STARTING_COMMANDER_DATA;
							commandersPacket.m_clientId = -1; // -1 to signal originally from the Server

							commandersPacket.commander0.clientId = m_commanders[0].m_clientId;
							commandersPacket.commander0.unitId = m_commanders[0].m_unitId;
							commandersPacket.commander0.posX = m_commanders[0].m_posX;
							commandersPacket.commander0.posY = m_commanders[0].m_posY;

							commandersPacket.commander1.clientId = m_commanders[1].m_clientId;
							commandersPacket.commander1.unitId = m_commanders[1].m_unitId;
							commandersPacket.commander1.posX = m_commanders[1].m_posX;
							commandersPacket.commander1.posY = m_commanders[1].m_posY;

							commandersPacket.serialize(newBuffer);
							m_network->sendToAll(data, STARTING_COMMANDERS_PACKET_SIZE);
						}
						i += UNIT_PACKET_SIZE;
						break;
					}
					case TEXTCHAT_MESSAGE:
					{
						i += TEXTCHAT_MESSAGE_PACKET_SIZE;
						printf("Server received TEXTCHAT_MESSAGE packet from [Client: %d]\n", clientId);
						m_network->sendToOthers(clientId, defaultBuffer.m_data, TEXTCHAT_MESSAGE_PACKET_SIZE);
						break;
					}
					case SKIP_TURN:
					{
						i += SKIP_TURN_PACKET_SIZE;
						printf("Server received SKIP_TURN packet from [Client: %d]\n", clientId);

						m_network->sendToOthers(clientId, defaultBuffer.m_data, SKIP_TURN_PACKET_SIZE);
						break;
					}
					case PING_SOCKET:
					{
						i += BASIC_PACKET_SIZE;
						// Server pinged to see if it is still active
						break;
					}
					case GAME_TURN_START:
					case DESYNCED:
					{
						i += BASIC_PACKET_SIZE;
						printf("Server received BasicPacket PacketType: %d from [Client: %d]\n", defaultPacket.m_packetType, clientId);

						m_network->sendToAll(defaultBuffer.m_data, BASIC_PACKET_SIZE);
						break;
					}
					default:
						printf("error in packet types received from [Client %d], value: %d\n", clientId, defaultPacket.m_packetType);
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