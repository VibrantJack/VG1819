#pragma once
#include "ability/status/statusLV/Status_LV.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Status_Archer_LV3::Status_Archer_LV3() : Status_LV::Status_LV()
	{
		m_Id = STATUS_ARCHER_LV3;
		//addTimePoint(TimePointEvent::Level_Up);
	}

	int Status_Archer_LV3::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		if (Status_LV::effect(p_type, p_event) == 0)
		{
			changeEffectedAD();
			/*
			AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);
			for (auto it : m_effectedAD)
			{
				for (auto attr : it.second)
				{
					node->effect(m_unit, it.first, attr.first, attr.second);
				}
			}*/
			return 0;
		}
		return 1;
	}
}