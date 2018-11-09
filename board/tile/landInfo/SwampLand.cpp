#include "board/tile/landInfo/LandInformation.h"
#include "ability/node/AbilityNodeManager.h"

void SwampLand::effectOnStay(unit::Unit* p_unit)
{
	//damage unit by 1

	ability::AbilityNode* node1 = ability::AbilityNodeManager::getInstance()->findNode("ChangeAttributeNode");
	ability::AbilityNode* node2 = ability::AbilityNodeManager::getInstance()->findNode("CheckHPNode");

	//change hp
	node1->effect(p_unit, "hp", -1);
	//then check hp
	node2->effect(p_unit);
}