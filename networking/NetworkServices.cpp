/*
* NetworkServices
* Class wraps Winsock send and recv functions for use with
* ServerNetwork and ClientNetwork
*/
#include "networking\NetworkServices.h"
#include <stdio.h>

namespace networking
{
	int NetworkServices::sendMessage(SOCKET curSocket, char * message, int messageSize)
	{
		int iResult = send(curSocket, message, messageSize, 0);
		return iResult;
	}

	int NetworkServices::receiveMessage(SOCKET curSocket, char * buffer, int bufSize)
	{
		return recv(curSocket, buffer, bufSize, 0);
	}

	void NetworkServices::serializePacketTest(Packet p_packet, char* p_data)
	{
		p_packet.serialize(p_data);
	}

	char* NetworkServices::serializePacket(Packet p_packet)
	{
		PacketTypes packetType = (PacketTypes)p_packet.packetType;
		switch (packetType)
		{
		case PacketTypes::CLIENT_SUMMON_UNIT:
		{
			char packet_data[sizeof(Packet)];
			p_packet.serialize(packet_data);
			return packet_data;
		}
		}
		return nullptr;
	}
}