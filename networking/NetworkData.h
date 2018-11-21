#pragma once
#include <string.h>

// For ResizablePacket
#include <vector>
#include <unordered_map>
#include "kitten\K_GameObject.h"
#include "unit\Unit.h"

#define MAX_PACKET_SIZE 1000000
#define MAX_CHAR_BUFSIZE 512

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

class Buffer
{
	friend class AbilityPacket;
	friend class Packet;
public:
	char* m_data;		// pointer to buffer data
	int m_size;			// size of buffer data in bytes
	int getIndex() { return m_index; }
private:
	int m_index = 0;	// index of next byte to be read/written
};

// Use to get packet type first, then deserialize into appropriate packet
struct Packet {

	unsigned int m_packetType;
	int m_clientId;

	void writeInt(Buffer& buffer, int value)
	{
		assert(buffer.m_index + sizeof(int) <= buffer.m_size);

		*((int*)(buffer.m_data + buffer.m_index)) = value;
		buffer.m_index += sizeof(int);
	}

	void writeChar(Buffer &buffer, char value)
	{
		assert(buffer.m_index + sizeof(char) <= buffer.m_size);

		*((char*)(buffer.m_data + buffer.m_index)) = value;
		buffer.m_index += sizeof(char);
	}

	int readInt(Buffer& buffer)
	{
		//assert(buffer.m_index + sizeof(int) <= buffer.m_size);

		int value = *((int*)(buffer.m_data + buffer.m_index));
		buffer.m_index += sizeof(int);

		return value;
	}

	char readChar(Buffer &buffer)
	{
		//assert(buffer.m_index + sizeof(char) <= buffer.m_size);

		char value = *((char*)(buffer.m_data + buffer.m_index));
		buffer.m_index += sizeof(char);

		return value;
	}

	void serialize(Buffer& buffer) {
		writeInt(buffer, m_packetType);
		writeInt(buffer, m_clientId);
	}

	void deserialize(Buffer& buffer) {
		m_packetType = readInt(buffer);
		m_clientId = readInt(buffer);
	}
};

struct SummonUnitPacket : Packet
{
	int unitId;
	int posX, posY;

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->m_packetType;		q++;
		*q = this->m_clientId;		q++;

		*q = this->unitId;		q++;
		*q = this->posX;		q++;
		*q = this->posY;		q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->m_packetType = *q;		q++;
		this->m_clientId = *q;		q++;

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
		*q = this->m_packetType;		q++;
		*q = this->m_clientId;		q++;

		*q = this->unitIndex;		q++;
		*q = this->posX;		q++;
		*q = this->posY;		q++;
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->m_packetType = *q;		q++;
		this->m_clientId = *q;		q++;

		this->unitIndex = *q;		q++;
		this->posX = *q;		q++;
		this->posY = *q;		q++;
	}
};

struct ManipulateTilePacket : Packet {

	int unitIndex;
	int posX, posY;
	char abilityName[MAX_CHAR_BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->m_packetType;   q++;
		*q = this->m_clientId;	q++;
		*q = this->unitIndex;	q++;
		*q = this->posX;		q++;
		*q = this->posY;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < MAX_CHAR_BUFSIZE; i++) {
			*p = this->abilityName[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->m_packetType = *q;		q++;
		this->m_clientId = *q;		q++;
		this->unitIndex = *q;		q++;
		this->posX = *q;		q++;
		this->posY = *q;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < MAX_CHAR_BUFSIZE; i++) {
			this->abilityName[i] = *p;
			p++;
		}
	}
};

struct SourceTargetDamagePacket : Packet {

	int sourceUnitIndex;
	int targetUnitIndex;
	int power;
	char abilityName[MAX_CHAR_BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->m_packetType;   q++;
		*q = this->m_clientId;	q++;
		*q = this->sourceUnitIndex;	q++;
		*q = this->targetUnitIndex;		q++;
		*q = this->power;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < MAX_CHAR_BUFSIZE; i++) {
			*p = this->abilityName[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->m_packetType = *q;		q++;
		this->m_clientId = *q;		q++;
		this->sourceUnitIndex = *q;		q++;
		this->targetUnitIndex = *q;		q++;
		this->power = *q;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < MAX_CHAR_BUFSIZE; i++) {
			this->abilityName[i] = *p;
			p++;
		}
	}
};

