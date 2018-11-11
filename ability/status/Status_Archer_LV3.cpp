#pragma once
#include "ability/status/Status.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Status_Archer_LV3::Status_Archer_LV3() : Status_LV::Status_LV()
	{

	}

	int Status_Archer_LV3::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent * p_event)
	{
		if (Status_LV::effect(p_type, p_event) == 0)
		{
			AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);

			node->effect(m_unit, ABILITY_QUICK_SHOOT, "target", 1);//increase target num by 1
			node->effect(m_unit, ABILITY_QUICK_SHOOT, "description", "Deal 2 damage three times.");//change description

			return 0;
		}
		return 1;
	}
}