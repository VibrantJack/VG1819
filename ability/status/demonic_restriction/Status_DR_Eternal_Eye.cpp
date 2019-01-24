#include "Status_Demonic_Restriction.h"
#include "board/component/tilePipeline/TilePipeline.h"

namespace ability
{
	Status_DR_Eternal_Eye::Status_DR_Eternal_Eye() : Status_Demonic_Restriction::Status_Demonic_Restriction()
	{
	}

	void Status_DR_Eternal_Eye::restrictionOn()
	{
		AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);
		ChangeAbilityDescriptionNode* cadNode = static_cast<ChangeAbilityDescriptionNode*>(node);

		cadNode->addFilter(m_unit, ABILITY_OPPOSE, FILTER, FILTER_NOT_DP);
		//oppose can not use on unit that's not on dp 
	}

	void Status_DR_Eternal_Eye::restrictionOff()
	{
		//change back

		AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);
		ChangeAbilityDescriptionNode* cadNode = static_cast<ChangeAbilityDescriptionNode*>(node);

		cadNode->removeFilter(m_unit, ABILITY_OPPOSE, FILTER, FILTER_NOT_DP);
		//oppose can use on unit that's not on dp 
	}
}