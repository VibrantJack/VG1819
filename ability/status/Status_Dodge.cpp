#pragma once
#include "ability/status/Status.h"

//Rock

namespace ability
{
	Status_Dodge::Status_Dodge() : Status::Status()
	{

	}

	int Status_Dodge::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent * p_event)
	{
		if (p_type == ability::TimePointEvent::Turn_Start)
		{
			//reduce duration
			changeCounter();
			checkDuration();
			return 0;
		}
		else if (p_type == ability::TimePointEvent::Receive_Damage)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode("ChangeAbilityInfoNode");
			AbilityInfoPackage* pack = p_event->getPackage(INFO_PACKAGE_KEY);
			//decrease the amount of damage it deals, means the result is 0
			int changedValue = -(pack->m_intValue["power"]);
			node->effect(pack, "power", changedValue);
			return 0;
		}
		return 1;
	}
}