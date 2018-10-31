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
		if (checkTarget(p_info))
		{
			//damage target by power
			unit::Unit* target = p_info->m_targets[0];

			for (auto it : target->m_tags)
			{
				if (it == "Structure")
				{
					//TO DO:send receive damage event to target

					int power = -(p_info->m_intValue.find("power")->second);

					damage(target, power);

					//delete package
					delete p_info;

					return 1;
				}
			}
		}

		//delete package
		done(p_info);
		
		//target isn't structure
		return 0;
	}

}