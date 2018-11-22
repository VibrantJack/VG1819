#pragma once
#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	int PowerOfMoney::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//deal damaga to all units

			//change power
			int powerFactor = p_info->m_intValue[UNIT_POWER];
			int counter = p_info->m_intValue[COUNTER_MONEY];
			p_info->m_intValue[UNIT_POWER] = powerFactor * counter;

			//trigger deal damage event
			triggerTPEvent(ability::TimePointEvent::Deal_Damage, p_info->m_source, p_info);

			for (unit::Unit* u : p_info->m_targets)
			{
				//get copy of package
				AbilityInfoPackage* clonePackage = new AbilityInfoPackage(*p_info);

				//trigger receive damage
				triggerTPEvent(ability::TimePointEvent::Receive_Damage, u, clonePackage);

				int power = -(clonePackage->m_intValue.find(UNIT_POWER)->second);

				damage(u, power);

				//delete clone
				delete clonePackage;
			}
		}

		//delete package
		done(p_info);

		return 0;
	}
}