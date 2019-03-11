#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	void LordOrder::applyStatus(AbilityInfoPackage * p_info, unit::Unit* p_unit)
	{
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_LORD_ORDER);

		std::vector<std::string> intKeys;
		intKeys.push_back(UNIT_POWER);
		intKeys.push_back(UNIT_DURATION);

		addStatusInfo(se, p_info, intKeys);

		//set caster
		se->setCaster(p_info->m_source);

		//attach to target
		se->attach(p_unit);

	}

	int LordOrder::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//check if unit has this status
			for (unit::Unit* u : p_info->m_targets)
			{
				if (!u->getStatusContainer()->getStatus(STATUS_LORD_ORDER, m_name))//doesn't have status
				{
					applyStatus(p_info, u);
				}
			}
		}

		//delete package
		done(p_info);

		return 0;
	}
}