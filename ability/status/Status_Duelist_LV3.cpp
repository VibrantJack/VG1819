#pragma once
#include "ability/status/Status.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Status_Duelist_LV3::Status_Duelist_LV3()
	{

	}

	int Status_Duelist_LV3::effect(TimePointEvent p_timePoint, int p_value)
	{
		if (Status_LV::effect(p_timePoint, p_value) == 0)
		{
			AbilityNode* node = AbilityNodeManager::getInstance()->findNode("ChangeAbilityDescriptionNode");

			node->effect(m_unit, "Slay", "power", 2);
			node->effect(m_unit, "Dodge", "CD", -1);

			return 0;
		}
		return 1;
	}
}