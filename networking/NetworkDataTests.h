//#pragma once
//#include <string.h>
//#include <stdint.h>
//#include <assert.h>
//#include <vector>
//
//#define MAX_PACKET_SIZE 1000000
//#define MAX_BUFSIZE 512
//
//enum PacketTypes2 {
//
//	INIT_CONNECTION = 0,
//	SERVER_SHUTDOWN,
//	CLIENT_DISCONNECT,
//	SEND_CLIENT_ID,
//	MANIPULATE_TILE,
//	UNIT_MOVE,
//	SUMMON_UNIT,
//	SOURCE_TARGET_DMG_ABILITY,
//	SINGLE_TILE_ABILITY,
//	SINGLE_TARGET_ABILITY
//
//};
//
//struct Buffer2
//{
//	friend struct Packet;
//	char* m_data;		// pointer to buffer data
//	int m_size;		// size of buffer data in bytes
//	int getIndex() { return m_index; }
//private:
//	int m_index = 0;		// index of next byte to be read/written
//};
//
//struct Packet2
//{
//	void writeInt(Buffer &buffer, uint32_t value)
//	{
//		assert(buffer.m_index + sizeof(uint32_t) <= buffer.m_size);
//
//		*((uint32_t*)(buffer.m_data + buffer.m_index)) = value;
//		buffer.m_index += sizeof(uint32_t);
//	}
//
//	void writeChar(Buffer &buffer, uint8_t value)
//	{
//
//	}
//
//	uint32_t readInt(Buffer &buffer)
//	{
//		assert(buffer.m_index + 4 <= buffer.m_size);
//
//		uint32_t value;
//		value = *((uint32_t*)(buffer.m_data + buffer.m_index));
//		buffer.m_index += 4;
//		return value;
//	}
//};
//
//struct PacketA : Packet
//{
//	std::vector<int> m_values;
//	int x;
//
//	void write(Buffer &buffer)
//	{
//		writeInt(buffer, this->x);
//	}
//
//	void read(Buffer &buffer)
//	{
//		this->x = readInt(buffer);
//	}
//};
