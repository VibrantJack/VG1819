#pragma once

// Networking libraries
#include <winsock2.h>
#include <Windows.h>
#include "networking\NetworkServices.h"
#include <ws2tcpip.h>

#include <stdio.h> 

// size of our buffer
#define DEFAULT_BUFLEN 512
// port to connect sockets through 
#define DEFAULT_PORT "6881"
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace networking
{
	class ClientNetwork
	{

	public:
		ClientNetwork();
		~ClientNetwork();

		int receivePackets(char * p_recvbuf);

	public:
		// for error checking function calls in Winsock library
		int m_iResult;

		// socket for client to connect to server
		SOCKET m_connectSocket;
	};
}

