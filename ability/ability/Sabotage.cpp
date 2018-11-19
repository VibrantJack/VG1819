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

	int Sabotage::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//damage target by power

			//trigger deal damage event
			triggerTPEvent(ability::TimePointEvent::Deal_Damage, p_info->m_source, p_info);

			unit::Unit* target = p_info->m_targets[0];

			for (std::string it : target->m_tags)
			{
				if (it == STRUCTURE)
				{
					triggerTPEvent(ability::TimePointEvent::Receive_Damage, target, p_info);

					int power = -(p_info->m_intValue.find(UNIT_POWER)->second);

					damage(target, power);

					return 0;
				}
			}
		}

		//delete package
		done(p_info);
		
		//target isn't structure
		return 1;
	}

}