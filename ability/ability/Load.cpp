#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"
#include "board/BoardManager.h"
//Rock

namespace ability
{
	void Load::applyStatus(AbilityInfoPackage * p_info)
	{
		//apply Status_Dodge to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_LOAD);

		//set properties
		se->addCounter(UNIT_DURATION, 1);
		se->setEffectedAD(ABILITY_FIRE);

		se->addAttributeChange(UNIT_POWER, p_info->m_intValue[UNIT_POWER]);
		se->addAttributeChange(AREA_MAX, p_info->m_intValue[AREA_MAX]);

		//attach to target
		se->attach(p_info->m_targets[0]);
	}

	Load::Load()
	{
	}

	Load::~Load()
	{
	}

	int Load::effect(AbilityInfoPackage* p_info)
	{
		//check if unit has this status
		if (!p_info->m_targets[0]->getStatusContainer()->getStatus(STATUS_LOAD))
			applyStatus(p_info);

		//delete package
		done(p_info);

		return 0;
	}

}