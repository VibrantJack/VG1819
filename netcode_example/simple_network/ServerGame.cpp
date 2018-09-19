/*
* ServerGame
* The "Server" that handles game data and updates connected
* clients
*/
#include "ServerGame.h"

unsigned int ServerGame::client_id; 

ServerGame::ServerGame(void)
{
    // id's to assign clients for our table
    client_id = 0;

    // set up the server network to listen 
    network = new ServerNetwork(); 
}

ServerGame::~ServerGame(void)
{
}

void ServerGame::update()
{
    // get new clients
   if(network->acceptNewClient(client_id))
   {
        printf("client %d has been connected to the server\n",client_id);

        client_id++;
   } else {
	   //printf("No clients connecting\n");
   }

   receiveFromClients();
}

void ServerGame::receiveFromClients()
{

    Packet packet;

    // go through all clients to see if they are trying to send data
    std::map<unsigned int, SOCKET>::iterator iter;

    for(iter = network->sessions.begin(); iter != network->sessions.end(); iter++)
    {
        int data_length = network->receiveData(iter->first, network_data);

        if (data_length <= 0) 
        {
            //no data recieved
            continue;
        }

        int i = 0;
        while (i < (unsigned int)data_length) 
        {
            packet.deserialize(&(network_data[i]));

            switch (packet.packet_type) {

                case INIT_CONNECTION:
					i += sizeof(Packet);
                    printf("\nserver received init packet from client %d\n", iter->first);
                    break;

                case CLIENT_ARMY_DATA:
					ClientArmyPacket armyPacket;
					armyPacket.deserialize(&(network_data[i]));
					i += sizeof(ClientArmyPacket);
					m_iArmyData++;

                    printf("\nserver received client army data packet from %d\n", iter->first);
					// Store army data according to the appropriate client ID (iter->first)
					storeArmyData(armyPacket, iter->first);

					// Should store army data for both players before sending out starting
					// hand data and opposing player's starting Commander data
					if (m_iArmyData == 2) {
						sendStartingDataPackets();
						sendInitiativePackets();
					}
					// Calling these methods immediately for testing on a single machine
					sendStartingDataPackets();
					sendInitiativePackets();
					sendStartTurnPacket();
                    break;

				case CLIENT_MANIPULATE_TILE:
					ClientManipulateTile manipulateTile;
					manipulateTile.deserialize(&(network_data[i]));
					i += sizeof(ClientManipulateTile);
					printf("\nserver received client manipulate tile packet from client %d\n", iter->first);
					printf("Client: %d is manipulating tile id: %d\n", iter->first, manipulateTile.tile_id);

					// Now send the manipulated tile data to all other clients
					sendManipulateTilePacket(manipulateTile);
					break;

                default:
                    printf("error in packet types received from client %d\n", iter->first);
                    break;
            }
        }
    }
}

void ServerGame::storeArmyData(ClientArmyPacket packet, int p_iClient) {
	if (!m_bClient1DataStored) {
		m_bClient1DataStored = true;
		client1Data.client_id = p_iClient;
		client1Data.unit1 = packet.unit_id1;
		client1Data.unit2 = packet.unit_id2;
		client1Data.unit3 = packet.unit_id3;
		client1Data.unit4 = packet.unit_id4;
		client1Data.unit5 = packet.unit_id5;
		client1Data.unit6 = packet.unit_id6;

		printf("Client ID: %d\n", client1Data.client_id);
		printf("Unit ID: %d\n", client1Data.unit1);
		printf("Unit ID: %d\n", client1Data.unit2);
		printf("Unit ID: %d\n", client1Data.unit3);
		printf("Unit ID: %d\n", client1Data.unit4);
		printf("Unit ID: %d\n", client1Data.unit5);
		printf("Unit ID: %d\n", client1Data.unit6);
	} else if (!m_bClient2DataStored) {
		m_bClient2DataStored = true;
		client2Data.client_id = p_iClient;
		client2Data.unit1 = packet.unit_id1;
		client2Data.unit2 = packet.unit_id2;
		client2Data.unit3 = packet.unit_id3;
		client2Data.unit4 = packet.unit_id4;
		client2Data.unit5 = packet.unit_id5;
		client2Data.unit6 = packet.unit_id6;

		printf("Client ID: %d\n", client2Data.client_id);
		printf("Unit ID: %d\n", client2Data.unit1);
		printf("Unit ID: %d\n", client2Data.unit2);
		printf("Unit ID: %d\n", client2Data.unit3);
		printf("Unit ID: %d\n", client2Data.unit4);
		printf("Unit ID: %d\n", client2Data.unit5);
		printf("Unit ID: %d\n", client2Data.unit6);
	} else {
		printf("Army data already stored for client: %d and client: %d\n", client1Data.client_id, client2Data.client_id);
	}
}

void ServerGame::sendActionPackets()
{
    // send action packet
    const unsigned int packet_size = sizeof(Packet);
    char packet_data[packet_size];

    Packet packet;
    packet.packet_type = ACTION_EVENT;

    packet.serialize(packet_data);

    network->sendToAll(packet_data,packet_size);
}

void ServerGame::sendStartingDataPackets()
{
	// send starting data packets
	const unsigned int packet_size = sizeof(StartingDataPacket);
	char packet_data[packet_size];

	StartingDataPacket packet;
	packet.packet_type = STARTING_DATA;
	packet.commander_id = 11;
	packet.unit_id1 = 111;
	packet.unit_id2 = 112;
	packet.unit_id3 = 113;

	packet.serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}

void ServerGame::sendInitiativePackets()
{
	// send initiative data packets
	const unsigned int packet_size = sizeof(InitiativeDataPacket);
	char packet_data[packet_size];

	InitiativeDataPacket packet;
	packet.packet_type = INITIATIVE_DATA;
	packet.unit_id1 = 101;
	packet.unit_id2 = 102;
	packet.unit_id3 = 102;

	packet.serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}

void ServerGame::sendStartTurnPacket()
{
	// send starting turn unit data packet
	const unsigned int packet_size = sizeof(StartTurnPacket);
	char packet_data[packet_size];

	StartTurnPacket packet;
	packet.packet_type = UNIT_START_TURN;
	packet.unit_id = 1001;

	packet.serialize(packet_data);

	// Here we would need to get the client id mapped to the unit id
	// For testing purposes, sending to the first client, should be 0
	network->sendtoClient(0, packet_data, packet_size);
}

void ServerGame::sendManipulateTilePacket(ClientManipulateTile packet) {
	// send manipulated tile data packets
	const unsigned int packet_size = sizeof(ClientManipulateTile);
	char packet_data[packet_size];

	packet.serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}