#pragma once
#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	int Execute::effect(AbilityInfoPackage* p_info)
	{
		//deal damage to target

		//get counter name
		std::string name = p_info->m_stringValue[COUNTER_NAME];

		//get lv
		int lv = p_info->m_source->m_attributes[UNIT_LV];
		if (lv >= 3)
		{//get kill counter
			int powerFactor = p_info->m_intValue[COUNTER_POWER];

			int counter = p_info->m_intValue[name];

			//add to damage
			p_info->m_intValue[UNIT_POWER] += counter * powerFactor;
		}

		//single target damage
		//trigger deal damage event
		triggerTPEvent(ability::TimePointEvent::Deal_Damage, p_info->m_source, p_info);

		//trigger receive damage event
		unit::Unit* target = p_info->m_targets[0];
		triggerTPEvent(ability::TimePointEvent::Receive_Damage, target, p_info);

		//so power will change to negative
		int power = -(p_info->m_intValue.find(UNIT_POWER)->second);

		changeHP(target, power);


		//check if target dies
		if (target->m_attributes[UNIT_HP] <= 0)
		{//add kill counter
			int delta = p_info->m_intValue[COUNTER_CHANGE];
			changeCounter(p_info->m_source, name, delta);
		}

		UniversalSounds::playSound("execute");

		done(p_info);

		return 0;
	}
}