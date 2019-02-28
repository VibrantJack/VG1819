#pragma once
#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

int ability::Rally::effect(AbilityInfoPackage * p_info)
{
	int in_change = p_info->m_intValue.at(UNIT_POWER);
	for (unit::Unit* u : p_info->m_targets)
	{
		//apply Status_Encourage to target
		ability::Status* status = ability::StatusManager::getInstance()->findStatus(STATUS_TEMP_CHANGE);
		addStatusInfo(status, p_info);

		status->m_source = m_name;
		status->addAttributeChange(UNIT_IN, in_change);

		//duration
		int dur = p_info->m_intValue[UNIT_DURATION];
		status->addCounter(UNIT_DURATION, dur);

		status->attach(u);
	}

	//delete package
	done(p_info);

	return 0;
}