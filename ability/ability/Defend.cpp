#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"

//Rock

namespace ability
{
	void Defend::applyStatus(AbilityInfoPackage * p_info)
	{
		//apply Status_Dodge to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_DODGE);

		//set properties
		addStatusInfo(se, p_info);

		int dur = p_info->m_intValue.find(UNIT_DURATION)->second;
		se->addCounter(UNIT_DURATION, dur);

		se->m_source = ABILITY_DEFEND;
		//attach to target
		se->attach(p_info->m_targets[0]);
	}

	void Defend::stackStatus(AbilityInfoPackage * p_info)
	{
		ability::Status* se = p_info->m_targets[0]->getStatusContainer()->getStatus(STATUS_DODGE, ABILITY_DEFEND);

		//reset duration
		int dur = p_info->m_intValue.find(UNIT_DURATION)->second;
		se->addCounter(UNIT_DURATION, dur);
	}

	int Defend::effect(AbilityInfoPackage* p_info)
	{
		//check if unit has this status
		if (p_info->m_targets[0]->getStatusContainer()->getStatus(STATUS_DODGE, ABILITY_DEFEND))
			stackStatus(p_info);
		else
			applyStatus(p_info);

		UniversalSounds::playSound("sword_3");

		//delete package
		done(p_info);

		return 0;
	}

}