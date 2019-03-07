#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	int ToxicAura::effect(AbilityInfoPackage* p_info)
	{
		//get duration increase
		int dur = p_info->m_intValue[UNIT_DURATION];

		//check if unit has this status
		for (unit::Unit* u : p_info->m_targets)
		{
			Status* s = u->getStatusContainer()->getStatus(STATUS_POISON);
			if (s != nullptr)
			{
				s->m_intValue[UNIT_DURATION] += dur;
			}
		}

		//delete package
		done(p_info);

		return 0;
	}

}