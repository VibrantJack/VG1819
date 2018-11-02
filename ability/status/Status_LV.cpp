#pragma once
#include "ability/status/Status.h"
//Rock

namespace ability
{
	Status_LV::Status_LV() : Status::Status()
	{
		
	}

	int Status_LV::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent * p_event)
	{
		int lv = p_event->getInt("lv");
		if (p_type == ability::TimePointEvent::Level_Up && lv >= m_LV)
		{
			//change attribute
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode("ChangeAttributeNode");
			for (auto it : *m_attributeChange)
			{
				node->effect(m_unit, it.first, it.second);
			}
			return 0;
		}
		return 1;
	}
}