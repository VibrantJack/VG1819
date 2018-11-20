#pragma once
#include <string.h>
#include <stdint.h>
#include <assert.h>

#define MAX_PACKET_SIZE 1000000
#define MAX_BUFSIZE 512

enum PacketTypes {

	INIT_CONNECTION = 0,
	SERVER_SHUTDOWN,
	CLIENT_DISCONNECT,
	SEND_CLIENT_ID,
	MANIPULATE_TILE,
	UNIT_MOVE,
	SUMMON_UNIT,
	SOURCE_TARGET_DMG_ABILITY,
	SINGLE_TILE_ABILITY,
	SINGLE_TARGET_ABILITY

};

struct Buffer
{
	char* data;		// pointer to buffer data
	int size;		// size of buffer data in bytes
	int index;		// index of next byte to be read/written
};

struct Packet
{
	void writeInt(Buffer &buffer, uint32_t value)
	{
		assert(buffer.index + sizeof(uint32_t) <= buffer.size);

		*((uint32_t*)(buffer.data + buffer.index)) = value;
		buffer.index += sizeof(uint32_t);
	}

	void writeChar(Buffer &buffer, uint8_t value)
	{

	}

	uint32_t readInt(Buffer &buffer)
	{
		assert(buffer.index + 4 <= buffer.size);

		uint32_t value;
		value = *((uint32_t*)(buffer.data + buffer.index));
		buffer.index += 4;
		return value;
	}
};

struct PacketA : Packet
{
	int x;

	void write(Buffer &buffer)
	{
		writeInt(buffer, this->x);
	}

	void read(Buffer &buffer)
	{
		this->x = readInt(buffer);
	}
};
