/*
* ServerNetwork
* Network class that setups Winsock for the server and attempts
* to accept connecting clients
* Also has a function to receive data from all clients, send
* data to all clients, and send data to a specific client
*/
#include "networking\ServerNetwork.h"

namespace networking
{
	ServerNetwork::ServerNetwork(void)
	{
		// create WSADATA object
		WSADATA wsaData;

		// our sockets for the server
		m_listenSocket = INVALID_SOCKET;
		m_clientSocket = INVALID_SOCKET;

		// address info for the server to listen to
		struct addrinfo *result = NULL;
		struct addrinfo hints;

		// Initialize Winsock
		m_iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (m_iResult != 0) {
			printf("WSAStartup failed with error: %d\n", m_iResult);
			exit(1);
		}

		// set address information
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;    // TCP connection!!!
		hints.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		m_iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
		if (m_iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", m_iResult);
			WSACleanup();
			exit(1);
		}

		// Create a SOCKET for connecting to server
		m_listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (m_listenSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			exit(1);
		}

		// Set the mode of the socket to be nonblocking
		u_long iMode = 1;
		m_iResult = ioctlsocket(m_listenSocket, FIONBIO, &iMode);
		if (m_iResult == SOCKET_ERROR) {
			printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
			closesocket(m_listenSocket);
			WSACleanup();
			exit(1);
		}

		// Setup the TCP listening socket
		m_iResult = bind(m_listenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (m_iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(m_listenSocket);
			WSACleanup();
			exit(1);
		}

		// no longer need address information
		freeaddrinfo(result);

		// start listening for new clients attempting to connect
		m_iResult = listen(m_listenSocket, SOMAXCONN);
		if (m_iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(m_listenSocket);
			WSACleanup();
			exit(1);
		}
	}


	ServerNetwork::~ServerNetwork(void)
	{
		closesocket(m_listenSocket);
		SOCKET currentSocket;
		for (auto iter = m_sessions.begin(); iter != m_sessions.end(); iter++)
		{
			currentSocket = iter->second;
			closesocket(currentSocket);
		}
		WSACleanup();
	}

	// accept new connections
	bool ServerNetwork::acceptNewClient(unsigned int & id)
	{
		// if client waiting, accept the connection and save the socket
		m_clientSocket = accept(m_listenSocket, NULL, NULL);

		if (m_clientSocket != INVALID_SOCKET)
		{
			//disable nagle on the client's socket
			char value = 1;
			setsockopt(m_clientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

			// insert new client into session id table
			m_sessions.insert(std::pair<unsigned int, SOCKET>(id, m_clientSocket));

			return true;
		}
		return false;
	}

	// receive incoming data
	int ServerNetwork::receiveData(unsigned int client_id, char * recvbuf)
	{
		if (m_sessions.find(client_id) != m_sessions.end())
		{
			SOCKET currentSocket = m_sessions[client_id];
			m_iResult = NetworkServices::receiveMessage(currentSocket, recvbuf, MAX_PACKET_SIZE);

			if (m_iResult == 0)
			{
				printf("Connection closed\n");
				closesocket(currentSocket);
			}

			return m_iResult;
		}
		return 0;
	}

	// send data to all clients
	void ServerNetwork::sendToAll(char * packets, int totalSize)
	{
		//printf("Send to all called\n");
		SOCKET currentSocket;
		std::map<unsigned int, SOCKET>::iterator iter;
		int iSendResult;

		for (iter = m_sessions.begin(); iter != m_sessions.end(); iter++)
		{
			currentSocket = iter->second;
			iSendResult = NetworkServices::sendMessage(currentSocket, packets, totalSize);

			if (iSendResult == SOCKET_ERROR)
			{
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(currentSocket);
			}
		}
	}

	void ServerNetwork::sendToClient(unsigned int client_id, char * packets, int totalSize)
	{
		SOCKET currentSocket;
		std::map<unsigned int, SOCKET>::iterator iter;
		int iSendResult;

		iter = m_sessions.find(client_id);
		if (iter != m_sessions.end()) {
			currentSocket = iter->second;
			iSendResult = NetworkServices::sendMessage(currentSocket, packets, totalSize);

			if (iSendResult == SOCKET_ERROR)
			{
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(currentSocket);
			}
		}
	}

	void ServerNetwork::sendToOthers(unsigned int client_id, char * packets, int totalSize)
	{
		SOCKET currentSocket;
		std::map<unsigned int, SOCKET>::iterator iter;
		int iSendResult;

		for (iter = m_sessions.begin(); iter != m_sessions.end(); iter++)
		{
			if (iter->first != client_id)
			{
				currentSocket = iter->second;
				iSendResult = NetworkServices::sendMessage(currentSocket, packets, totalSize);

				if (iSendResult == SOCKET_ERROR)
				{
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(currentSocket);
				}
			}
		}
	}
}