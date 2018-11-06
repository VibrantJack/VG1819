#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Fight::Fight()
	{
	}

	Fight::~Fight()
	{
	}

	int Fight::effect(AbilityInfoPackage* p_info)
	{
		//damage target by power
		if (checkTarget(p_info))
		{
			//trigger deal damage event
			triggerTPEvent(ability::TimePointEvent::Deal_Damage, p_info->m_source, p_info);

			//trigger receive damage event
			unit::Unit* target = p_info->m_targets[0];
			triggerTPEvent(ability::TimePointEvent::Receive_Damage, target, p_info);

			//so power will change to negative
			int power = -(p_info->m_intValue.find("power")->second);

			damage(target, power);
		}

		//delete package
		done(p_info);

		return 0;
	}

}
