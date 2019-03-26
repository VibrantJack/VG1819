#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"

//Rock

namespace ability
{
	int Brew::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//change counter
			unit::Unit* target = p_info->m_targets[0];
			int power = p_info->m_intValue[COUNTER_CHANGE];
			std::string name = p_info->m_stringValue[COUNTER_NAME];
			changeCounter(target, name, power);
		}

		done(p_info);

		UniversalSounds::playSound("bubbling");

		return 0;
	}
}