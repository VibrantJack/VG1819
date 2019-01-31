#pragma once
#include "ability/status/Status.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Status_Eternal_Eye_LV3::Status_Eternal_Eye_LV3() : Status_LV::Status_LV()
	{
		m_Id = STATUS_ETERNAL_EYE_LV3;
		addTimePoint(TimePointEvent::Level_Up);
	}

	int Status_Eternal_Eye_LV3::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		if (Status_LV::effect(p_type, p_event) == 0)
		{
			AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);

			node->effect(m_unit, ABILITY_CURSE, UNIT_POWER, 2);//increase damage by 2
			node->effect(m_unit, ABILITY_OPPOSE, PUSH_BACK, 1);//oppose push back 1 more blocks

			return 0;
		}
		return 1;
	}
}