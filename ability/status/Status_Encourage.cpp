#pragma once
#include "ability/status/Status.h"
#include "unit/UnitCommon.h"
//Rock

namespace ability
{
	Status_Encourage::Status_Encourage() : Status::Status()
	{
		m_name = STATUS_ENCOURAGE;
		addTimePoint(TimePointEvent::Turn_End);
		addTimePoint(TimePointEvent::Deal_Damage);
	}

	int Status_Encourage::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent * p_event)
	{
		if (p_type == ability::TimePointEvent::Turn_End)
		{
			//reduce duration
			changeCounter();
			return 0;
		}
		else if (p_type == ability::TimePointEvent::Deal_Damage)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAbilityInfo);
			AbilityInfoPackage* pack = p_event->getPackage(INFO_PACKAGE_KEY);
			node->effect(pack, UNIT_POWER, m_counter.at(UNIT_POWER));
			return 0;
		}
		return 1;
	}
}