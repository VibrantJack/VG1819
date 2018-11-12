// ClientGame
//
// Initializes ClientNetwork and sets up anything that needs to be setup on init connection
// Has update loop to always check for incoming data from the server
//
// @Ken

#include "networking\ClientGame.h"
#include <assert.h>
#include <iostream>

// Kibble
#include "kibble\databank\databank.hpp"

// Units
#include "kitten\K_GameObjectManager.h"
#include "unit\UnitSpawn.h"
#include "unit\unitComponent\UnitMove.h"
#include "unit\UnitMonitor.h"

// Unit movement
#include "board\BoardManager.h"
#include "unit\unitComponent\UnitMove.h"

namespace networking
{
	ClientGame* ClientGame::sm_clientGameInstance = nullptr;

	// Creates the singleton instance.
	void ClientGame::createInstance(const std::string &p_strAddr)
	{
		assert(sm_clientGameInstance == nullptr);
		sm_clientGameInstance = new ClientGame(p_strAddr);
	}

	// Destroys the singleton instance.
	void ClientGame::destroyInstance()
	{
		assert(sm_clientGameInstance != nullptr);
		delete sm_clientGameInstance;
		sm_clientGameInstance = nullptr;
	}

	// Access to singleton instance.
	ClientGame* ClientGame::getInstance()
	{
		//assert(sm_clientGameInstance);
		return sm_clientGameInstance;
	}

	ClientGame::ClientGame(const std::string &p_strAddr)
	{
		setupNetwork(p_strAddr);
	}


	ClientGame::~ClientGame()
	{
		if (m_network != nullptr)
		{
			delete m_network;
		}

		auto end = m_unitGOList.end();
		for (auto it = m_unitGOList.begin(); it != end; ++it)
		{
			kitten::K_GameObjectManager::getInstance()->destroyGameObject((*it).second);
		}
	}

	void ClientGame::setupNetwork(const std::string &p_strAddr)
	{
		m_network = new ClientNetwork();

		if (m_network->init(p_strAddr))
		{ 
			// Client connects and sends INIT_CONNECTION packet
			char packet_data[BASIC_PACKET_SIZE];

			Packet packet;
			packet.packetType = INIT_CONNECTION;
			packet.serialize(packet_data);
			NetworkServices::sendMessage(m_network->m_connectSocket, packet_data, BASIC_PACKET_SIZE);

			m_networkValid = true;
		}
		else
		{
			printf("Client Network init error: %s\n", m_network->getError().c_str());

			delete m_network;
			m_network = nullptr;

			m_networkValid = false;
		}
	}

	void ClientGame::disconnectFromNetwork(bool p_bServerShutdown)
	{
		// If Server sent disconnect then no need to send packet to server
		if (!p_bServerShutdown)
		{
			// Send a packet to alert server that client is disconnecting
			Packet packet;
			packet.packetType = CLIENT_DISCONNECT;
			packet.clientId = m_iClientId;

			char data[BASIC_PACKET_SIZE];
			packet.serialize(data);
			NetworkServices::sendMessage(m_network->m_connectSocket, data, BASIC_PACKET_SIZE);
		}

		// Shutdown ClientNetwork
		if (m_network != nullptr)
		{
			delete m_network;
			m_network = nullptr;
		}

		m_networkValid = false;

	}

	void ClientGame::update()
	{
		Packet packet;
		int data_length = m_network->receivePackets(m_network_data);

		if (data_length <= 0)
		{
			//no data recieved
			return;
		}

		int i = 0;
		PacketTypes packetType;

		while (i < (unsigned int)data_length)
		{
			packet.deserialize(&(m_network_data[i]));
			packetType = (PacketTypes)packet.packetType;

			switch (packetType) {

			case PacketTypes::SEND_CLIENT_ID:
			{
				i += BASIC_PACKET_SIZE;

				m_iClientId = packet.clientId;
				break;
			}
			case PacketTypes::SERVER_SHUTDOWN:
			{
				printf("[Client: %d] received SERVER_SHUTDOWN packet from server\n", m_iClientId);

				i += BASIC_PACKET_SIZE;
				disconnectFromNetwork(true);
				// @TODO: After disconnecting from network, we should prompt to return to main menu or something similar
				// After returning to main menu, we then destroy ClientGame
				break;
			}
			case PacketTypes::SUMMON_UNIT:
			{
				printf("[Client: %d] received CLIENT_SUMMON_UNIT packet from server\n", m_iClientId);

				SummonUnitPacket summonUnitPacket;
				summonUnitPacket.deserialize(&(m_network_data[i]));
				i += SUMMON_UNIT_PACKET_SIZE;

				// Call function here that summons a unit
				summonUnit(summonUnitPacket.clientId, summonUnitPacket.unitId, summonUnitPacket.posX, summonUnitPacket.posY);
				break;
			}
			case PacketTypes::UNIT_MOVE:
			{
				printf("[Client: %d] received UNIT_MOVE packet from server\n", m_iClientId);

				UnitMovePacket unitMovePacket;
				unitMovePacket.deserialize(&(m_network_data[i]));
				i += UNIT_MOVE_PACKET_SIZE;
				printf("[Client: %d] received Unit index: %d, posX: %d, posY: %d\n", m_iClientId, unitMovePacket.unitIndex, unitMovePacket.posX, unitMovePacket.posY);

				// Call function here that summons a unit
				moveUnit(unitMovePacket.unitIndex, unitMovePacket.posX, unitMovePacket.posY);
				break;
			}
			default:
				printf("error in packet types\n");
				break;
			}
		}
	}

