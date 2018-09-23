#include "ability/ability/Ability.h"

//Rock

namespace ability
{
	Fight::Fight()
	{
	}

	int Fight::effect(const AbilityInfoPackage* p_info)
	{
		//damage target by power
		unit::Unit* target = p_info->m_target;
		//so power will change to negative
		int power = -(p_info->m_intValue.find("power")->second);

		AbilityNode* node1 = AbilityNodeManager::getInstance()->findNode("ChangeAttributeNode");
		AbilityNode* node2 = AbilityNodeManager::getInstance()->findNode("CheckHPNode");

		//change hp
		node1->effect(target, "HP", power);
		//then check hp
		node2->effect(target);

		return 0;
	}

}
