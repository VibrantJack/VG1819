#pragma once

#include <winsock2.h>
#include <Windows.h>
#include "networking\dedicated_server\NetworkServices.h"
#include <ws2tcpip.h>
#include <map>
#include <string>
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "6881" 
#define MAX_CLIENTS 2

namespace networking
{
	class GameSession;
	class ServerNetwork
	{
		
	friend class ServerGame;
	public:
		struct ClientInfo
		{
			SOCKET m_socket = INVALID_SOCKET;
			int m_serverClientId = -1;		// The ID assigned to the player when they connect to the server; should not change
			int m_gameSessionClientId = -1; // The ID for the player in the current GameSession, may change
			GameSession* m_gameSession = nullptr;
		};

		ServerNetwork();
		~ServerNetwork();

		bool init();
		void shutdown();

		// send data to all clients
		void sendToAll(char * packets, int totalSize);
		void sendToClient(unsigned int client_id, char * packets, int totalSize);
		void sendToOthers(unsigned int client_id, char * packets, int totalSize);

		// Send functions for polled clients
		void sendToPolledClient(unsigned int client_id, char * packets, int totalSize);

		void sendToSocket(ClientInfo* p_info, char * p_packets, int p_totalSize);

		// receive incoming data
		int receiveData(ClientInfo* p_client, char* p_buffer);
		int receiveData(unsigned int p_clientId, char* p_buffer);
		int receiveDataFromPolled(unsigned int p_clientId, char* p_buffer);

		// accept new connections
		bool acceptNewClient(unsigned int& p_iClientId);
		void addPolledClientToSessions(unsigned int p_iPolledClientId, unsigned int& p_iClientId);

		void removeQueuedRemovals();
		void queuePolledClientRemoval(ClientInfo* p_client, bool p_closeSocket = true);
		void queueClientRemoval(ClientInfo* p_client, bool p_closeSocket = true);
		void removePolledClient(ClientInfo* p_client, bool p_closeSocket = true);
		void removeClient(ClientInfo* p_client, bool p_closeSocket = true);

		const SOCKET getClientSocket(unsigned int p_clientId) const;

		const std::string& getError() const { return m_strError; }

	private:
		// Socket to listen for new connections
		SOCKET m_listenSocket;

		// Socket to give to the clients
		SOCKET m_clientSocket;

		// for error checking return values
		int m_iResult;

		// m_sessions: master list of client sockets that are connected to the server
		// m_polledSessions: client sockets that have polled for the server and have not commit to joining
		std::map<unsigned int, ClientInfo*> m_sessions;
		std::map<unsigned int, ClientInfo*> m_polledSessions;

		//pair: Client to remove, close socket?
		std::vector<std::pair<ClientInfo*, bool>> m_clientsToRemove;
		std::vector<std::pair<ClientInfo*, bool>> m_polledClientsToRemove;
		
		std::string m_strError;
	};

}