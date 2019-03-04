/*
* NetworkServices
* Class wraps Winsock send and recv functions for use with
* ServerNetwork and ClientNetwork
*/
#include "networking\dedicated_server\NetworkServices.h"
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
}