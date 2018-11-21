/*
* ServerGame
* The Server that handles game data and updates connected
* clients
*/
#include "ServerGame.h"
#include "ClientGame.h"

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

			sm_networkValid = false;
		}
		else
		{
			sm_networkValid = true;
		}

	}

	void ServerGame::shutdownNetwork()
	{
		// Shutdown ServerNetwork
		if (m_network != nullptr)
		{
			char data[BASIC_PACKET_SIZE];

			Buffer buffer;
			buffer.m_data = data;
			buffer.m_size = BASIC_PACKET_SIZE;

			Packet packet;
			packet.m_packetType = SERVER_SHUTDOWN;
			packet.serialize(buffer);

			m_network->sendToAll(data, BASIC_PACKET_SIZE);

			delete m_network;
			m_network = nullptr;
		}

		sm_networkValid = false;
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
				Buffer defaultBuffer;
				defaultBuffer.m_data = &(m_network_data[i]);
				defaultBuffer.m_size = BASIC_PACKET_SIZE;

				Packet defaultPacket;
				defaultPacket.deserialize(defaultBuffer);

				switch (defaultPacket.m_packetType) {

					case INIT_CONNECTION:
					{
						i += BASIC_PACKET_SIZE;
						printf("Server received init packet from [Client: %d]\n", iter->first);

						// Send a packet to the client to notify them what their ID is
						int clientId = iter->first;
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
						unsigned int clientId = iter->first;
						printf("Server received CLIENT_DISCONNECT from [Client: %d]\n", clientId);						
						m_network->removeClient(clientId);

						break;
					}
					case SUMMON_UNIT:
					{
						printf("Server received CLIENT_SUMMON_UNIT packet from [Client: %d]\n", iter->first);

						SummonUnitPacket summonUnitPacket;
						summonUnitPacket.deserialize(&(m_network_data[i]));
						i += SUMMON_UNIT_PACKET_SIZE;
						sendSummonedUnitPacket(iter->first, summonUnitPacket);

						break;
					}
					case UNIT_MOVE:
					{
						printf("Server received UNIT_MOVE packet from [Client: %d]\n", iter->first);

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
					case MANIPULATE_TILE:
					{
						printf("Server received MANIPULATE_TILE packet from [Client: %d]\n", iter->first);

						ManipulateTilePacket manipPacket;
						manipPacket.deserialize(&(m_network_data[i]));
						i += MANIPULATE_PACKET_SIZE;
						printf("Server sending ability name: %s, unit index: %d, posX: %d, posY: %d\n", manipPacket.abilityName, manipPacket.unitIndex, manipPacket.posX, manipPacket.posY);

						// Send received packet to other clients
						char packet_data[MANIPULATE_PACKET_SIZE];
						manipPacket.serialize(packet_data);

						m_network->sendToOthers(iter->first, packet_data, MANIPULATE_PACKET_SIZE);
						break;
					}
					case SOURCE_TARGET_DMG_ABILITY:
					{
						printf("Server received SOURCE_TARGET_DMG_ABILITY packet from [Client: %d]\n", iter->first);

						SourceTargetDamagePacket stpPacket;
						stpPacket.deserialize(&(m_network_data[i]));
						i += SOURCE_TARGET_DAMAGE_PACKET_SIZE;
						printf("Server sending ability name: %s, source index: %d, target index: %d, power: %d\n", 
							stpPacket.abilityName, stpPacket.sourceUnitIndex, stpPacket.targetUnitIndex, stpPacket.power);

						// Send received packet to other clients
						char packet_data[SOURCE_TARGET_DAMAGE_PACKET_SIZE];
						stpPacket.serialize(packet_data);

						m_network->sendToOthers(iter->first, packet_data, SOURCE_TARGET_DAMAGE_PACKET_SIZE);
						break;
					}
					case SINGLE_TILE_ABILITY:
					{
						printf("Server received SINGLE_TILE_ABILITY packet from [Client: %d]\n", iter->first);

						SingleTilePacket stPacket;
						stPacket.deserialize(&(m_network_data[i]));
						i += SINGLE_TILE_PACKET_SIZE;
						printf("Server sending ability name: %s, posX: %d, posY: %d\n",
							stPacket.abilityName, stPacket.posX, stPacket.posY);

						// Send received packet to other clients
						char packet_data[SINGLE_TILE_PACKET_SIZE];
						stPacket.serialize(packet_data);

						m_network->sendToOthers(iter->first, packet_data, SINGLE_TILE_PACKET_SIZE);
						break;
					}
					case SINGLE_TARGET_ABILITY:
					{
						printf("Server received SINGLE_TARGET_ABILITY packet from [Client: %d]\n", iter->first);

						SingleTargetPacket sTgtPacket;
						sTgtPacket.deserialize(&(m_network_data[i]));
						i += SINGLE_TARGET_PACKET_SIZE;
						printf("Server sending ability name: %s, source unit: %d, target index: %d, dur: %d, pow: %d\n",
							sTgtPacket.abilityName, sTgtPacket.sourceUnitIndex, sTgtPacket.targetUnitIndex, sTgtPacket.dur, sTgtPacket.pow);

						// Send received packet to other clients
						char packet_data[SINGLE_TARGET_PACKET_SIZE];
						sTgtPacket.serialize(packet_data);

						m_network->sendToOthers(iter->first, packet_data, SINGLE_TARGET_PACKET_SIZE);
						break;
					}
					default:
						printf("error in packet types received from client %d\n", iter->first);
						i += (unsigned int)data_length;						
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