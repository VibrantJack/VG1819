/*
* ServerNetwork
* Network class that setups Winsock for the server and attempts
* to accept connecting clients
* Also has a function to receive data from all clients, send
* data to all clients, and send data to a specific client
*/
#include "networking\ServerNetwork.h"
#include "kitten\event_system\EventManager.h"

namespace networking
{
	ServerNetwork::ServerNetwork()
	{
		
	}


	ServerNetwork::~ServerNetwork()
	{
		shutdown();
	}

	bool ServerNetwork::init()
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
			m_strError = "WSAStartup failed with error: " + std::to_string(m_iResult);
			return false;
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
			m_strError = "getaddrinfo failed with error: " + std::to_string(m_iResult);
			WSACleanup();
			return false;
		}

		// Create a SOCKET for connecting to server
		m_listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (m_listenSocket == INVALID_SOCKET) {
			m_strError = "socket failed with error: " + std::to_string(WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return false;
		}

		// Set the mode of the socket to be nonblocking
		u_long iMode = 1;
		m_iResult = ioctlsocket(m_listenSocket, FIONBIO, &iMode);
		if (m_iResult == SOCKET_ERROR) {
			m_strError = "ioctlsocket failed with error: " + std::to_string(WSAGetLastError());
			closesocket(m_listenSocket);
			m_listenSocket = INVALID_SOCKET;
			WSACleanup();
			return false;
		}

		// Setup the TCP listening socket
		m_iResult = bind(m_listenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (m_iResult == SOCKET_ERROR) {
			m_strError = "bind failed with error: " + std::to_string(WSAGetLastError());
			freeaddrinfo(result);
			closesocket(m_listenSocket);
			m_listenSocket = INVALID_SOCKET;
			WSACleanup();
			return false;
		}

		// no longer need address information
		freeaddrinfo(result);

		// start listening for new clients attempting to connect
		m_iResult = listen(m_listenSocket, SOMAXCONN);
		if (m_iResult == SOCKET_ERROR) {
			m_strError = "listen failed with error: " + std::to_string(WSAGetLastError());
			closesocket(m_listenSocket);
			m_listenSocket = INVALID_SOCKET;
			WSACleanup();
			return false;
		}

		return true;
	}

	void ServerNetwork::shutdown()
	{
		closesocket(m_listenSocket);
		m_listenSocket = INVALID_SOCKET;

		SOCKET currentSocket;
		for (auto iter = m_sessions.begin(); iter != m_sessions.end(); iter++)
		{
			currentSocket = iter->second;
			if (currentSocket != INVALID_SOCKET)
			{
				closesocket(currentSocket);
				iter->second = INVALID_SOCKET;
			}
		}
		WSACleanup();
	}

	bool ServerNetwork::acceptNewClient(unsigned int & p_iClientId)
	{
		// if client waiting, accept the connection and save the socket
		m_clientSocket = accept(m_listenSocket, NULL, NULL);

		if (m_clientSocket != INVALID_SOCKET)
		{
			//disable nagle on the client's socket
			char value = 1;
			setsockopt(m_clientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

			// insert new client into session id table
			m_sessions.insert(std::pair<unsigned int, SOCKET>(p_iClientId, m_clientSocket));

			return true;
		}
		return false;
	}

	void ServerNetwork::removeClient(unsigned int & p_iClientId)
	{
		if (m_sessions.find(p_iClientId) != m_sessions.end())
		{
			printf("Server disconnecting [Client: %d]\n", p_iClientId);

			SOCKET currentSocket = m_sessions[p_iClientId];
			closesocket(currentSocket);
			//currentSocket = INVALID_SOCKET;
			m_sessions[p_iClientId] = INVALID_SOCKET;

			// Cannot remove the socket from the map as this function is called from ServerGame::update()
			// iterator that references the current socket
			// Socket clean up should be taken care of in ServerNetwork::shutdown();
			// Consider something similar to K_GameObjectManager::deleteQueuedObjects() if necessary 
			//m_sessions.erase(p_iClientId);
		}
		else
		{
			printf("Server cannot remove [Client: %d]: client not found\n", p_iClientId);
		}
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
				printf("Server lost connection to [Client: %d]\n", client_id);
				closesocket(currentSocket);
				m_sessions[client_id] = INVALID_SOCKET;

				// Display disconnect screen; Server detected client disconnect
				kitten::Event* eventData = new kitten::Event(kitten::Event::End_Game_Screen);
				eventData->putInt(GAME_END_RESULT, 2);
				kitten::EventManager::getInstance()->triggerEvent(kitten::Event::End_Game_Screen, eventData);
			}
			return m_iResult;
		}
		return 0;
	}

	// send data to all clients
	void ServerNetwork::sendToAll(char * packets, int totalSize)
	{
		SOCKET currentSocket;
		std::map<unsigned int, SOCKET>::iterator iter;
		int iSendResult;

		for (iter = m_sessions.begin(); iter != m_sessions.end(); iter++)
		{
			currentSocket = iter->second;
			if (currentSocket != INVALID_SOCKET)
			{
				iSendResult = NetworkServices::sendMessage(currentSocket, packets, totalSize);

				if (iSendResult == SOCKET_ERROR)
				{
					printf("send to [Client: %d] failed with error: %d\n", iter->first, WSAGetLastError());
					closesocket(currentSocket);
					iter->second = INVALID_SOCKET;
				}
			}
		}
	}

	// Send to a specific client
	void ServerNetwork::sendToClient(unsigned int client_id, char * packets, int totalSize)
	{
		SOCKET currentSocket;
		std::map<unsigned int, SOCKET>::iterator iter;
		int iSendResult;

		iter = m_sessions.find(client_id);
		if (iter != m_sessions.end()) {
			currentSocket = iter->second;
			if (currentSocket != INVALID_SOCKET)
			{
				iSendResult = NetworkServices::sendMessage(currentSocket, packets, totalSize);

				if (iSendResult == SOCKET_ERROR)
				{
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(currentSocket);
					iter->second = INVALID_SOCKET;
				}
			}
		}
	}

	// Send to all clients except the one specified
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
				if (currentSocket != INVALID_SOCKET)
				{
					iSendResult = NetworkServices::sendMessage(currentSocket, packets, totalSize);

					if (iSendResult == SOCKET_ERROR)
					{
						printf("send failed with error: %d\n", WSAGetLastError());
						closesocket(currentSocket);
						iter->second = INVALID_SOCKET;
					}
				}
			}
		}
	}
}