#pragma once
#include "ability/status/statusLV/Status_LV.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Status_Gorefiend_LV3::Status_Gorefiend_LV3() : Status_LV::Status_LV()
	{
		m_Id = STATUS_GOREFIEND_LV3;
		//addTimePoint(TimePointEvent::Level_Up);
	}

	int Status_Gorefiend_LV3::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		if (Status_LV::effect(p_type, p_event) == 0)
		{
			changeEffectedAD();
			/*
			AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);

			node->effect(m_unit, ABILITY_HEALTH_LINK, UNIT_POWER, 1);
			node->effect(m_unit, ABILITY_CRASH, UNIT_POWER, 10);*/

			return 0;
		}
		return 1;
	}
}