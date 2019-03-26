#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"

//Rock

namespace ability
{
	int Crash::effect(AbilityInfoPackage* p_info)
	{
		//power
		int pow = p_info->m_intValue[UNIT_POWER];

		//source unit hp
		unit::Unit* source = p_info->m_source;
		int hp = source->m_attributes[UNIT_HP];

		//doesn't have enough hp, then change power
		if (hp < pow)
		{
			p_info->m_intValue[UNIT_POWER] = hp;
			pow = hp;
		}

		//cost that much hp
		changeHP(source, -pow);

		//deal damage
		singleTargetDamage(p_info);

		UniversalSounds::playSound("monster_grunt");

		//done(p_info);

		return 0;
	}
}