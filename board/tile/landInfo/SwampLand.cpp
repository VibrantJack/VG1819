#include "board/tile/landInfo/LandInformation.h"
#include "ability/node/AbilityNodeManager.h"

void SwampLand::effectOnStay(unit::Unit* p_unit)
{
	//damage unit by 1

	ability::AbilityNode* node1 = ability::AbilityNodeManager::getInstance()->findNode(ability::ChangeAttribute);
	ability::AbilityNode* node2 = ability::AbilityNodeManager::getInstance()->findNode(ability::CheckHP);

	//change hp
	node1->effect(p_unit, UNIT_HP, -1);
	//then check hp
	node2->effect(p_unit);
}