#pragma once
#include "ability/status/Status.h"
#include "unit/UnitCommon.h"
//Rock

namespace ability
{
	Status_Block::Status_Block() : Status::Status()
	{
		m_Id = STATUS_BLOCK;
		m_statusType = StatusType::Shield;
		addTimePoint(TimePointEvent::Receive_Damage);
	}

	int Status_Block::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		if (p_type == ability::TimePointEvent::Receive_Damage)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAbilityInfo);
			AbilityInfoPackage* pack = p_event->getPackage(INFO_PACKAGE_KEY);
			node->effect(pack, UNIT_POWER, -m_intValue.at(UNIT_POWER));//reduce damage
			return 0;
		}
		return 1;
	}
}
