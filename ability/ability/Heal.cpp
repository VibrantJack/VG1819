#pragma once
#include "Heal.h"

//Rock

namespace ability
{
	Heal::Heal()
	{
	}

	int Heal::effect(const AbilityInfoPackage* p_info)
	{
		//heal target by power
		unit::Unit* target = p_info->m_target;
		int power = p_info->m_power;

		AbilityNode* node1 = AbilityNodeManager::getInstance()->findNode("ChangeHPNode");

		node1->effect(target, power);

		return 0;
	}

}
