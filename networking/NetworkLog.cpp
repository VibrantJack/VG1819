#include "NetworkLog.h"
#include <ctime>
#include <sstream>

#define LOG_DIRECTORY "../networking/logs/"
#define LOG_EXTENSION ".txt"

namespace networking
{
	NetworkLog::NetworkLog(const std::string& p_type)
	{
		std::stringstream filename;
		filename << p_type;
		
		time_t now = time(0);
		tm *gmtm = gmtime(&now);
		
		filename << "_" << gmtm->tm_mday
			<< "_" << (gmtm->tm_mon + 1)
			<< "_" << (gmtm->tm_year + 1900)
			<< "_" << gmtm->tm_hour
			<< "_" << gmtm->tm_min
			<< "_" << gmtm->tm_sec;

		m_filename = LOG_DIRECTORY + filename.str() + LOG_EXTENSION;
		m_log = std::ofstream(m_filename);
	}

	NetworkLog::~NetworkLog()
	{
		if (m_log.is_open())
		{
			m_log.close();
		}
	}

	bool NetworkLog::logMessage(const std::string& p_message)
	{
		if (m_log.is_open())
		{
			m_log << p_message << std::endl;
			return true;
		}
		return false;
	}
}