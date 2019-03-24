/*
* ServerNetwork
* Network class that setups Winsock for the server and attempts
* to accept connecting clients
* Also has a function to receive data from all clients, send
* data to all clients, and send data to a specific client
*/
#include "networking\dedicated_server\ServerNetwork.h"
#include "GameSession.h"

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
		printf("ServerNetwork initialized\n");
		return true;
	}

	void ServerNetwork::shutdown()
	{
		closesocket(m_listenSocket);
		m_listenSocket = INVALID_SOCKET;

		SOCKET currentSocket;
		for (auto iter = m_sessions.begin(); iter != m_sessions.end(); iter++)
		{
			ClientInfo* client = iter->second;
			if (client->m_socket != INVALID_SOCKET)
			{
				closesocket(client->m_socket);
				client->m_socket = INVALID_SOCKET;
			}
		}
		WSACleanup();
		printf("ServerNetwork shutdown\n");
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

			ClientInfo* client = new ClientInfo();
			client->m_socket = m_clientSocket;
			client->m_serverClientId = p_iClientId;

			// Insert new client into polled sessions id map
			m_sessions.insert(std::pair<unsigned int, ClientInfo*>(p_iClientId, client));

			m_playerCount++;
			setServerInfoChanged(true);

			return true;
		}
		return false;
	}

	void ServerNetwork::removeQueuedRemovals()
	{
		for (auto toRemove: m_clientsToRemove)
		{
			removeClient(toRemove.first, toRemove.second);
		}
		m_clientsToRemove.clear();
	}

	void ServerNetwork::queueClientRemoval(ClientInfo* p_client, bool p_closeSocket)
	{
		m_clientsToRemove.push_back(std::make_pair(p_client, p_closeSocket));
	}

	void ServerNetwork::removeClient(ClientInfo* p_client, bool p_closeSocket)
	{
		if (p_client->m_gameSession != nullptr)
		{
			p_client->m_gameSession->removePlayer(p_client);
		}

		if (auto it = m_sessions.find(p_client->m_serverClientId) != m_sessions.end())
		{
			printf("Server disconnecting [Polled Client: %d]\n", p_client->m_serverClientId);
			auto result = m_sessions.erase(p_client->m_serverClientId);
			closesocket(p_client->m_socket);
			delete p_client;

			m_playerCount--;
			setServerInfoChanged(true);
			
		} 
		else
		{
			printf("Server cannot remove [Polled Client: %d]: polled client not found\n", p_client->m_serverClientId);
		}
	}
	
	int ServerNetwork::receiveData(ClientInfo* p_client, char* p_buffer)
	{
		m_iResult = NetworkServices::receiveMessage(p_client->m_socket, p_buffer, MAX_PACKET_SIZE);

		if (m_iResult == 0)
		{
			printf("Server lost connection to [Client: %d]\n", p_client->m_serverClientId);
			closesocket(p_client->m_socket);
			queueClientRemoval(p_client);
		}
		return m_iResult;
	}

	int ServerNetwork::receiveData(unsigned int client_id, char * recvbuf)
	{
		if (auto it = m_sessions.find(client_id) != m_sessions.end())
		{
			ClientInfo* client = m_sessions[client_id];
			m_iResult = NetworkServices::receiveMessage(client->m_socket, recvbuf, MAX_PACKET_SIZE);

			if (m_iResult == 0)
			{
				printf("Server lost connection to [Polled Client: %d]\n", client_id);
				queueClientRemoval(client);
			}
			return m_iResult;
		}
		return 0;
	}

	// send data to all clients
	void ServerNetwork::sendToAll(char * packets, int totalSize)
	{
		ClientInfo* client;
		std::map<unsigned int, ClientInfo*>::iterator iter;
		int sendResult;

		for (iter = m_sessions.begin(); iter != m_sessions.end(); ++iter)
		{
			client = iter->second;
			sendResult = NetworkServices::sendMessage(client->m_socket, packets, totalSize);

			if (sendResult == SOCKET_ERROR)
			{
				printf("send to [Client: %d] failed with error: %d\n", iter->first, WSAGetLastError());
				queueClientRemoval(client);
			}
		}
	}

	// Send to all clients except the one specified
	void ServerNetwork::sendToOthers(unsigned int client_id, char * packets, int totalSize)
	{
		ClientInfo* client;
		std::map<unsigned int, ClientInfo*>::iterator iter;
		int iSendResult;

		for (iter = m_sessions.begin(); iter != m_sessions.end(); /* no increment */)
		{
			if (iter->first != client_id)
			{
				client = iter->second;
				iSendResult = NetworkServices::sendMessage(client->m_socket, packets, totalSize);

				if (iSendResult == SOCKET_ERROR)
				{
					printf("send failed with error: %d\n", WSAGetLastError());
					queueClientRemoval(client);
				}				
			}
		}
	}

	void ServerNetwork::sendToClient(unsigned int client_id, char * packets, int totalSize)
	{
		ClientInfo* client;
		std::map<unsigned int, ClientInfo*>::iterator iter;
		int iSendResult;

		iter = m_sessions.find(client_id);
		if (iter != m_sessions.end())
		{
			client = iter->second;
			iSendResult = NetworkServices::sendMessage(client->m_socket, packets, totalSize);

			if (iSendResult == SOCKET_ERROR)
			{
				printf("send failed with error: %d\n", WSAGetLastError());
				queueClientRemoval(client);
			}
			
		}
	}

	void ServerNetwork::sendToSocket(ClientInfo* p_client, char * p_packets, int p_totalSize)
	{
		int result = NetworkServices::sendMessage(p_client->m_socket, p_packets, p_totalSize);

		if (result == SOCKET_ERROR)
		{
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(p_client->m_socket);
			queueClientRemoval(p_client);
			
		}
	}

	void ServerNetwork::setServerInfoChanged(bool p_changed)
	{
		m_serverInfoChanged = p_changed;
	}

	const SOCKET ServerNetwork::getClientSocket(unsigned int p_clientId) const
	{
		auto it = m_sessions.find(p_clientId);
		if (it != m_sessions.end())
		{
			return (*it).second->m_socket;
		}
		else
		{
			return INVALID_SOCKET;
		}
	}
}