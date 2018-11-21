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
		//delete[] message; // If using createBuffer to create char * buffers
		return iResult;
	}

	int NetworkServices::receiveMessage(SOCKET curSocket, char * buffer, int bufSize)
	{
		return recv(curSocket, buffer, bufSize, 0);
	}


	// Only use createBuffer if you will be sending the buffer through sendMessage which will delete char[]
	Buffer& NetworkServices::createBuffer(int p_packetSize)
	{
		Buffer buffer;
		buffer.m_data = new char[p_packetSize];
		buffer.m_size = p_packetSize;
		return buffer;
	}
}