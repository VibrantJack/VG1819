#pragma once
#include "ability/status/Status.h"

//Rock

namespace ability
{
	Status_Encourage::Status_Encourage()
	{

	}

	int Status_Encourage::effect(TimePointEvent p_timePoint)
	{
		if (p_timePoint == ability::Turn_End)
		{
			//reduce duration
			m_counter["duration"] -= 1;
			if (m_counter["duration"] <= 0)
				removeThis();
		}
		return 0;
	}

	int Status_Encourage::effect(TimePointEvent p_timePoint, ability::AbilityInfoPackage * p_pack)
	{
		if (p_timePoint == ability::Deal_Damage)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode("ChangeAbilityInfoNode");
			node->effect(p_pack, "power" , m_counter["power"]);
		}
		return 0;
	}
}