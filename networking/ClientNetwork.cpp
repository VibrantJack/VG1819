/*
* ClientNetwork
* Network class that setups Winsock for the client and attempts
* to connect to a server.
* Also has a function that receives data from the server
*/
#include "networking\ClientNetwork.h"

namespace networking
{
	ClientNetwork::ClientNetwork()
	{
		
	}

	ClientNetwork::~ClientNetwork()
	{
		shutdown();
	}

	bool ClientNetwork::init(const std::string &p_strAddr)
	{
		// create WSADATA object
		WSADATA wsaData;

		// socket
		m_connectSocket = INVALID_SOCKET;

		// holds address info for socket to connect to
		struct addrinfo *result = NULL,
			*ptr = NULL,
			hints;

		// Initialize Winsock
		m_iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

		if (m_iResult != 0) {
			m_strError = "WSAStartup failed with error: " + std::to_string(m_iResult);
			return false;
		}

		// set address info
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;  //TCP connection!!!


		//resolve server address and port 
		//m_iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
		m_iResult = getaddrinfo(p_strAddr.c_str(), DEFAULT_PORT, &hints, &result);

		if (m_iResult != 0)
		{
			m_strError = "getaddrinfo failed with error: " + std::to_string(m_iResult);
			WSACleanup();
			return false;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			// Create a SOCKET for connecting to server
			m_connectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);

			if (m_connectSocket == INVALID_SOCKET) {
				m_strError = "socket failed with error: " + std::to_string(WSAGetLastError());
				WSACleanup();
				return false;
			}

			// Connect to server.
			m_iResult = connect(m_connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

			if (m_iResult == SOCKET_ERROR)
			{
				closesocket(m_connectSocket);
				m_connectSocket = INVALID_SOCKET;
				m_strError = "The server is down... did not connect";
			}
		}



		// no longer need address info for server
		freeaddrinfo(result);



		// if connection failed
		if (m_connectSocket == INVALID_SOCKET)
		{
			m_strError = "Unable to connect to server!";
			WSACleanup();
			return false;
		}

		// Set the mode of the socket to be nonblocking
		u_long iMode = 1;

		m_iResult = ioctlsocket(m_connectSocket, FIONBIO, &iMode);
		if (m_iResult == SOCKET_ERROR)
		{
			m_strError = "ioctlsocket failed with error: " + std::to_string(WSAGetLastError());
			closesocket(m_connectSocket);
			m_connectSocket = INVALID_SOCKET;
			WSACleanup();
			return false;
		}

		//disable nagle
		char value = 1;
		setsockopt(m_connectSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

		return true;
	}

	void ClientNetwork::shutdown()
	{
		closesocket(m_connectSocket);
		m_connectSocket = INVALID_SOCKET;
		WSACleanup();
	}

	int ClientNetwork::receivePackets(char * recvbuf)
	{
		m_iResult = NetworkServices::receiveMessage(m_connectSocket, recvbuf, MAX_PACKET_SIZE);

		if (m_iResult == 0)
		{
			printf("Connection closed\n");
			closesocket(m_connectSocket);
			m_connectSocket = INVALID_SOCKET;
			WSACleanup();
			// TODO: Properly disconnect rather than shutdown lol
			// Will need to clean up ClientNetwork and properly clean up ClientGame
		}

		return m_iResult;
	}
}