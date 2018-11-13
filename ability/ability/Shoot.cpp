#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	Shoot::Shoot()
	{
	}

	Shoot::~Shoot()
	{
	}

	int Shoot::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//trigger deal damage event
			triggerTPEvent(ability::TimePointEvent::Deal_Damage, p_info->m_source, p_info);

			//trigger receive damage event
			unit::Unit* target = p_info->m_targets[0];
			triggerTPEvent(ability::TimePointEvent::Receive_Damage, target, p_info);

			//so power will change to negative
			int power = -(p_info->m_intValue.find(UNIT_POWER)->second);

			damage(target, power);
		}

		//delete package
		done(p_info);

		return 0;
	}

}