#pragma once
#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	int Invest::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			AbilityNode* node1 = AbilityNodeManager::getInstance()->findNode(ChangeAttribute);

			unit::Unit* target = p_info->m_targets[0];
			int power = p_info->m_intValue[UNIT_POWER];

			int limit = p_info->m_intValue[COUNTER_MAX];
			int counter = target->m_attributes[COUNTER_MONEY];

			if (counter + power > limit)
			{
				power = limit - counter;
				if (power < 0)
					power = 0;
			}

			//change counter
			node1->effect(target, COUNTER_MONEY, power);
		}

		//delete package
		done(p_info);

		return 0;
	}
}