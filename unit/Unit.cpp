#include "Unit.h"

//@Rock

namespace unit
{
	Unit::Unit()
	{
	}


	Unit::~Unit()
	{
	}

	void Unit::addStatus(ability::Status *p_newStatus)
	{
		m_statusContainer->addStatus(p_newStatus);
	}

	bool Unit::removeStatus(ability::Status * p_oldStatus)
	{
		return m_statusContainer->removeStatus(p_oldStatus);
	}

	StatusContainer * Unit::getStatus()
	{
		return m_statusContainer;
	}

	int Unit::useAbility(int p_abilityIndex)
	{
		//TO DO assemble info package

		//test purpose
		ability::AbilityInfoPackage* info = new ability::AbilityInfoPackage();
		info->m_target = this;

		AbilityDescription* ad = m_abilityDescription[p_abilityIndex];

		//check unit's lv
		if (m_attributes["LV"] < ad->m_intValue["LV"])
		{
			return 1;//means unit can not use this ability
		}

		//TO DO: cost counter
		if (ad->m_stringValue.find("counter") != ad->m_stringValue.end())
		{
			//TO DO:ask player to cost counter
			std::string counterName = ad->m_stringValue["counter"];
			int maxNum = m_attributes[counterName];
			//info->m_counterNumber =
		}

		//TO DO: get target, passing range and area
		//display range and area
		//select
		//get target info
		//if targetNum = 0
		//return 2
		

		std::string name = ad->m_stringValue["name"];
		info->m_power = ad->m_intValue["power"];

		return ability::AbilityManager::getInstance()->useAbility(name, info);
	}

	int Unit::callStatus(int p_StatusIndex, int p_event)
	{
		//TO DO: method call for status
		return false;
	}

	int Unit::destroyedByDamage()
	{
		//send destroyed event
		//destroy unit (game object)
		return 0;
	}
}
