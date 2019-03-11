#pragma once
#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	int PowerSurge::effect(AbilityInfoPackage * p_info)
	{
		std::string name = p_info->m_stringValue[COUNTER_NAME];
		int counter = p_info->m_intValue[name];
		int inChange = p_info->m_intValue[UNIT_IN];
		int mvChange = p_info->m_intValue[UNIT_MV];
		//int dur = p_info->m_intValue[UNIT_DURATION];

		//remove counter
		changeCounter(p_info->m_source, name, -counter);

		for (unit::Unit* u : p_info->m_targets)
		{
			int cost = u->m_attributes[UNIT_COST];
			if (cost <= counter)
			{
				//apply move change
				ability::Status* status = ability::StatusManager::getInstance()->findStatus(STATUS_TEMP_CHANGE);

				//status->addAttributeChange(UNIT_IN, inChange);
				status->addAttributeChange(UNIT_MV, mvChange);

				//status info
				std::vector<std::string> intKeys;
				intKeys.push_back(UNIT_DURATION);

				addStatusInfo(status, p_info, intKeys);

				status->attach(u);

				//apply in change
				status = ability::StatusManager::getInstance()->findStatus(STATUS_IN_CHANGE);

				status->addAttributeChange(UNIT_IN, inChange);
				//status->addAttributeChange(UNIT_MV, mvChange);

				//status info
				addStatusInfo(status, p_info, intKeys);

				status->attach(u);
			}
		}

		UniversalSounds::playSound("glocken_up");

		//delete package
		done(p_info);

		return 0;
	}
}