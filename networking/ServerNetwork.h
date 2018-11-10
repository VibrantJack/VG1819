#pragma once

#include <winsock2.h>
#include <Windows.h>
#include "networking\NetworkServices.h"
#include <ws2tcpip.h>
#include <map>
#include <string>
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "6881" 
#define MAX_CLIENTS 2

namespace networking
{
	class ServerNetwork
	{
	friend class ServerGame;
	public:
		ServerNetwork();
		~ServerNetwork();

		bool init();
		void shutdown();

		// send data to all clients
		void sendToAll(char * packets, int totalSize);
		void sendToClient(unsigned int client_id, char * packets, int totalSize);
		void sendToOthers(unsigned int client_id, char * packets, int totalSize);

		// receive incoming data
		int receiveData(unsigned int client_id, char * recvbuf);

		// accept new connections
		bool acceptNewClient(unsigned int & id);

		const std::string& getError() const { return m_strError; }

	private:
		// Socket to listen for new connections
		SOCKET m_listenSocket;

		// Socket to give to the clients
		SOCKET m_clientSocket;

		// for error checking return values
		int m_iResult;

		// table to keep track of each client's socket
		std::map<unsigned int, SOCKET> m_sessions;
		
		std::string m_strError;
	};

}