#include "Status_Demonic_Restriction.h"

#include "ability/AbilityMacro.h"
#include "unit/UnitCommon.h"

namespace ability
{
	Status_DR_Evil_Fiend::Status_DR_Evil_Fiend() : Status_Demonic_Restriction::Status_Demonic_Restriction()
	{
	}

	void Status_DR_Evil_Fiend::restrictionOn()
	{
		AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);

		//disable Horror

		//Execute get less kill counter
	}

	void Status_DR_Evil_Fiend::restrictionOff()
	{
		//change back

		AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);

		//enable Horror

		//Execute get original kill counter
	}
}