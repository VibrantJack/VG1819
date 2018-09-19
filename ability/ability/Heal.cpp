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

		AbilityNode* node1 = AbilityNodeManager::getInstance()->findNode("ChangeAttributeNode");
		AbilityNode* node2 = AbilityNodeManager::getInstance()->findNode("CheckHPNode");

		//change hp
		node1->effect(target, "HP", power);
		//then check hp
		node2->effect(target);

		return 0;
	}

}
