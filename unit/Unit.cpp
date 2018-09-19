#include "Unit.h"

Unit::Unit()
{
}


Unit::~Unit()
{
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
	//TO DO assemble info package

	//test purpose
	AbilityInfoPackage* info = new AbilityInfoPackage();
	info->m_target = this;
	info->m_power = 4;

	return AbilityManager::getInstance()->useAbility(m_Ability[p_abilityIndex], info);
}

int Unit::callStatus(int p_StatusIndex, int p_event)
{
	//TO DO: method call for status
	return false;
}
