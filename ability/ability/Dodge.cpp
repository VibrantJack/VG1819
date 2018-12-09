#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"

//Rock

namespace ability
{
	void Dodge::applyStatus(AbilityInfoPackage * p_info)
	{
		//apply Status_Dodge to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_DODGE);

		//set properties
		int dur = p_info->m_intValue.find(UNIT_DURATION)->second;
		se->addCounter(UNIT_DURATION, dur);
		se->m_source = ABILITY_DODGE;
		//attach to target
		se->attach(p_info->m_targets[0]);
	}

	void Dodge::stackStatus(AbilityInfoPackage * p_info)
	{
		ability::Status* se = p_info->m_targets[0]->getStatusContainer()->getStatus(STATUS_DODGE, ABILITY_DODGE);

		//reset duration
		int dur = p_info->m_intValue.find(UNIT_DURATION)->second;
		se->addCounter(UNIT_DURATION, dur);
	}

	int Dodge::effect(AbilityInfoPackage* p_info)
	{
		//check if unit has this status
		if (p_info->m_targets[0]->getStatusContainer()->getStatus(STATUS_DODGE, ABILITY_DODGE))
			stackStatus(p_info);
		else
			applyStatus(p_info);

		//delete package
		done(p_info);

		return 0;
	}

}