#pragma once
#include "ability/status/Status.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Status_Priest_LV3::Status_Priest_LV3() : Status_LV::Status_LV()
	{

	}

	int Status_Priest_LV3::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent * p_event)
	{
		if (p_type == ability::TimePointEvent::Turn_End && m_activate)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode("ChangeAttributeNode");

			int power = m_unit->m_ADList["Heal"]->m_intValue["power"];

			node->effect(m_unit, "HP", power);
			return 0;
		}
		else if (!m_activate)
		{
			if (Status_LV::effect(p_type, p_event) == 0)
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