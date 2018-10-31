#include "ability/ability/Ability.h"

//Rock

namespace ability
{
	Slay::Slay()
	{
	}

	Slay::~Slay()
	{
	}

	int Slay::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//deal damaga to all units

			int power = -(p_info->m_intValue.find("power")->second);

			for (unit::Unit* u : p_info->m_targets)
			{
				//TO DO:send receive damage event to target

				damage(u, power);
			}
		}

		//delete package
		done(p_info);

		return 0;
	}

}