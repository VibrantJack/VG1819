#pragma once
#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	int Drain::effect(AbilityInfoPackage* p_info)
	{

		unit::Unit* source = p_info->m_source;

		//deal damage to target

		//trigger deal damage event
		triggerTPEvent(ability::TimePointEvent::Deal_Damage, source, p_info);
		//trigger receive damage event
		unit::Unit* target = p_info->m_targets[0];
		triggerTPEvent(ability::TimePointEvent::Receive_Damage, target, p_info);
		//so power will change to negative
		int power = -(p_info->m_intValue.find(UNIT_POWER)->second);

		changeHP(target, power);
		
		//gain vigor counter
		int delta = p_info->m_intValue[COUNTER_CHANGE];
		changeCounter(source, COUNTER_VIGOR, delta);

		//check counter
		int counter = source->m_attributes[COUNTER_VIGOR];
		int max = p_info->m_intValue[COUNTER_MAX];
		if (counter >= max)//reach max
		{
			//lv up
			source->levelup();
			//reduce counter to 0
			changeCounter(source, COUNTER_VIGOR, -counter);
		}

		done(p_info);

		return 0;
	}
}