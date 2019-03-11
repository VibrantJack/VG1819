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

		std::vector<std::string> intKeys;
		intKeys.push_back(UNIT_POWER);
		intKeys.push_back(UNIT_DURATION);

		addStatusInfo(se, p_info, intKeys);

		/*
		//set properties
		addStatusInfo(se, p_info);

		int dur = p_info->m_intValue.find(UNIT_DURATION)->second;
		int pow = p_info->m_intValue.find(UNIT_POWER)->second;

		se->addCounter(UNIT_DURATION, dur);
		se->addCounter(UNIT_POWER, pow);
		se->m_source = ABILITY_ENCOURAGE;*/

		//attach to target
		se->attach(p_info->m_targets[0]);
		glm::vec3 test = p_info->m_targets[0]->getTransform().getTranslation();
		UniversalPfx::getInstance()->playEffect("Encourage", p_info->m_targetTilesGO[0]->getTransform().getTranslation());

	}

	void Encourage::stackStatus( AbilityInfoPackage* p_info)
	{
		ability::Status* se = p_info->m_targets[0]->getStatusContainer()->getStatus(STATUS_ENCOURAGE, ABILITY_ENCOURAGE);
		//reset duration
		int dur = p_info->m_intValue.find(UNIT_DURATION)->second;
		se->m_intValue[UNIT_DURATION] = dur;
		UniversalPfx::getInstance()->playEffect("Encourage", p_info->m_targetTilesGO[0]->getTransform().getTranslation());

	}

	int Encourage::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//check if unit has this status
			if (p_info->m_targets[0]->getStatusContainer()->getStatus(STATUS_ENCOURAGE, ABILITY_ENCOURAGE))
			{
				stackStatus(p_info);
			}
			else
			{
				applyStatus(p_info);
			}
			
			UniversalSounds::playSound("marimba");

		}

		//delete package
		done(p_info);

		return 0;
	}

}