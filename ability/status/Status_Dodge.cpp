#pragma once
#include "ability/status/Status.h"

//Rock

namespace ability
{
	Status_Dodge::Status_Dodge()
	{

	}

	Status_Dodge::~Status_Dodge()
	{
	}

	int Status_Dodge::effect(TimePointEvent p_timePoint)
	{
		if (p_timePoint == ability::Turn_Start)
		{
			//reduce duration
			changeCounter();
			checkDuration();
		}
		return 0;
	}

	int Status_Dodge::effect(TimePointEvent p_timePoint, ability::AbilityInfoPackage * p_pack)
	{
		if (p_timePoint == ability::Receive_Damage)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode("ChangeAbilityInfoNode");
			int changedValue = - (p_pack->m_intValue["power"]);
			node->effect(p_pack, "power", changedValue);
		}
		return 0;
	}
}