#pragma once
#include "ability/status/statusLV/Status_LV.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Status_Wraith_LV2::Status_Wraith_LV2() : Status_LV::Status_LV()
	{
		m_Id = STATUS_WRAITH_LV2;
		//addTimePoint(TimePointEvent::Level_Up);
	}

	int Status_Wraith_LV2::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		if (Status_LV::effect(p_type, p_event) == 0)
		{
			changeEffectedAD();
			
			/*
			AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);

			//get power change
			int pow = m_intValue[UNIT_POWER];

			node->effect(m_unit, ABILITY_ATTACH, UNIT_POWER, pow);//increase power by 3 / double effect
			*/
			return 0;
		}
		return 1;
	}
}