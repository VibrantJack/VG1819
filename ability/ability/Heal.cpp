#pragma once
#include "ability/ability/Ability.h"

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
			//heal target by power
			int power = p_info->m_intValue.find("power")->second;

			for (unit::Unit* target : p_info->m_targets)
			{
				//positive power = heal
				damage(target, power);
			}
		}

		//delete package
		done(p_info);

		return 0;
	}

}
