#include "Status_Demonic_Restriction.h"

#include "ability/AbilityMacro.h"
#include "unit/UnitCommon.h"

namespace ability
{
	Status_DR_Horror_Lord::Status_DR_Horror_Lord() : Status_Demonic_Restriction::Status_Demonic_Restriction()
	{
	}

	void Status_DR_Horror_Lord::restrictionOn()
	{
		changeEffectedAD();
		/*
		AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);

		//disable Horror
		node->effect(m_unit, ABILITY_HORROR, ABILITY_DISABLE, 1);

		//Execute get less kill counter
		node->effect(m_unit, ABILITY_EXECUTE, COUNTER_CHANGE, -1);*/
	}

	void Status_DR_Horror_Lord::restrictionOff()
	{
		changeEffectedAD(true);
		/*
		//change back

		AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);

		//enable Horror
		node->effect(m_unit, ABILITY_HORROR, ABILITY_DISABLE, -1);

		//Execute get original kill counter
		node->effect(m_unit, ABILITY_EXECUTE, COUNTER_CHANGE, 1);*/
	}

	int Status_DR_Horror_Lord::effect()
	{
		setEffectedAD();
		return 0;
	}
}