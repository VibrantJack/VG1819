#pragma once
#include "ability/status/Status.h"
//Rock

namespace ability
{
	int Status_LV::effect(TimePointEvent p_timePoint, int p_value)
	{
		if (p_timePoint == ability::Level_Up && p_value >= m_LV)
		{
			//change attribute
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode("ChangeAttributeNode");
			for (auto it : m_attributeChange)
			{
				node->effect(m_unit, it.first, it.second);
			}
			return 0;
		}
		return 1;
	}
}