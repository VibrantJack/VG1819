#pragma once
#include <string.h>

// For ResizablePacket
#include <vector>
#include <unordered_map>
#include "kitten\K_GameObject.h"
#include "unit\Unit.h"

#define MAX_PACKET_SIZE 1000000
#define BUFSIZE 512

#define BASIC_PACKET_SIZE sizeof(Packet)
#define SUMMON_UNIT_PACKET_SIZE sizeof(SummonUnitPacket)
#define UNIT_MOVE_PACKET_SIZE sizeof(UnitMovePacket)
#define TEST_PACKET_SIZE sizeof(TestPacket)
#define MANIPULATE_PACKET_SIZE sizeof(ManipulateTilePacket)
#define SOURCE_TARGET_DAMAGE_PACKET_SIZE sizeof(SourceTargetDamagePacket)
#define SINGLE_TILE_PACKET_SIZE sizeof(SingleTilePacket)
#define SINGLE_TARGET_PACKET_SIZE sizeof(SingleTargetPacket)

enum PacketTypes {

	INIT_CONNECTION = 0,
	SERVER_SHUTDOWN,
	CLIENT_DISCONNECT,
	SEND_CLIENT_ID,
	ABILITY_PACKET,
	MANIPULATE_TILE,
	UNIT_MOVE,
	SUMMON_UNIT,
	SOURCE_TARGET_DMG_ABILITY,
	SINGLE_TILE_ABILITY,
	SINGLE_TARGET_ABILITY

};

// Use to get packet type first, then deserialize into appropriate packet
struct Packet {

	unsigned int packetType;
	int clientId;


	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;		q++;
		*q = this->clientId;		q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packetType = *q;		q++;
		this->clientId = *q;		q++;
	}
};

struct SummonUnitPacket : Packet
{
	int unitId;
	int posX, posY;

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;		q++;
		*q = this->clientId;		q++;

		*q = this->unitId;		q++;
		*q = this->posX;		q++;
		*q = this->posY;		q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packetType = *q;		q++;
		this->clientId = *q;		q++;

		this->unitId = *q;		q++;
		this->posX = *q;		q++;
		this->posY = *q;		q++;
	}
};

struct UnitMovePacket : Packet 
{
	int unitIndex;
	int posX, posY;


	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;		q++;
		*q = this->clientId;		q++;

		*q = this->unitIndex;		q++;
		*q = this->posX;		q++;
		*q = this->posY;		q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packetType = *q;		q++;
		this->clientId = *q;		q++;

		this->unitIndex = *q;		q++;
		this->posX = *q;		q++;
		this->posY = *q;		q++;
	}
};

struct ManipulateTilePacket : Packet {

	int unitIndex;
	int posX, posY;
	char abilityName[BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;   q++;
		*q = this->clientId;	q++;
		*q = this->unitIndex;	q++;
		*q = this->posX;		q++;
		*q = this->posY;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			*p = this->abilityName[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packetType = *q;		q++;
		this->clientId = *q;		q++;
		this->unitIndex = *q;		q++;
		this->posX = *q;		q++;
		this->posY = *q;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			this->abilityName[i] = *p;
			p++;
		}
	}
};

struct SourceTargetDamagePacket : Packet {

	int sourceUnitIndex;
	int targetUnitIndex;
	int power;
	char abilityName[BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;   q++;
		*q = this->clientId;	q++;
		*q = this->sourceUnitIndex;	q++;
		*q = this->targetUnitIndex;		q++;
		*q = this->power;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			*p = this->abilityName[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packetType = *q;		q++;
		this->clientId = *q;		q++;
		this->sourceUnitIndex = *q;		q++;
		this->targetUnitIndex = *q;		q++;
		this->power = *q;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			this->abilityName[i] = *p;
			p++;
		}
	}
};

struct SingleTilePacket : Packet {

	int posX, posY;
	char abilityName[BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;   q++;
		*q = this->clientId;	q++;
		*q = this->posX;		q++;
		*q = this->posY;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			*p = this->abilityName[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packetType = *q;		q++;
		this->clientId = *q;		q++;
		this->posX = *q;		q++;
		this->posY = *q;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			this->abilityName[i] = *p;
			p++;
		}
	}
};

struct SingleTargetPacket : Packet {

