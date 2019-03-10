#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	void Corrupt::applyStatus(AbilityInfoPackage* p_info, unit::Unit* p_unit)
	{
		//apply Status_Poison to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_POISON);

		std::vector<std::string> intKeys;
		intKeys.push_back(UNIT_POWER);
		intKeys.push_back(UNIT_DURATION);

		addStatusInfo(se, p_info, intKeys);

		//attach to target
		se->attach(p_unit);
	}

	void Corrupt::refresh(AbilityInfoPackage * p_info, unit::Unit * p_unit, Status* p_status)
	{
		//get current status power
		int currentPow = p_status->m_intValue[UNIT_POWER];

		//get ability power
		int pow = p_info->m_intValue[UNIT_POWER];

		//if ability power is higher than current power, status will use ability power
		if (pow >= currentPow)
		{
			p_status->m_intValue[UNIT_POWER] = currentPow;

			//refresh duration
			int dur = p_info->m_intValue[UNIT_DURATION];
			p_status->m_intValue[UNIT_DURATION] = dur;
		}
	}

	int Corrupt::effect(AbilityInfoPackage* p_info)
	{
		//change power
		std::string name = p_info->m_stringValue[COUNTER_NAME];
		int powerFactor = p_info->m_intValue[COUNTER_POWER];
		int counter = p_info->m_intValue[name];
		p_info->m_intValue[UNIT_POWER] = powerFactor * counter;

		//remove counter
		changeCounter(p_info->m_source, name, -counter);

		//check if unit has this status
		for (unit::Unit* u : p_info->m_targets)
		{
			Status* s = u->getStatusContainer()->getStatus(STATUS_POISON, m_name);
			if (s != nullptr)
			{
				//has poison already then refresh it
				refresh(p_info, u, s);
			}
			else
			{
				//doesn't poison, apply status
				applyStatus(p_info, u);
			}
		}

		//delete package
		done(p_info);

		return 0;
	}

}