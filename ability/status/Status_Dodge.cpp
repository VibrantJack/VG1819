#pragma once
#include "ability/status/Status.h"
#include "unit/UnitCommon.h"
//Rock

namespace ability
{
	Status_Dodge::Status_Dodge() : Status::Status()
	{
		m_Id = STATUS_DODGE;
		m_statusType = StatusType::Shield;
		addTimePoint(TimePointEvent::Receive_Damage, -1);
		//endEffectAt(TimePointEvent::Turn_Start);
	}

	int Status_Dodge::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		if (p_type == ability::TimePointEvent::Receive_Damage)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAbilityInfo);
			AbilityInfoPackage* pack = p_event->getPackage(INFO_PACKAGE_KEY);
			//decrease the amount of damage it deals, means the result is 0
			int changedValue = -(pack->m_intValue[UNIT_POWER]);
			node->effect(pack, UNIT_POWER, changedValue);

			removeThis();//only effect onece
			return 0;
		}
		else
			checkDuration(p_type);

		return 1;
	}
}