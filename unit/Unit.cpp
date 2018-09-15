#include "Unit.h"

Unit::Unit()
{
}


Unit::~Unit()
{
}

void Unit::addAbility(Ability * p_newAbility)
{
	m_Ability.push_back(p_newAbility);
}

void Unit::addStatus(Status *p_newStatus)
{
	m_Status.push_back(p_newStatus);
}

bool Unit::removeStatus(Status * p_oldStatus)
{
	for (std::vector<Status*>::iterator it = m_Status.begin(); it != m_Status.end(); it++)
	{
		if (*it == p_oldStatus)
		{
			m_Status.erase(it);
			return true;
		}
	}
	return false;
}

int Unit::useAbility(int p_abilityIndex)
{
	return m_Ability[p_abilityIndex]->effect();
}

int Unit::callStatus(int p_StatusIndex, int p_event)
{
	//TO DO: method call for status
	return false;
}
