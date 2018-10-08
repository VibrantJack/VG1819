#pragma once
#include "ability/status/Status.h"
#include <string>
#include <vector>

//Rock

//This class will contain a list of status

namespace unit
{
	class StatusContainer
	{
	public:
		std::vector<ability::Status*> m_statusList;

		StatusContainer();

		void addStatus(ability::Status *p_newStatus);
		bool removeStatus(const ability::Status *p_oldStatus);
		ability::Status* getStatus(const std::string& p_name);
	};
}