	int ClientGame::getUnitGameObjectIndex(kitten::K_GameObject* p_unit)
	{
		for (auto it = m_unitGOList.begin(); it != m_unitGOList.end(); ++it)
		{
			if (it->second == p_unit)
			{
				return it->first;
			}
		}
		return -1; // Not found
	}

	void ClientGame::summonUnit(int p_iClientId, int p_iUnitId, int p_iPosX, int p_iPosY)
	{
		// Create the unit GO and add it to the list
		kitten::K_GameObject* unitGO = unit::UnitSpawn::getInstance()->spawnUnitObject(kibble::getUnitFromId(p_iUnitId));
		m_unitGOList.insert(std::make_pair(m_iUnitIndex, unitGO));
		m_iUnitIndex++;

		//initialize position
		unitGO->getComponent<unit::UnitMove>()->setTile(p_iPosX, p_iPosY);
		unitGO->getComponent<unit::Unit>()->m_clientId = m_iClientId;

		// Print out unit data for debug
		unit::Unit* testDummy = unitGO->getComponent<unit::Unit>();
		testDummy->m_clientId = p_iClientId;
		unit::UnitMonitor::getInstanceSafe()->printUnit(testDummy);
	}

	void ClientGame::moveUnit(int p_iUnitIndex, int p_iPosX, int p_iPosY)
	{
		kitten::K_GameObject* targetTile = BoardManager::getInstance()->getTile(p_iPosX, p_iPosY);
		m_unitGOList.at(p_iUnitIndex)->getComponent<unit::UnitMove>()->move(targetTile);
	}

	void ClientGame::sendPacket(Packet* p_packet)
	{
		switch (p_packet->packetType)
		{
		case PacketTypes::SUMMON_UNIT:
		{
			char data[SUMMON_UNIT_PACKET_SIZE];

			SummonUnitPacket* packet = static_cast<SummonUnitPacket*>(p_packet);
			packet->serialize(data);
			NetworkServices::sendMessage(m_network->m_connectSocket, data, SUMMON_UNIT_PACKET_SIZE);
			break;
		}

		case PacketTypes::UNIT_MOVE:
		{
			char data[UNIT_MOVE_PACKET_SIZE];

			UnitMovePacket* packet = static_cast<UnitMovePacket*>(p_packet);
			packet->serialize(data);
			NetworkServices::sendMessage(m_network->m_connectSocket, data, UNIT_MOVE_PACKET_SIZE);
			break;
		}
		}

		delete p_packet;
		p_packet = nullptr;

	}

	void ClientGame::sendSummonUnitPacket(int p_iClientId, int p_iUnitId, int p_iPosX, int p_iPosY)
	{
		SummonUnitPacket packet;
		packet.packetType = PacketTypes::SUMMON_UNIT;
		packet.clientId = p_iClientId;
		packet.unitId = p_iUnitId;
		packet.posX = p_iPosX;
		packet.posY = p_iPosY;

		char data[SUMMON_UNIT_PACKET_SIZE];
		packet.serialize(data);
		NetworkServices::sendMessage(m_network->m_connectSocket, data, SUMMON_UNIT_PACKET_SIZE);
	}

	void ClientGame::sendMovementPacket(int p_iUnitIndex, int p_iPosX, int p_iPosY)
	{
		UnitMovePacket packet;
		packet.packetType = PacketTypes::UNIT_MOVE;
		packet.clientId = m_iClientId;
		packet.unitIndex = p_iUnitIndex;
		packet.posX = p_iPosX;
		packet.posY = p_iPosY;

		char data[UNIT_MOVE_PACKET_SIZE];
		packet.serialize(data);
		NetworkServices::sendMessage(m_network->m_connectSocket, data, UNIT_MOVE_PACKET_SIZE);
	}
}