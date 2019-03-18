#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	void CursedProtection::applyStatus(AbilityInfoPackage * p_info, unit::Unit* p_unit)
	{
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_CURSED_BEING);

		std::vector<std::string> intKeys;
		intKeys.push_back(UNIT_DURATION);
		intKeys.push_back("SVC_power");
		intKeys.push_back("SVC_duration");

		std::vector<std::string> stringKeys;
		intKeys.push_back("SVC_name");
		intKeys.push_back("SVC_description");

		addStatusInfo(se, p_info, intKeys,stringKeys);

		//attach to target
		se->attach(p_unit);

	}

	int CursedProtection::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//check if unit has this status
			for (unit::Unit* u : p_info->m_targets)
			{
				if (!u->getStatusContainer()->getStatus(STATUS_CURSED_BEING, m_name))//doesn't have status
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