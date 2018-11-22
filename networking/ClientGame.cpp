// ClientGame
//
// Initializes ClientNetwork and sets up anything that needs to be setup on init connection
// Has update loop to always check for incoming data from the server
//
// @Ken

#include "networking\ClientGame.h"
#include <assert.h>
#include <iostream>
#include <unordered_map>

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
	bool ClientGame::sm_networkValid = false;

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
		sm_networkValid = false;
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

		/*auto end = m_unitGOList.end();
		for (auto it = m_unitGOList.begin(); it != end; ++it)
		{
			kitten::K_GameObjectManager::getInstance()->destroyGameObject((*it).second);
		}*/
	}

	void ClientGame::setupNetwork(const std::string &p_strAddr)
	{
		m_network = new ClientNetwork();

		if (m_network->init(p_strAddr))
		{ 
			// Client connects and sends INIT_CONNECTION packet
			char packet_data[BASIC_PACKET_SIZE];

			Buffer buffer;
			buffer.m_data = packet_data;
			buffer.m_size = BASIC_PACKET_SIZE;

			Packet packet;
			packet.m_packetType = INIT_CONNECTION;
			packet.serialize(buffer);

			NetworkServices::sendMessage(m_network->m_connectSocket, packet_data, BASIC_PACKET_SIZE);

			sm_networkValid = true;
		}
		else
		{
			printf("Client Network init error: %s\n", m_network->getError().c_str());

			delete m_network;
			m_network = nullptr;

			sm_networkValid = false;
		}
	}

	void ClientGame::disconnectFromNetwork(bool p_bServerShutdown)
	{
		// If Server sent disconnect then no need to send packet to server
		if (!p_bServerShutdown)
		{
			// Send a packet to alert server that client is disconnecting
			char data[BASIC_PACKET_SIZE];

			Buffer buffer;
			buffer.m_data = data;
			buffer.m_size = BASIC_PACKET_SIZE;

			Packet packet;
			packet.m_packetType = CLIENT_DISCONNECT;
			packet.m_clientId = m_iClientId;		

			packet.serialize(buffer);
			NetworkServices::sendMessage(m_network->m_connectSocket, data, BASIC_PACKET_SIZE);
		}

		// Shutdown ClientNetwork
		if (m_network != nullptr)
		{
			delete m_network;
			m_network = nullptr;
		}

		sm_networkValid = false;

	}

	void ClientGame::update()
	{
		int data_length = m_network->receivePackets(m_network_data);

		if (data_length <= 0)
		{
			//no data recieved
			return;
		}
		//printf("Bytes received: %d\n", data_length);
		int i = 0;
		PacketTypes packetType;

		while (i < (unsigned int)data_length)
		{
			//printf("Start of Loop Count i: %d\n", i);
			Buffer defaultBuffer;
			defaultBuffer.m_data = &(m_network_data[i]);
			defaultBuffer.m_size = BASIC_PACKET_SIZE;

			Packet defaultPacket;
			defaultPacket.deserialize(defaultBuffer);

			packetType = (PacketTypes)defaultPacket.m_packetType;
			printf("PacketType received: %d\n", packetType);
			switch (packetType) {

			case PacketTypes::SEND_CLIENT_ID:
			{
				i += BASIC_PACKET_SIZE;
				m_iClientId = defaultPacket.m_clientId;
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
			case PacketTypes::ABILITY_PACKET:
			{
				printf("[Client: %d] received ABILITY_PACKET packet from server\n", m_iClientId);

				Buffer buffer;
				buffer.m_data = &(m_network_data[i]);
				buffer.m_size = MAX_PACKET_SIZE;

				AbilityPacket packet;
				packet.deserialize(buffer);
				packet.print();
				printf("data_length: %d\n", data_length);
				printf("Before increment Count i: %d\n", i);
				i += packet.getBytes();
				printf("Incremented Count i: %d\n", i);
				useAbility(packet);
				break;
			}
			case PacketTypes::SUMMON_UNIT:
			{
				printf("[Client: %d] received CLIENT_SUMMON_UNIT packet from server\n", m_iClientId);

				Buffer buffer;
				buffer.m_data = &(m_network_data[i]);
				buffer.m_size = SUMMON_UNIT_PACKET_SIZE;

				SummonUnitPacket summonUnitPacket;
				summonUnitPacket.deserialize(buffer);
				i += SUMMON_UNIT_PACKET_SIZE;

				summonUnit(summonUnitPacket.m_clientId, summonUnitPacket.unitId, summonUnitPacket.posX, summonUnitPacket.posY);
				break;
			}
			case PacketTypes::SKIP_TURN:
			{
				i += BASIC_PACKET_SIZE;
				m_bServerCalling = true;
				unit::Unit* currentUnit = unit::InitiativeTracker::getInstance()->getCurrentUnit()->getComponent<unit::Unit>();
				currentUnit->playerSkipTurn();
				m_bServerCalling = false;

				break;
			}
			default:
				printf("[Client: %d] received %d; error in packet types\n", packetType);
				i += (unsigned int)data_length;
				break;
			}
		}
	}

	void ClientGame::useAbility(AbilityPacket& p_packet)
	{
		std::string strAbilityName = p_packet.m_abilityName;
		printf("[Client: %d] using ability: %s\n", m_iClientId, strAbilityName.c_str());

		ability::AbilityInfoPackage* info = new ability::AbilityInfoPackage();
		info->m_source = getUnitGameObject(p_packet.sourceUnit)->getComponent<unit::Unit>();
		info->m_targets = p_packet.getTargetUnits();
		info->m_intValue = p_packet.getIntValues();
		info->m_targetTilesGO = p_packet.getTargetTiles();

		ability::AbilityManager::getInstance()->findAbility(strAbilityName)->effect(info);
	}

	void ClientGame::testNewPacket(const std::string & p_strAbilityName, ability::AbilityInfoPackage * p_info)
	{
		AbilityPacket packet;
		packet.packetType = 0; // Create new enum for AbilityPacket
		packet.clientId = 1;
		packet.sourceUnit = 2;

		//packet.m_numTargetUnits = p_info->m_targets.size();
		//packet.m_targets = p_info->m_targets;

		//packet.m_numIntValues = p_info->m_intValue.size();
		//packet.m_intValue = p_info->m_intValue;

		//packet.m_numTargetTiles = p_info->m_targetTilesGO.size();
		//packet.m_targetTilesGO = p_info->m_targetTilesGO;

		packet.addTargetUnits(p_info->m_targets);
		packet.addIntValues(p_info->m_intValue);
		packet.addTargetTiles(p_info->m_targetTilesGO);

		packet.m_abilityNameLength = p_strAbilityName.size();
		//strcpy(packet.m_abilityName, p_strAbilityName.c_str());
		packet.m_abilityName = p_strAbilityName;

		//char* data = new char[packet.getSize()];
		char data[1000000];
		Buffer buffer;
		buffer.m_data = data;
		buffer.m_size = packet.getSize();
		packet.serialize(buffer);

		Buffer buffer2;
		buffer2.m_data = data;
		buffer2.m_size = packet.getSize();
		AbilityPacket packet2;
		packet2.deserialize(buffer2);

		packet2.print();
		//delete[] data;
	}

	void ClientGame::sendAbilityPacket(const std::string & p_strAbilityName, ability::AbilityInfoPackage * p_info)
	{
		AbilityPacket packet;
		packet.packetType = ABILITY_PACKET;
		packet.clientId = m_iClientId;
		packet.sourceUnit = getUnitGameObjectIndex(&p_info->m_source->getGameObject());
		packet.addTargetUnits(p_info->m_targets);
		packet.addIntValues(p_info->m_intValue);
		packet.addTargetTiles(p_info->m_targetTilesGO);
		packet.m_abilityNameLength = p_strAbilityName.size();
		packet.m_abilityName = p_strAbilityName;

		char* data = new char[packet.getSize()];
		Buffer buffer;
		buffer.m_data = data;
		buffer.m_size = packet.getSize();
		packet.serialize(buffer);
		printf("[Client: %d] sending ABILITY_PACKET\n", m_iClientId);
		packet.print();

		NetworkServices::sendMessage(m_network->m_connectSocket, data, packet.getSize());
		delete[] data;
	}

	void ClientGame::summonUnit(int p_iClientId, int p_iUnitId, int p_iPosX, int p_iPosY)
	{
		// Create the unit GO and add it to the list
		kitten::K_GameObject* unitGO = unit::UnitSpawn::getInstance()->spawnUnitObject(p_iUnitId);
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

	void ClientGame::sendSummonUnitPacket(int p_iClientId, int p_iUnitId, int p_iPosX, int p_iPosY)
	{
		char data[SUMMON_UNIT_PACKET_SIZE];

		Buffer buffer;
		buffer.m_data = data;
		buffer.m_size = SUMMON_UNIT_PACKET_SIZE;

		SummonUnitPacket packet;
		packet.m_packetType = PacketTypes::SUMMON_UNIT;
		packet.m_clientId = p_iClientId;
		packet.unitId = p_iUnitId;
		packet.posX = p_iPosX;
		packet.posY = p_iPosY;
		
		packet.serialize(buffer);
		NetworkServices::sendMessage(m_network->m_connectSocket, data, SUMMON_UNIT_PACKET_SIZE);
	}

	void ClientGame::sendSkipTurnPacket()
	{
		char data[BASIC_PACKET_SIZE];

		Buffer buffer;
		buffer.m_data = data;
		buffer.m_size = BASIC_PACKET_SIZE;

		Packet packet;
		packet.m_packetType = SKIP_TURN;
		packet.m_clientId = m_iClientId;

		packet.serialize(buffer);
		NetworkServices::sendMessage(m_network->m_connectSocket, data, BASIC_PACKET_SIZE);
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

	kitten::K_GameObject* ClientGame::getUnitGameObject(int p_iIndex)
	{
		auto it = m_unitGOList.find(p_iIndex);
		if (it != m_unitGOList.end())
		{
			return it->second;
		}
		return nullptr;
	}

	void ClientGame::removeUnitGameObject(int p_iUnitIndex)
	{
		auto it = m_unitGOList.find(p_iUnitIndex);
		if (it != m_unitGOList.end())
		{
			m_unitGOList.erase(it);
		}
	}
}