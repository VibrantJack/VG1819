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
#include "kitten\K_GameObject.h"
#include "unit\UnitSpawn.h"
#include "unit\unitComponent\UnitMove.h"
#include "unit\UnitMonitor.h"

namespace networking
{
	ClientGame* ClientGame::sm_clientGameInstance = nullptr;

	// Creates the singleton instance.
	void ClientGame::createInstance()
	{
		assert(sm_clientGameInstance == nullptr);
		sm_clientGameInstance = new ClientGame();
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
		assert(sm_clientGameInstance);
		return sm_clientGameInstance;
	}

	ClientGame::ClientGame()
	{

		m_network = new ClientNetwork();

		{ // Client connects and sends INIT_CONNECTION packet; maybe move this into ClientServer class
			const unsigned int packet_size = sizeof(Packet);
			char packet_data[packet_size];

			Packet packet;
			packet.packetType = INIT_CONNECTION;
			packet.serialize(packet_data);
			NetworkServices::sendMessage(m_network->m_connectSocket, packet_data, packet_size);
		}
	}


	ClientGame::~ClientGame()
	{
		delete m_network;
	}

	void ClientGame::sendPacket(Packet p_packet)
	{
		switch (p_packet.packetType)
		{
			case PacketTypes::CLIENT_SUMMON_UNIT :
			{
				const unsigned int packetSize = sizeof(Packet);
				char data[packetSize];
				NetworkServices::serializePacketTest(p_packet, data);
				NetworkServices::sendMessage(m_network->m_connectSocket, data, packetSize);
			}
		}
		//char* packet_data = NetworkServices::serializePacket(p_packet);
		//NetworkServices::sendMessage(m_network->m_connectSocket, data, packetSize);

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
		unsigned int clientId;

		while (i < (unsigned int)data_length)
		{
			packet.deserialize(&(m_network_data[i]));
			packetType = (PacketTypes)packet.packetType;
			clientId = packet.clientId;

			switch (packetType) {

			case PacketTypes::SEND_CLIENT_ID:
				Packet packet;
				packet.deserialize(&(m_network_data[i]));
				i += sizeof(Packet);

				m_iClientId = packet.clientId;
				printf("Client ID: %d\n", m_iClientId);

				break;
			case PacketTypes::CLIENT_SUMMON_UNIT:
				printf("\nclient received CLIENT_SUMMON_UNIT packet from server\n");

				SummonUnitPacket summonUnitPacket;
				summonUnitPacket.deserialize(&(m_network_data[i]));
				i += sizeof(SummonUnitPacket);
				
				// Call function here that summons a unit
				summonUnit(summonUnitPacket);
				break;

			default:
				printf("\nerror in packet types\n");
				break;
			}
		}
	}

	void ClientGame::summonUnit(SummonUnitPacket p_packet)
	{
		kitten::K_GameObject* testDummyGO = unit::UnitSpawn::getInstance()->spawnUnitObject(kibble::getUnitFromId(p_packet.unitId));
		unit::Unit* testDummy = testDummyGO->getComponent<unit::Unit>();
		unit::UnitMonitor::getInstanceSafe()->printUnit(testDummy);

		//initialize position
		testDummyGO->getComponent<unit::UnitMove>()->setTile(p_packet.posX, p_packet.posY);
	}

	// Testing functions below
	void ClientGame::sendActionPackets()
	{
		// send action packet
		const unsigned int packet_size = sizeof(Packet);
		char packet_data[packet_size];

		Packet packet;
		packet.packetType = ACTION_EVENT;

		packet.serialize(packet_data);

		NetworkServices::sendMessage(m_network->m_connectSocket, packet_data, packet_size);
	}

	void ClientGame::storeStartingData(StartingDataPacket packet) {
		printf("PacketType: %d\n", packet.packetType);
		printf("Starting Unit ID: %d\n", packet.unit_id1);
		printf("Starting Unit ID: %d\n", packet.unit_id2);
		printf("Starting Unit ID: %d\n", packet.unit_id3);
		printf("Enemy Commander ID: %d\n", packet.commander_id);
	}

	void ClientGame::receiveInitiativePacket(InitiativeDataPacket packet) {
		printf("PacketType: %d\n", packet.packetType);
		printf("First Unit ID: %d\n", packet.unit_id1);
		printf("Second Unit ID: %d\n", packet.unit_id2);
		printf("Third Unit ID: %d\n", packet.unit_id3);
	}

	void ClientGame::receiveStartTurnPacket(StartTurnPacket packet) {
		printf("PacketType: %d\n", packet.packetType);
		printf("Active Unit ID: %d\n", packet.unit_id);
	}

	void ClientGame::manipulateTile() {
		int iTile_id;
		printf("Enter Tile ID: ");
		std::cin >> iTile_id;

		const unsigned int packet_size = sizeof(ClientManipulateTile);
		char packet_data[packet_size];

		ClientManipulateTile packet;
		packet.packetType = CLIENT_MANIPULATE_TILE;
		packet.tile_id = iTile_id;
		packet.serialize(packet_data);
		NetworkServices::sendMessage(m_network->m_connectSocket, packet_data, packet_size);
	}

	void ClientGame::receiveManipulatedTilePacket(ClientManipulateTile packet) {
		printf("PacketType: %d\n", packet.packetType);
		printf("Manipulated Tile ID: %d\n", packet.tile_id);
	}
}