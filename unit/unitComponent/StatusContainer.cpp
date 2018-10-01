#pragma once
#include "StatusContainer.h"

namespace unit
{
	void unit::StatusContainer::addStatus(ability::Status * p_newStatus)
	{
		m_statusList.push_back(p_newStatus);
	}

	bool unit::StatusContainer::removeStatus(const ability::Status * p_oldStatus)
	{
		for (auto it = m_statusList.begin(); it != m_statusList.end(); it++)
		{
			if ((*it) == p_oldStatus)
			{
				m_statusList.erase(it);
				return true;
			}
		}
		return false;
	}
}

