/*
 * ClientGame
 * The "Game" that the client player uses to interact
 * with the host
*/
#include "ClientGame.h"
#include <iostream>

ClientGame::ClientGame(void)
{

    network = new ClientNetwork();

	{ // Client connects and sends INIT_CONNECTION packet; maybe move this into ClientServer class
		const unsigned int packet_size = sizeof(Packet);
		char packet_data[packet_size];

		Packet packet;
		packet.packet_type = INIT_CONNECTION;
		packet.serialize(packet_data);
		NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
	}

	{ // After connecting, send army data to server
		ClientArmyPacket armyPacket;
		armyPacket.packet_type = CLIENT_ARMY_DATA;
		armyPacket.unit_id1 = 1;
		armyPacket.unit_id2 = 2;
		armyPacket.unit_id3 = 3;
		armyPacket.unit_id4 = 4;
		armyPacket.unit_id5 = 5;
		armyPacket.unit_id6 = 6;

		const unsigned int armyPacket_size = sizeof(ClientArmyPacket);
		char armyPacket_data[armyPacket_size];
		armyPacket.serialize(armyPacket_data);
		NetworkServices::sendMessage(network->ConnectSocket, armyPacket_data, armyPacket_size);
	}
}


ClientGame::~ClientGame(void)
{
	delete network;
}

void ClientGame::sendActionPackets()
{
    // send action packet
    const unsigned int packet_size = sizeof(Packet);
    char packet_data[packet_size];

    Packet packet;
    packet.packet_type = ACTION_EVENT;

    packet.serialize(packet_data);

    NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientGame::storeStartingData(StartingDataPacket packet) {
	printf("PacketType: %d\n", packet.packet_type);
	printf("Starting Unit ID: %d\n", packet.unit_id1);
	printf("Starting Unit ID: %d\n", packet.unit_id2);
	printf("Starting Unit ID: %d\n", packet.unit_id3);
	printf("Enemy Commander ID: %d\n", packet.commander_id);
}

void ClientGame::receiveInitiativePacket(InitiativeDataPacket packet) {
	printf("PacketType: %d\n", packet.packet_type);
	printf("First Unit ID: %d\n", packet.unit_id1);
	printf("Second Unit ID: %d\n", packet.unit_id2);
	printf("Third Unit ID: %d\n", packet.unit_id3);
}

void ClientGame::receiveStartTurnPacket(StartTurnPacket packet) {
	printf("PacketType: %d\n", packet.packet_type);
	printf("Active Unit ID: %d\n", packet.unit_id);
}

void ClientGame::manipulateTile() {
	int iTile_id;
	printf("Enter Tile ID: ");
	std::cin >> iTile_id;

	const unsigned int packet_size = sizeof(ClientManipulateTile);
	char packet_data[packet_size];

	ClientManipulateTile packet;
	packet.packet_type = CLIENT_MANIPULATE_TILE;
	packet.tile_id = iTile_id;
	packet.serialize(packet_data);
	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientGame::receiveManipulatedTilePacket(ClientManipulateTile packet) {
	printf("PacketType: %d\n", packet.packet_type);
	printf("Manipulated Tile ID: %d\n", packet.tile_id);
}

void ClientGame::update()
{
    Packet packet;
    int data_length = network->receivePackets(network_data);

    if (data_length <= 0) 
    {
        //no data recieved
        return;
    }

    int i = 0;
    while (i < (unsigned int)data_length) 
    {
        packet.deserialize(&(network_data[i]));

        switch (packet.packet_type) {

            case ACTION_EVENT:
				i += sizeof(Packet);
                printf("\nclient received action event packet from server\n");
                break;

			case STARTING_DATA:
				printf("\nclient received starting data packet from server\n");
				StartingDataPacket startingData;
				startingData.deserialize(&(network_data[i]));
				i += sizeof(StartingDataPacket);
				storeStartingData(startingData);
				break;

			case INITIATIVE_DATA:
				printf("\nclient received initiative data packet from server\n");
				InitiativeDataPacket initiativeData;
				initiativeData.deserialize(&(network_data[i]));
				i += sizeof(InitiativeDataPacket);
				receiveInitiativePacket(initiativeData);
				break;

			case UNIT_START_TURN:
				printf("\nclient received unit start turn data packet from server\n");
				StartTurnPacket startTurnData;
				startTurnData.deserialize(&(network_data[i]));
				i += sizeof(StartTurnPacket);
				receiveStartTurnPacket(startTurnData);
				manipulateTile();
				break;

			case CLIENT_MANIPULATE_TILE:
				printf("\nclient received manipulated tile data packet from server\n");
				ClientManipulateTile manipulatedTile;
				manipulatedTile.deserialize(&(network_data[i]));
				i += sizeof(ClientManipulateTile);
				receiveManipulatedTilePacket(manipulatedTile);
				break;

            default:
                printf("\nerror in packet types\n");
                break;
        }
    }
}
