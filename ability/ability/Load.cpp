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
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_AD_CHANGE);

		//status info
		std::vector<std::string> stringKeys;
		std::vector<std::string> intKeys;
		intKeys.push_back(UNIT_DURATION);

		readADChange(p_info, &intKeys, &stringKeys);

		addStatusInfo(se, p_info, intKeys,stringKeys);

		se->endEffectAt(TimePointEvent::Deal_Damage);

		/*
		//set properties
		addStatusInfo(se, p_info);

		se->addCounter(UNIT_DURATION, 1);
		se->setEffectedAD(ABILITY_FIRE);

		se->addAttributeChange(UNIT_POWER, p_info->m_intValue[UNIT_POWER]);
		se->addAttributeChange(AREA_MAX, p_info->m_intValue[AREA_MAX]);

		se->m_source = ABILITY_LOAD;*/


		//attach to target
		se->attach(p_info->m_targets[0]);
	}

	int Load::effect(AbilityInfoPackage* p_info)
	{
		//check if unit has this status
		if (!p_info->m_targets[0]->getStatusContainer()->getStatus(STATUS_LOAD,ABILITY_LOAD))
			applyStatus(p_info);

		UniversalSounds::playSound("load");

		//delete package
		done(p_info);

		return 0;
	}

}