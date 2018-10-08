#pragma once
#include "ability/status/Status.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Status_Priest_LV3::Status_Priest_LV3()
	{

	}

	int Status_Priest_LV3::effect(TimePointEvent p_timePoint)
	{
		//unit is lv3, Heal self at the end of turn.
		if (m_activate && p_timePoint == ability::Turn_End)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode("ChangeAttributeNode");

			int power = m_unit->m_ADList["Heal"]->m_intValue["power"];

			node->effect(m_unit,"HP",power);
			return 0;
		}
		
		return 1;
	}

	int Status_Priest_LV3::effect(TimePointEvent p_timePoint, int p_value)
	{
		//not activate, level up to 3, then activate this status
		if (!m_activate)
		{
			if (Status_LV::effect(p_timePoint, p_value) == 0)
			{
				m_activate = true;

				//TO DO:register turn end event
				//TO DO:unregister level up event

				return 0;
			}
		}
		return 1;
	}
}