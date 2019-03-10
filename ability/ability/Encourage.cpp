#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"

//Rock

namespace ability
{
	void Encourage::applyStatus(AbilityInfoPackage* p_info)
	{
		//apply Status_Encourage to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_ENCOURAGE);

		//set properties
		addStatusInfo(se, p_info);

		int dur = p_info->m_intValue.find(UNIT_DURATION)->second;
		int pow = p_info->m_intValue.find(UNIT_POWER)->second;

		se->addCounter(UNIT_DURATION, dur);
		se->addCounter(UNIT_POWER, pow);
		se->m_source = ABILITY_ENCOURAGE;
		//attach to target
		se->attach(p_info->m_targets[0]);
		glm::vec3 test = p_info->m_targets[0]->getTransform().getTranslation();
	}

	void Encourage::stackStatus( AbilityInfoPackage* p_info)
	{
		ability::Status* se = p_info->m_targets[0]->getStatusContainer()->getStatus(STATUS_ENCOURAGE, ABILITY_ENCOURAGE);
		//reset duration
		int dur = p_info->m_intValue.find(UNIT_DURATION)->second;
		se->addCounter(UNIT_DURATION, dur);
	}

	int Encourage::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//check if unit has this status
			if (p_info->m_targets[0]->getStatusContainer()->getStatus(STATUS_ENCOURAGE, ABILITY_ENCOURAGE))
				stackStatus(p_info);
			else
				applyStatus(p_info);
		}

		//delete package
		done(p_info);

		return 0;
	}

}