struct SingleTilePacket : Packet {

	int posX, posY;
	char abilityName[MAX_CHAR_BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->m_packetType;   q++;
		*q = this->m_clientId;	q++;
		*q = this->posX;		q++;
		*q = this->posY;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < MAX_CHAR_BUFSIZE; i++) {
			*p = this->abilityName[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->m_packetType = *q;		q++;
		this->m_clientId = *q;		q++;
		this->posX = *q;		q++;
		this->posY = *q;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < MAX_CHAR_BUFSIZE; i++) {
			this->abilityName[i] = *p;
			p++;
		}
	}
};

struct SingleTargetPacket : Packet {

	int sourceUnitIndex;
	int targetUnitIndex;
	int dur, pow;
	char abilityName[MAX_CHAR_BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->m_packetType;  q++;
		*q = this->m_clientId;	q++;
		*q = this->sourceUnitIndex;		q++;
		*q = this->targetUnitIndex;		q++;
		*q = this->dur;			q++;
		*q = this->pow;			q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < MAX_CHAR_BUFSIZE; i++) {
			*p = this->abilityName[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->m_packetType = *q;	q++;
		this->m_clientId = *q;	q++;
		this->sourceUnitIndex = *q;		q++;
		this->targetUnitIndex = *q;		q++;
		this->dur = *q;			q++;
		this->pow = *q;			q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < MAX_CHAR_BUFSIZE; i++) {
			this->abilityName[i] = *p;
			p++;
		}
	}
};

struct TargetUnitPacket : Packet {

	int targetUnitIndex;
	char abilityName[MAX_CHAR_BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->m_packetType;  q++;
		*q = this->m_clientId;	q++;
		*q = this->targetUnitIndex;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < MAX_CHAR_BUFSIZE; i++) {
			*p = this->abilityName[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->m_packetType = *q;	q++;
		this->m_clientId = *q;	q++;
		this->targetUnitIndex = *q;		q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < MAX_CHAR_BUFSIZE; i++) {
			this->abilityName[i] = *p;
			p++;
		}
	}
};

struct TestPacket : Packet {

	int num;
	char msg[MAX_CHAR_BUFSIZE];

	void serialize(char* data) {
		int *q = (int*)data;
		*q = this->m_packetType;   q++;
		*q = this->m_clientId;	q++;
		*q = this->num;			q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < MAX_CHAR_BUFSIZE; i++) {
			*p = this->msg[i];
			p++;
		}
	}

	void deserialize(char* data) {
		int *q = (int*)data;
		this->m_packetType = *q;		q++;
		this->m_clientId = *q;		q++;
		this->num = *q;				q++;

		char *p = (char*)q;
		int i = 0;
		for (int i = 0; i < MAX_CHAR_BUFSIZE; i++) {
			this->msg[i] = *p;
			p++;
		}
	}
};

class AbilityPacket
{
	typedef std::vector<unit::Unit*> TargetUnits;
	typedef std::unordered_map<std::string, int> IntValues;
	typedef std::vector<kitten::K_GameObject*>  TargetTiles;
public:
	friend struct Buffer;
	int packetType;
	int clientId;
	int sourceUnit;

	int m_abilityNameLength;
	char m_abilityName[MAX_CHAR_BUFSIZE];

	void print();

	void serialize(Buffer& buffer);
	void deserialize(Buffer& buffer);

	void addTargetUnits(TargetUnits p_targets);
	void addIntValues(IntValues p_values);
	void addTargetTiles(TargetTiles p_targetTilesGO);
	int getSize();

private:	
	int sumKeysLength = 0;

	int m_numTargetUnits;
	TargetUnits m_targets;

	int m_numIntValues;
	IntValues m_intValue;

	int m_numTargetTiles;
	TargetTiles m_targetTilesGO;

	void writeInt(Buffer &buffer, int value);
	void writeChar(Buffer &buffer, char value);
	int readInt(Buffer &buffer);
	char readChar(Buffer &buffer);
	
};
