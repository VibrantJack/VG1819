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

		int i = 0;
		PacketTypes packetType;

		while (i < (unsigned int)data_length)
		{
			Buffer defaultBuffer;
			defaultBuffer.m_data = &(m_network_data[i]);
			defaultBuffer.m_size = BASIC_PACKET_SIZE;

			Packet defaultPacket;
			defaultPacket.deserialize(defaultBuffer);

			packetType = (PacketTypes)defaultPacket.m_packetType;
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
				i += MAX_PACKET_SIZE;

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
			case PacketTypes::UNIT_MOVE:
			{
				printf("[Client: %d] received UNIT_MOVE packet from server\n", m_iClientId);

				Buffer buffer;
				buffer.m_data = &(m_network_data[i]);
				buffer.m_size = UNIT_MOVE_PACKET_SIZE;

				UnitMovePacket unitMovePacket;
				unitMovePacket.deserialize(buffer);
				i += UNIT_MOVE_PACKET_SIZE;
				printf("[Client: %d] received Unit index: %d, posX: %d, posY: %d\n", m_iClientId, unitMovePacket.unitIndex, unitMovePacket.posX, unitMovePacket.posY);

				moveUnit(unitMovePacket.unitIndex, unitMovePacket.posX, unitMovePacket.posY);
				break;
			}
			case PacketTypes::MANIPULATE_TILE:
			{
				printf("[Client: %d] received MANIPULATE_TILE packet from server\n", m_iClientId);

				ManipulateTilePacket manipPacket;
				manipPacket.deserialize(&(m_network_data[i]));
				i += MANIPULATE_PACKET_SIZE;
				printf("[Client: %d] received ability name: %s, unit index: %d, posX: %d, posY: %d\n", 
					m_iClientId, manipPacket.abilityName, manipPacket.unitIndex, manipPacket.posX, manipPacket.posY);
				
				manipulateTile(manipPacket.abilityName, manipPacket.unitIndex, manipPacket.posX, manipPacket.posY);
				break;
			}
			case PacketTypes::SOURCE_TARGET_DMG_ABILITY:
			{
				printf("[Client: %d] received SOURCE_TARGET_DMG_ABILITY packet from server\n", m_iClientId);

				SourceTargetDamagePacket stpPacket;
				stpPacket.deserialize(&(m_network_data[i]));
				i += SOURCE_TARGET_DAMAGE_PACKET_SIZE;
				printf("[Client: %d] received ability name: %s, source index: %d, target index: %d, power: %d\n",
					m_iClientId, stpPacket.abilityName, stpPacket.sourceUnitIndex, stpPacket.targetUnitIndex, stpPacket.power);
				
				sourceTargetDamageAbility(stpPacket.abilityName, stpPacket.sourceUnitIndex, stpPacket.targetUnitIndex, stpPacket.power);
				break;
			}
			case PacketTypes::SINGLE_TILE_ABILITY:
			{
				printf("[Client: %d] received SINGLE_TILE_ABILITY packet from server\n", m_iClientId);

				SingleTilePacket stPacket;
				stPacket.deserialize(&(m_network_data[i]));
				i += SINGLE_TILE_PACKET_SIZE;
				printf("[Client: %d] received ability name: %s, posX: %d, posY: %d\n",
					m_iClientId, stPacket.abilityName, stPacket.posX, stPacket.posY);

				singleTileAbility(stPacket.abilityName, stPacket.posX, stPacket.posY);
				break;
			}
			case PacketTypes::SINGLE_TARGET_ABILITY:
			{
				printf("[Client: %d] received SINGLE_TARGET_ABILITY packet from server\n", m_iClientId);

				SingleTargetPacket sTgtPacket;
				sTgtPacket.deserialize(&(m_network_data[i]));
				i += SINGLE_TARGET_PACKET_SIZE;
				printf("[Client: %d] received ability name: %s, source unit: %d, target index: %d, dur: %d, pow: %d\n",
					m_iClientId, sTgtPacket.abilityName, sTgtPacket.sourceUnitIndex, sTgtPacket.targetUnitIndex, sTgtPacket.dur, sTgtPacket.pow);

				singleTargetAbility(sTgtPacket.abilityName, sTgtPacket.sourceUnitIndex, sTgtPacket.targetUnitIndex, sTgtPacket.dur, sTgtPacket.pow);
				break;
			}
			default:
				printf("error in packet types\n");
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
		//strcpy(packet.m_abilityName, p_strAbilityName.c_str());
		packet.m_abilityName = p_strAbilityName;

		char data[MAX_PACKET_SIZE];
		Buffer buffer;
		buffer.m_data = data;
		buffer.m_size = packet.getSize();
		packet.serialize(buffer);
		printf("[Client: %d] sending ABILITY_PACKET\n", m_iClientId);
		packet.print();

		NetworkServices::sendMessage(m_network->m_connectSocket, data, MAX_PACKET_SIZE); // Try buffer.m_size instead of MAX_PACKET_SIZE and see if data gets transferred successfully

		// ****************

		//if (p_strAbilityName == ABILITY_MANIPULATE_TILE)
		//{
		//	TileInfo* tileInfo = p_info->m_targetTilesGO[0]->getComponent<TileInfo>();
		//	int posX = tileInfo->getPosX();
		//	int posY = tileInfo->getPosY();

		//	int unitIndex = getUnitGameObjectIndex(&p_info->m_source->getGameObject());
		//	sendManipulateTilePacket(p_strAbilityName, unitIndex, posX, posY);
		//	//testNewPacket(p_strAbilityName, p_info);
		//}
		//else if (p_strAbilityName == ABILITY_FIGHT || p_strAbilityName == ABILITY_HEAL 
		//	|| p_strAbilityName == ABILITY_SHOOT || p_strAbilityName == ABILITY_SABOTAGE)// These have the same pkg contents
		//{
		//	int sourceUnitIndex = getUnitGameObjectIndex(&p_info->m_source->getGameObject());
		//	int targetUnitIndex = getUnitGameObjectIndex(&p_info->m_targets[0]->getGameObject());
		//	int power = p_info->m_intValue.find(UNIT_POWER)->second;
		//	sendSourceTargetDamagePacket(p_strAbilityName, sourceUnitIndex, targetUnitIndex, power);
		//}
		//else if (p_strAbilityName == ABILITY_BUILD_WALL || p_strAbilityName == ABILITY_SUMMON_UNIT)// These have the same package contents
		//{
		//	TileInfo* tileInfo = p_info->m_targetTilesGO[0]->getComponent<TileInfo>();
		//	int posX = tileInfo->getPosX();
		//	int posY = tileInfo->getPosY();
		//	sendSingleTilePacket(p_strAbilityName, posX, posY);
		//}
		//else if (p_strAbilityName == ABILITY_ENCOURAGE || p_strAbilityName == ABILITY_DODGE)// These have the same package contents
		//{
		//	int sourceUnitIndex = getUnitGameObjectIndex(&p_info->m_source->getGameObject());
		//	int targetUnitIndex = getUnitGameObjectIndex(&p_info->m_targets[0]->getGameObject());
		//	int dur = p_info->m_intValue.find(UNIT_DURATION)->second;
		//	int pow;
		//	auto iter = p_info->m_intValue.find(UNIT_POWER);
		//	if (iter != p_info->m_intValue.end())
		//		pow = iter->second;
		//	else
		//		pow = 0;

		//	sendSingleTargetPacket(p_strAbilityName, sourceUnitIndex, targetUnitIndex, dur, pow);
		//}
	}

	void ClientGame::singleTargetAbility(const std::string &p_strAbilityName, int p_iSourceUnitIndex, int p_iTargetUnitIndex, int p_iDur, int p_iPow)
	{
		// Reconstructing AbilityInfoPackage

		ability::AbilityInfoPackage* pkg = new ability::AbilityInfoPackage();
		pkg->m_source = getUnitGameObject(p_iSourceUnitIndex)->getComponent<unit::Unit>();

		// Getting the target unit; need to push into a vector then assign the new vector to m_targets
		std::vector<unit::Unit*> targets;
		targets.push_back(getUnitGameObject(p_iTargetUnitIndex)->getComponent<unit::Unit>());
		pkg->m_targets = targets;

		// Storing int values
		std::unordered_map<std::string, int> intValues;
		intValues[UNIT_DURATION] = p_iDur;
		intValues[UNIT_POWER] = p_iPow;
		pkg->m_intValue = intValues;

		ability::AbilityManager::getInstance()->findAbility(p_strAbilityName)->effect(pkg);
	}

	void ClientGame::sendSingleTargetPacket(const std::string &p_strAbilityName, int p_iSourceUnitIndex, int p_iTargetUnitIndex, int p_iDur, int p_iPow)
	{
		SingleTargetPacket packet;
		packet.m_packetType = SINGLE_TARGET_ABILITY;
		strcpy(packet.abilityName, p_strAbilityName.c_str());
		packet.sourceUnitIndex = p_iSourceUnitIndex;
		packet.targetUnitIndex = p_iTargetUnitIndex;
		packet.dur = p_iDur;
		packet.pow = p_iPow;

		char data[SINGLE_TARGET_PACKET_SIZE];
		packet.serialize(data);

		NetworkServices::sendMessage(m_network->m_connectSocket, data, SINGLE_TARGET_PACKET_SIZE);
	}

	void ClientGame::singleTileAbility(const std::string &p_strAbilityName, int p_iPosX, int p_iPosY)
	{
		ability::AbilityInfoPackage* pkg = new ability::AbilityInfoPackage();

		std::vector<kitten::K_GameObject*> tiles;
		tiles.push_back(BoardManager::getInstance()->getTile(p_iPosX, p_iPosY));
		pkg->m_targetTilesGO = tiles;

		ability::AbilityManager::getInstance()->findAbility(p_strAbilityName)->effect(pkg);
	}

	void ClientGame::sendSingleTilePacket(const std::string &p_strAbilityName, int p_iPosX, int p_iPosY)
	{
		SingleTilePacket packet;
		packet.m_packetType = SINGLE_TILE_ABILITY;
		strcpy(packet.abilityName, p_strAbilityName.c_str());
		packet.posX = p_iPosX;
		packet.posY = p_iPosY;

		char data[SINGLE_TILE_PACKET_SIZE];
		packet.serialize(data);

		NetworkServices::sendMessage(m_network->m_connectSocket, data, SINGLE_TILE_PACKET_SIZE);
	}

	void ClientGame::sourceTargetDamageAbility(const std::string &p_strAbilityName, int p_iSourceUnitIndex, int p_iTargetUnitIndex, int p_iPower)
	{
		// Reconstructing AbilityInfoPackage

		// Getting the source unit
		ability::AbilityInfoPackage* pkg = new ability::AbilityInfoPackage();
		pkg->m_source = getUnitGameObject(p_iSourceUnitIndex)->getComponent<unit::Unit>();

		// Getting the target unit; need to push into a vector then assign the new vector to m_targets
		std::vector<unit::Unit*> targets;
		targets.push_back(getUnitGameObject(p_iTargetUnitIndex)->getComponent<unit::Unit>());
		pkg->m_targets = targets;

		// Getting the power of the ability; need to assign to map then assign the new map to m_intValue
		std::unordered_map<std::string, int> intValues;
		intValues[UNIT_POWER] = p_iPower;
		pkg->m_intValue = intValues;
		
		ability::AbilityManager::getInstance()->findAbility(p_strAbilityName)->effect(pkg);
	}

	void ClientGame::sendSourceTargetDamagePacket(const std::string &p_strAbilityName, int p_iSourceUnitIndex, int p_iTargetUnitIndex, int p_iPower)
	{
		SourceTargetDamagePacket packet;
		packet.m_packetType = SOURCE_TARGET_DMG_ABILITY;
		strcpy(packet.abilityName, p_strAbilityName.c_str());
		packet.sourceUnitIndex = p_iSourceUnitIndex;
		packet.targetUnitIndex = p_iTargetUnitIndex;
		packet.power = p_iPower;

		char data[SOURCE_TARGET_DAMAGE_PACKET_SIZE];
		packet.serialize(data);

		NetworkServices::sendMessage(m_network->m_connectSocket, data, SOURCE_TARGET_DAMAGE_PACKET_SIZE);
	}

	void ClientGame::manipulateTile(const std::string & p_strAbilityName, int p_iUnitIndex, int p_iPosX, int p_iPosY)
	{
		ability::AbilityInfoPackage* pkg = new ability::AbilityInfoPackage();
		std::vector<kitten::K_GameObject*> tiles;
		tiles.push_back(BoardManager::getInstance()->getTile(p_iPosX, p_iPosY));
		pkg->m_targetTilesGO = tiles;
		pkg->m_source = getUnitGameObject(p_iUnitIndex)->getComponent<unit::Unit>();

		ability::AbilityManager::getInstance()->findAbility(p_strAbilityName)->effect(pkg);
	}

	// p_iUnitIndex: The index of the unit GO that is manipulating the tile
	// p_iPosX, p_iPosX: The x and y position of the tile being manipulated
	void ClientGame::sendManipulateTilePacket(const std::string & p_strAbilityName, int p_iUnitIndex, int p_iPosX, int p_iPosY)
	{
		ManipulateTilePacket packet;
		packet.m_packetType = MANIPULATE_TILE;
		strcpy(packet.abilityName, p_strAbilityName.c_str());
		packet.unitIndex = p_iUnitIndex;
		packet.posX = p_iPosX;
		packet.posY = p_iPosY;

		char data[MANIPULATE_PACKET_SIZE];
		packet.serialize(data);

		NetworkServices::sendMessage(m_network->m_connectSocket, data, MANIPULATE_PACKET_SIZE);
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

	void ClientGame::moveUnit(int p_iUnitIndex, int p_iPosX, int p_iPosY)
	{
		kitten::K_GameObject* targetTile = BoardManager::getInstance()->getTile(p_iPosX, p_iPosY);

		getUnitGameObject(p_iUnitIndex)->getComponent<unit::UnitMove>()->move(targetTile);	
	}

	void ClientGame::sendMovementPacket(int p_iUnitIndex, int p_iPosX, int p_iPosY)
	{
		char data[UNIT_MOVE_PACKET_SIZE];

		Buffer buffer;
		buffer.m_data = data;
		buffer.m_size = UNIT_MOVE_PACKET_SIZE;

		UnitMovePacket packet;
		packet.m_packetType = PacketTypes::UNIT_MOVE;
		packet.m_clientId = m_iClientId;
		packet.unitIndex = p_iUnitIndex;
		packet.posX = p_iPosX;
		packet.posY = p_iPosY;

		packet.serialize(buffer);
		NetworkServices::sendMessage(m_network->m_connectSocket, data, UNIT_MOVE_PACKET_SIZE);
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