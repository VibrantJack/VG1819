#pragma once
#include "ability/status/Status.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Status_Archer_LV3::Status_Archer_LV3()
	{

	}

	int Status_Archer_LV3::effect(TimePointEvent p_timePoint, int p_value)
	{
		if (Status_LV::effect(p_timePoint, p_value) == 0)
		{
			AbilityNode* node = AbilityNodeManager::getInstance()->findNode("ChangeAbilityDescriptionNode");

			node->effect(m_unit,"QuickShoot","target",1);
			node->effect(m_unit, "QuickShoot", "description", "Deal 2 damage three times.");

			return 0;
		}
		return 1;
	}
}