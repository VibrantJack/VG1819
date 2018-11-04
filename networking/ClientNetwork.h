#pragma once

// Networking libraries
#include <winsock2.h>
#include <Windows.h>
#include "networking\NetworkServices.h"
#include <ws2tcpip.h>

#include <stdio.h> 
#include <string>

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
	friend class ClientGame;
	public:
		ClientNetwork();
		~ClientNetwork();

		bool init(const std::string &p_strAddr = "127.0.0.1");
		void shutdown();

		int receivePackets(char * p_recvbuf);

		const std::string& getError() const { return m_strError; }
	private:
		// for error checking function calls in Winsock library
		int m_iResult;

		// socket for client to connect to server
		SOCKET m_connectSocket;

		std::string m_strError;
	};
}

