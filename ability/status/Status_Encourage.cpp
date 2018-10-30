#pragma once
#include "ability/status/Status.h"

//Rock

namespace ability
{
	Status_Encourage::Status_Encourage() : Status::Status()
	{

	}

	int Status_Encourage::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent * p_event)
	{
		if (p_type == ability::TimePointEvent::Turn_End)
		{
			//reduce duration
			changeCounter();
			checkDuration();
			return 0;
		}
		else if (p_type == ability::TimePointEvent::Deal_Damage)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode("ChangeAbilityInfoNode");
			AbilityInfoPackage* pack = p_event->getPackage("info");
			node->effect(pack, "power", m_counter->at("power"));
			return 0;
		}
		return 1;
	}
}