#include "Unit.h"

//@Rock

namespace unit
{
	Unit::Unit()
	{
		m_statusContainer = new StatusContainer();
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

	ability::Status* Unit::getStatus(const std::string & p_name)
	{
		return m_statusContainer->getStatus(p_name);
	}

	StatusContainer * Unit::getStatusContainer()
	{
		return m_statusContainer;
	}

	int Unit::useAbility(const std::string& p_abilityName)
	{
		AbilityDescription* ad = m_ADList[p_abilityName];

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
		
		//TO DO assemble info package

		//test purpose
		ability::AbilityInfoPackage* info = new ability::AbilityInfoPackage();
		info->m_source = this;
		info->m_target = this;

		std::string name = ad->m_stringValue["name"];
		info->m_intValue["power"] = ad->m_intValue["power"];

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