	int sourceUnitIndex;
	int targetUnitIndex;
	int dur, pow;
	char abilityName[BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;  q++;
		*q = this->clientId;	q++;
		*q = this->sourceUnitIndex;		q++;
		*q = this->targetUnitIndex;		q++;
		*q = this->dur;			q++;
		*q = this->pow;			q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			*p = this->abilityName[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packetType = *q;	q++;
		this->clientId = *q;	q++;
		this->sourceUnitIndex = *q;		q++;
		this->targetUnitIndex = *q;		q++;
		this->dur = *q;			q++;
		this->pow = *q;			q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			this->abilityName[i] = *p;
			p++;
		}
	}
};

struct AbilityPacket : Packet {

	int sourceUnitIndex;
	char abilityName[BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;  q++;
		*q = this->clientId;	q++;
		*q = this->sourceUnitIndex;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			*p = this->abilityName[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packetType = *q;	q++;
		this->clientId = *q;	q++;
		this->sourceUnitIndex = *q;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			this->abilityName[i] = *p;
			p++;
		}
	}
};

struct TargetUnitPacket : Packet {

	int targetUnitIndex;
	char abilityName[BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;  q++;
		*q = this->clientId;	q++;
		*q = this->targetUnitIndex;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			*p = this->abilityName[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packetType = *q;	q++;
		this->clientId = *q;	q++;
		this->targetUnitIndex = *q;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			this->abilityName[i] = *p;
			p++;
		}
	}
};

struct TestPacket : Packet {

	int num;
	char msg[BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;   q++;
		*q = this->clientId;	q++;
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
		this->packetType = *q;		q++;
		this->clientId = *q;		q++;
		this->num = *q;				q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < BUFSIZE; i++) {
			this->msg[i] = *p;
			p++;
		}
	}
};
struct Buffer
{
	friend class ResizeablePacket;

	char* m_data;		// pointer to buffer data
	int m_size;			// size of buffer data in bytes
	int getIndex() { return m_index; }
//private:
	int m_index = 0;	// index of next byte to be read/written
};
class ResizeablePacket
{
	typedef std::vector<unit::Unit*> TargetUnits;
	typedef std::unordered_map<std::string, int> IntValues;
	typedef std::vector<kitten::K_GameObject*>  TargetTiles;
public:
	int packetType;
	int clientId;
	int sourceUnit;

	int m_numTargetUnits;
	TargetUnits m_targets;

	int m_numIntValues;
	IntValues m_intValue;

	int m_numTargetTiles;
	TargetTiles m_targetTilesGO;

	int m_abilityNameLength;
	char m_abilityName[BUFSIZE];

	void print(ResizeablePacket& packet);

	void serialize(Buffer& buffer);
	void deserialize(Buffer& buffer);

	int getSize();

	/*void addTargetUnits(std::vector<unit::Unit*> p_targets);
	void addIntValues(IntValues p_values);
	void addTargetTiles(std::vector<kitten::K_GameObject*> p_targetTilesGO);*/

private:
	

	void writeInt(Buffer &buffer, int value);
	void writeChar(Buffer &buffer, char value);
	int readInt(Buffer &buffer);
	char readChar(Buffer &buffer);
	
};

struct AbilityInfoPacket : Packet
{
	int sourceUnit;
	int m_numTargetUnits;
	int m_numIntValues;
	int m_numTargetTiles;

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;	q++;
		*q = this->clientId;	q++;
		*q = this->sourceUnit;		q++;
		*q = this->m_numTargetUnits;	q++;
		*q = this->m_numIntValues;		q++;
		*q = this->m_numTargetTiles;	q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packetType = *q;		q++;
		this->clientId = *q;		q++;
		this->sourceUnit = *q;		q++;
		this->m_numTargetUnits = *q;	q++;
		this->m_numIntValues = *q;		q++;
		this->m_numTargetTiles = *q;	q++;
	}
};

struct TargetUnitPacketTest : Packet
{
	int targetUnitIndex;

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;	q++;
		*q = this->clientId;	q++;
		*q = this->targetUnitIndex;		q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packetType = *q;		q++;
		this->clientId = *q;		q++;
		this->targetUnitIndex = *q;		q++;
	}
};

struct IntValuePacket : Packet
{
	int value;
	int keyLength;
	char key[BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->value;		q++;
		*q = this->keyLength;	q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < keyLength; i++) {
			*p = this->key[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->value = *q;		q++;
		this->keyLength = *q;	q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < keyLength; i++) {
			this->key[i] = *p;
			p++;
		}
	}
};

struct TargetTilePacket : Packet
{
	int posX;
	int posY;

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->packetType;	q++;
		*q = this->clientId;	q++;
		*q = this->posX;		q++;
		*q = this->posY;		q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->packetType = *q;		q++;
		this->clientId = *q;		q++;
		this->posX = *q;		q++;
		this->posY = *q;		q++;
	}
};
