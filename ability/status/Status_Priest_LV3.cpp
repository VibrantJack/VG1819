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
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);

			int power = m_unit->m_ADList[ABILITY_HEAL]->m_intValue[UNIT_POWER];

			node->effect(m_unit, UNIT_HP, power);
			return 0;
		}
		else if (!m_activate)
		{
			if (Status_LV::effect(p_type, p_event) == 0)
			{
				m_activate = true;

				addTimePoint(TimePointEvent::Turn_End);

				unit::StatusContainer* sc = m_unit->getStatusContainer();
				sc->registerTP(TimePointEvent::Turn_End, this);

				return 0;
			}
		}
		return 1;
	}
}