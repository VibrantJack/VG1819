#pragma once
#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	int PowerSurge::effect(AbilityInfoPackage * p_info)
	{
		int counter = p_info->m_intValue[COUNTER_ENERGY];
		int inChange = p_info->m_intValue[UNIT_IN];
		int mvChange = p_info->m_intValue[UNIT_MV];
		int dur = p_info->m_intValue[UNIT_DURATION];

		//remove counter
		changeCounter(p_info->m_source, COUNTER_ENERGY, -counter);

		for (unit::Unit* u : p_info->m_targets)
		{
			int cost = u->m_attributes[UNIT_COST];
			if (cost <= counter)
			{
				ability::Status* status = ability::StatusManager::getInstance()->findStatus(STATUS_TEMP_CHANGE);

				status->addAttributeChange(UNIT_IN, inChange);
				status->addAttributeChange(UNIT_MV, mvChange);
				status->addCounter(UNIT_DURATION, dur);

				status->attach(u);
			}
		}

		//delete package
		done(p_info);

		return 0;
	}
}