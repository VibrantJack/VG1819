/*
* ServerGame
* The Server that handles game data and updates connected
* clients
*/
#include "ServerGame.h"

// Game features to be run on the server
#include "unit\InitiativeTracker\InitiativeTracker.h"

namespace networking
{
	//unsigned int ServerGame::client_id;

	ServerGame* ServerGame::sm_serverGameInstance = nullptr;

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
	}

	// Access to singleton instance.
	ServerGame* ServerGame::getInstance()
	{
		//assert(sm_serverGameInstance);
		return sm_serverGameInstance;
	}

	ServerGame::ServerGame()
	{
		// id's to assign clients for our table
		client_id = 0;

		// set up the server network to listen 
		setupNetwork();
	}

	ServerGame::~ServerGame()
	{
		if (m_network != nullptr)
		{
			delete m_network;
		}
	}

	void ServerGame::setupNetwork()
	{
		m_network = new ServerNetwork();

		if (!m_network->init())
		{
			printf("Server Network init error: %s\n", m_network->getError().c_str());

			delete m_network;
			m_network = nullptr;

			m_networkValid = false;
		}
		else
		{
			m_networkValid = true;
		}

	}

	void ServerGame::shutdownNetwork()
	{
		Packet packet;
		packet.packetType = SERVER_SHUTDOWN;

		char data[BASIC_PACKET_SIZE];
		packet.serialize(data);
		m_network->sendToAll(data, BASIC_PACKET_SIZE);

		// Shutdown ServerNetwork
		if (m_network != nullptr)
		{
			delete m_network;
			m_network = nullptr;
		}

		m_networkValid = false;
	}

	void ServerGame::update()
	{
		// get new clients
		if (m_network->acceptNewClient(client_id))
		{
			printf("[Client: %d] has been connected to the server\n", client_id);

			client_id++;
		}

		receiveFromClients();
	}

	void ServerGame::receiveFromClients()
	{
		// go through all clients to see if they are trying to send data
		std::map<unsigned int, SOCKET>::iterator iter;

		for (iter = m_network->m_sessions.begin(); iter != m_network->m_sessions.end(); iter++)
		{
			int data_length = m_network->receiveData(iter->first, m_network_data);

			if (data_length <= 0)
			{
				//no data recieved
				continue;
			}

			int i = 0;
			while (i < (unsigned int)data_length)
			{
				// Take all incoming packets as Packet initially to read the packetType
				Packet packet;
				packet.deserialize(&(m_network_data[i]));

				switch (packet.packetType) {

					case INIT_CONNECTION:
					{
						i += BASIC_PACKET_SIZE;
						printf("\nserver received init packet from client %d\n", iter->first);

						// Send a packet to the client to notify them what their ID is
						unsigned int clientId = iter->first;
						char packet_data[BASIC_PACKET_SIZE];

						Packet packet;
						packet.packetType = SEND_CLIENT_ID;
						packet.clientId = clientId;

						packet.serialize(packet_data);
						m_network->sendToClient(clientId, packet_data, BASIC_PACKET_SIZE);
						break;
					}
					case CLIENT_DISCONNECT:
					{
						i += BASIC_PACKET_SIZE;
						unsigned int clientId = iter->first;
						printf("\nserver received CLIENT_DISCONNECT from client %d\n", clientId);						
						m_network->removeClient(clientId);

						break;
					}
					case SUMMON_UNIT:
					{
						printf("\nserver received CLIENT_SUMMON_UNIT packet from client %d\n", iter->first);

						SummonUnitPacket summonUnitPacket;
						summonUnitPacket.deserialize(&(m_network_data[i]));
						i += SUMMON_UNIT_PACKET_SIZE;
						sendSummonedUnitPacket(iter->first, summonUnitPacket);

						break;
					}
					case UNIT_MOVE:
					{
						printf("\nserver received UNIT_MOVE packet from client %d\n", iter->first);

						UnitMovePacket packet;
						packet.deserialize(&(m_network_data[i]));
						i += UNIT_MOVE_PACKET_SIZE;
						printf("Server sending Unit index: %d, posX: %d, posY: %d\n", packet.unitIndex, packet.posX, packet.posY);

						// Send received packet to other clients
						char packet_data[UNIT_MOVE_PACKET_SIZE];

						packet.serialize(packet_data);
						m_network->sendToOthers(iter->first, packet_data, UNIT_MOVE_PACKET_SIZE);


						break;
					}

					default:
						//printf("error in packet types received from client %d\n", iter->first);
						break;
				}
			}
		}
	}

	void ServerGame::sendSummonedUnitPacket(unsigned int p_iClientId, SummonUnitPacket p_packet)
	{
		char packet_data[SUMMON_UNIT_PACKET_SIZE];

		p_packet.serialize(packet_data);

		m_network->sendToOthers(p_iClientId, packet_data, SUMMON_UNIT_PACKET_SIZE);
	}
}