#include "ServerGame.h"
#include "ClientGame.h"
// used for multi-threading
#include <process.h>

void serverLoop(void *);
void clientLoop(void);

void serialize(TestPacket* packet, char* data);
void deserialize(char* data, TestPacket* packet);
void printMsg(Packet* packet);

ServerGame * server;
ClientGame * client;

int main()
{
	// initialize the server
	server = new ServerGame();

	// run the server on a thread to test on one machine
    _beginthread( serverLoop, 0, (void*)12);
	//serverLoop((void*)12);

    // initialize the client 
    client = new ClientGame();
	clientLoop();

	// Testing serialization and deserialization of packets
	{
		ClientManipulateTile packet;
		packet.packet_type = CLIENT_MANIPULATE_TILE;
		packet.tile_id = 11111;

		char data[TEST_PACKET_SIZE];
		packet.serialize(data);

		Packet packetType;
		packetType.deserialize(data);

		switch (packetType.packet_type) {

			case INIT_CONNECTION: {
				TestPacket temp;
				temp.deserialize(data);
				printMsg(&temp);
				break;
			}
			case CLIENT_ARMY_DATA: {
				ClientArmyPacket temp;
				temp.deserialize(data);
				printMsg(&temp);
				break;
			}
			case STARTING_DATA: {
				StartingDataPacket temp;
				temp.deserialize(data);
				printMsg(&temp);
				break;
			}
			case INITIATIVE_DATA: {
				InitiativeDataPacket temp;
				temp.deserialize(data);
				printMsg(&temp);
				break;
			}
			case UNIT_START_TURN: {
				StartTurnPacket temp;
				temp.deserialize(data);
				printMsg(&temp);
				break;
			}
			case CLIENT_MANIPULATE_TILE: {
				StartTurnPacket temp;
				temp.deserialize(data);
				printMsg(&temp);
				break;
			}
		}
	}
	// End testing serialization and deserialization of packets

	return 0;
}

void serverLoop(void * arg) 
{ 
    while(true) 
    {
        server->update();
    }
}

void clientLoop()
{
    while(true)
    {
        //do game stuff
        client->update();
    }
}


// Print function to test if deserialization functions are working
void printMsg(Packet* packet) {

	switch (packet->packet_type) {

		case INIT_CONNECTION: {
			TestPacket* p = static_cast<TestPacket*>(packet);
			printf("Packet Num: %d\n", p->num);
			printf("Packet Msg: %s\n", p->msg);
			break;
		}
		case CLIENT_ARMY_DATA: {
			ClientArmyPacket* p = static_cast<ClientArmyPacket*>(packet);
			printf("PacketType: %d\n", p->packet_type);
			printf("Unit ID: %d\n", p->unit_id1);
			printf("Unit ID: %d\n", p->unit_id2);
			printf("Unit ID: %d\n", p->unit_id3);
			printf("Unit ID: %d\n", p->unit_id4);
			printf("Unit ID: %d\n", p->unit_id5);
			printf("Unit ID: %d\n", p->unit_id6);
			break;
		}
		case STARTING_DATA: {
			StartingDataPacket* p = static_cast<StartingDataPacket*>(packet);
			printf("PacketType: %d\n", p->packet_type);
			printf("Unit ID: %d\n", p->unit_id1);
			printf("Unit ID: %d\n", p->unit_id2);
			printf("Unit ID: %d\n", p->unit_id3);
			printf("X Pos: %d\n", p->x);
			printf("Y Pos: %d\n", p->y);
			printf("Commander ID: %d\n", p->commander_id);
			break;
		}
		case INITIATIVE_DATA: {
			InitiativeDataPacket* p = static_cast<InitiativeDataPacket*>(packet);
			printf("PacketType: %d\n", p->packet_type);
			printf("Going first: %d\n", p->unit_id1);
			printf("Going second: %d\n", p->unit_id2);
			printf("Going third: %d\n", p->unit_id3);
			break;
		}
		case UNIT_START_TURN: {
			StartTurnPacket* p = static_cast<StartTurnPacket*>(packet);
			printf("PacketType: %d\n", p->packet_type);
			printf("Starting unit: %d\n", p->unit_id);
			break;
		}
		case CLIENT_MANIPULATE_TILE: {
			ClientManipulateTile* p = static_cast<ClientManipulateTile*>(packet);
			printf("PacketType: %d\n", p->packet_type);
			printf("Target Tile ID: %d\n", p->tile_id);
			break;
		}
	}
}