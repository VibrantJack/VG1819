#pragma once

#include <winsock2.h>
#include <Windows.h>
#include "networking\NetworkData.h"

namespace networking
{
	class NetworkServices
	{
	public:
		static int sendMessage(SOCKET curSocket, char * message, int messageSize);
		static int receiveMessage(SOCKET curSocket, char * buffer, int bufSize);

		static char* serializePacket(Packet p_packet);
		static void serializePacketTest(Packet* p_packet, char* p_data);
	};
}
