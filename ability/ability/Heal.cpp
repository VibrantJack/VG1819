#pragma once
#include "ability/ability/Ability.h"

//Rock

namespace ability
{
	Heal::Heal()
	{
	}

	int Heal::effect(const AbilityInfoPackage* p_info)
	{
		//heal target by power
		int power = p_info->m_intValue.find("power")->second;

		for (unit::Unit* target : p_info->m_multipleTargets)
		{
			//positive power = heal
			damage(target, power);
		}

		return 0;
	}

}
