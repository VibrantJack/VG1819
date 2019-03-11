#pragma once
#include "ability/status/Status.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Status_Poison::Status_Poison() : Status::Status()
	{
		m_Id = STATUS_POISON;
		m_statusType = StatusType::Stat_Debuff;
		addTimePoint(TimePointEvent::Turn_Start);
	}

	int Status_Poison::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		if (p_type == ability::TimePointEvent::Turn_Start)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);

			//get power
			int power = -m_intValue[UNIT_POWER];

			//damage unit
			node->effect(m_unit, UNIT_HP, power);

			checkDuration();

			return 0;
		}

		return 1;
	}
}