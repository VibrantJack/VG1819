#pragma once
#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	Heal::Heal()
	{
	}

	Heal::~Heal()
	{
	}

	int Heal::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//trigger deal damage event
			triggerTPEvent(ability::TimePointEvent::Heal, p_info->m_source, p_info);

			//trigger receive damage event
			unit::Unit* target = p_info->m_targets[0];
			triggerTPEvent(ability::TimePointEvent::Receive_Heal, target, p_info);

			//heal target by power
			int power = p_info->m_intValue.find(UNIT_POWER)->second;

			//positive power = heal
			damage(target, power);
		}

		//delete package
		done(p_info);

		return 0;
	}

}
