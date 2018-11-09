#include "ability/ability/Ability.h"

#include "unit/Unit.h"

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
			//trigger deal damage event
			triggerTPEvent(ability::TimePointEvent::Deal_Damage, p_info->m_source, p_info);

			//deal damaga to all units
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
		}

		//delete package
		done(p_info);

		return 0;
	}

}