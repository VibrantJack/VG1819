#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	QuickShoot::QuickShoot()
	{
	}

	QuickShoot::~QuickShoot()
	{
	}

	int QuickShoot::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//deal damaga to all units

			//trigger deal damage event
			triggerTPEvent(ability::TimePointEvent::Deal_Damage, p_info->m_source, p_info);


			for (unit::Unit* u : p_info->m_targets)
			{
				//get copy of package
				AbilityInfoPackage* clonePackage = new AbilityInfoPackage(*p_info);

				//trigger receive damage
				triggerTPEvent(ability::TimePointEvent::Receive_Damage, u, clonePackage);

				int power = -(clonePackage->m_intValue.find("power")->second);

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