#pragma once
#include "ability/status/Status.h"
#include "unit/UnitCommon.h"
//Rock

namespace ability
{
	Status_Dodge::Status_Dodge() : Status::Status()
	{
		m_name = STATUS_DODGE;
		addTimePoint(TimePointEvent::Turn_Start);
		addTimePoint(TimePointEvent::Receive_Damage);
	}

	int Status_Dodge::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent * p_event)
	{
		if (p_type == ability::TimePointEvent::Turn_Start)
		{
			//reduce duration
			changeCounter();
			return 0;
		}
		else if (p_type == ability::TimePointEvent::Receive_Damage)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAbilityInfo);
			AbilityInfoPackage* pack = p_event->getPackage(INFO_PACKAGE_KEY);
			//decrease the amount of damage it deals, means the result is 0
			int changedValue = -(pack->m_intValue[UNIT_POWER]);
			node->effect(pack, UNIT_POWER, changedValue);

			removeThis();//only effect onece
			return 0;
		}
		return 1;
	}
}