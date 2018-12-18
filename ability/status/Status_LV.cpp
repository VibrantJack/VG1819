#pragma once
#include "ability/status/Status.h"
#include "unit/UnitCommon.h"
//Rock

namespace ability
{
	Status_LV::Status_LV() : Status::Status()
	{
		m_name = STATUS_LV;
		addTimePoint(TimePointEvent::Level_Up);
	}

	int Status_LV::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent * p_event)
	{
		int lv = p_event->getInt(UNIT_LV);
		if (p_type == ability::TimePointEvent::Level_Up && lv == m_LV)
		{
			//change attribute
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);
			for (auto it : m_attributeChange)
			{
				node->effect(m_unit, it.first, it.second);
			}
			return 0;
		}
		return 1;
	}
}