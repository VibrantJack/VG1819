#pragma once
#include <winsock2.h>
#include <Windows.h>

class NetworkServices
{
public:
	static int sendMessage(SOCKET curSocket, char * message, int messageSize);
	static int receiveMessage(SOCKET curSocket, char * buffer, int bufSize);

	//void serialize(TestPacket* packet, char* data);
	//void deserialize(char* data, TestPacket* packet);
	//void printMsg(TestPacket* packet);
};

