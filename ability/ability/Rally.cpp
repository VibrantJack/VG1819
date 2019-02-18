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
		status->addCounter(UNIT_DURATION, 2);

		status->attach(u);
	}

	UniversalSounds::playSound("drums");

	//delete package
	done(p_info);

	return 0;
}