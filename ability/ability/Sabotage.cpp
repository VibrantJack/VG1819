#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Sabotage::Sabotage()
	{
	}

	Sabotage::~Sabotage()
	{
	}

	int Sabotage::effect(const AbilityInfoPackage* p_info)
	{
		//damage target by power
		unit::Unit* target = p_info->m_target;

		for (auto it : target->m_tags)
		{
			if (it == "Structure")
			{
				//TO DO:send receive damage event to target

				int power = -(p_info->m_intValue.find("power")->second);

				damage(target, power);

				return 0;
			}
		}
		
		//target isn't structure
		return 1;
	}

}