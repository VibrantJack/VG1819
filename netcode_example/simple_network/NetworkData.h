#pragma once
#include <string.h>

#define MAX_PACKET_SIZE 1000000
#define TEST_PACKET_SIZE sizeof(TestPacket)
#define BUFSIZE 512

enum PacketTypes {

    INIT_CONNECTION = 0,
	CLIENT_ARMY_DATA,
	STARTING_DATA,
	INITIATIVE_DATA,
	UNIT_START_TURN,
	UNIT_END_TURN,
	CLIENT_MANIPULATE_TILE,
	SERVER_MANIPULATE_TILE,
	CLIENT_UNIT_MOVE,
	SERVER_UNIT_MOVE,
	UNIT_ATTACK,
	UPDATE_UNIT_STATUS,
	UNIT_DEATH,
	CLIENT_SUMMON_UNIT,
	SERVER_SUMMON_UNIT,
    ACTION_EVENT,

};

//struct Packet {
//
//    unsigned int packet_type;
//
//    void serialize(char * data) {
//        memcpy(data, this, sizeof(Packet));
//    }
//
//    void deserialize(char * data) {
//        memcpy(this, data, sizeof(Packet));
//    }
//};

// Use to get packet type first, then deserialize into appropriate packet
struct Packet {

	unsigned int packet_type;


	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packet_type;		q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packet_type = *q;		q++;
	}
};


struct TestPacket : Packet {

	int num;
	char msg[BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packet_type;   q++;
		*q = this->num;			q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			*p = this->msg[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packet_type = *q;		q++;
		this->num = *q;				q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			this->msg[i] = *p;
			p++;
		}
	}
};

struct ClientArmyPacket : Packet {

	int unit_id1, unit_id2, unit_id3,
		unit_id4, unit_id5, unit_id6;

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packet_type;   q++;
		*q = this->unit_id1;	  q++;
		*q = this->unit_id2;	  q++;
		*q = this->unit_id3;	  q++;
		*q = this->unit_id4;	  q++;
		*q = this->unit_id5;	  q++;
		*q = this->unit_id6;	  q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packet_type = *q;		q++;
		this->unit_id1 = *q;		q++;
		this->unit_id2 = *q;		q++;
		this->unit_id3 = *q;		q++;
		this->unit_id4 = *q;		q++;
		this->unit_id5 = *q;		q++;
		this->unit_id6 = *q;		q++;
	}
};

struct StartingDataPacket : Packet {

	int unit_id1, unit_id2, unit_id3;
	int x, y;
	// Opposing player commander id
	int commander_id;

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packet_type;   q++;
		*q = this->unit_id1;	  q++;
		*q = this->unit_id2;	  q++;
		*q = this->unit_id3;	  q++;
		*q = this->x;			  q++;
		*q = this->y;			  q++;
		*q = this->commander_id;  q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packet_type = *q;		q++;
		this->unit_id1 = *q;		q++;
		this->unit_id2 = *q;		q++;
		this->unit_id3 = *q;		q++;
		this->x = *q;				q++;
		this->y = *q;				q++;
		this->commander_id = *q;	q++;
	}
};

struct InitiativeDataPacket : Packet {

	int unit_id1, unit_id2, unit_id3;

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packet_type;   q++;
		*q = this->unit_id1;	  q++;
		*q = this->unit_id2;	  q++;
		*q = this->unit_id3;	  q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packet_type = *q;		q++;
		this->unit_id1 = *q;		q++;
		this->unit_id2 = *q;		q++;
		this->unit_id3 = *q;		q++;
	}
};

struct StartTurnPacket : Packet {

	int unit_id;

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packet_type;   q++;
		*q = this->unit_id;	  q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packet_type = *q;		q++;
		this->unit_id = *q;		q++;
	}
};

struct ClientManipulateTile : Packet {

	int tile_id;

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packet_type;   q++;
		*q = this->tile_id;		  q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packet_type = *q;		q++;
		this->tile_id = *q;			q++;
	}
};