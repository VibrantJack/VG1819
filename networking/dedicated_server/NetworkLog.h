#pragma once
#include <iostream>
#include <fstream>

#define CLIENT_LOG "Client_Log"
#define SERVER_LOG "Server_Log"

namespace networking
{
	class NetworkLog
	{
	private:
		std::ofstream m_log;
		std::string m_filename;
	public:
		NetworkLog(const std::string& p_type);
		~NetworkLog();

		bool logMessage(const std::string& p_message);
	};
}