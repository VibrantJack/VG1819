#pragma once
#include "ability/status/Status.h"
#include "unit/UnitCommon.h"
//Rock

namespace ability
{
	Status_Encourage::Status_Encourage() : Status::Status()
	{
		m_Id = STATUS_ENCOURAGE;
		m_statusType = StatusType::Stat_Buff;
		endEffectAt();
		addTimePoint(TimePointEvent::Deal_Damage);
	}

	int Status_Encourage::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		if (p_type == ability::TimePointEvent::Deal_Damage)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAbilityInfo);
			AbilityInfoPackage* pack = p_event->getPackage(INFO_PACKAGE_KEY);
			node->effect(pack, UNIT_POWER, m_intValue.at(UNIT_POWER));
			return 0;
		}
		else
			checkDuration(p_type);

		return 1;
	}
}