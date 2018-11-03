#include "Ability.h"

int ability::Ability::damage(unit::Unit* p_target, int power)
{
	AbilityNode* node1 = AbilityNodeManager::getInstance()->findNode("ChangeAttributeNode");
	AbilityNode* node2 = AbilityNodeManager::getInstance()->findNode("CheckHPNode");

	//change hp
	node1->effect(p_target, "HP", power);
	//then check hp
	node2->effect(p_target);

	return 0;
}
