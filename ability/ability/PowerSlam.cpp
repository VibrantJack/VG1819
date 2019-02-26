#pragma once
#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	int PowerSlam::effect(AbilityInfoPackage* p_info)
	{
		//deal damaga to all units

		//change power
		int powerFactor = p_info->m_intValue[COUNTER_POWER];
		int counter = p_info->m_intValue[COUNTER_ENERGY];
		p_info->m_intValue[UNIT_POWER] = powerFactor * counter;

		//remove counter
		changeCounter(p_info->m_source, COUNTER_ENERGY, -counter);

		//get target (this is CT ability)
		getTarget(p_info);

		multiTargetDamage(p_info);

		/*
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

		//delete package
		done(p_info);*/

		return 0;
	}
}