#include "Status_Demonic_Restriction.h"

#include "ability/AbilityMacro.h"
#include "unit/UnitCommon.h"

namespace ability
{
	Status_DR_Gorefiend::Status_DR_Gorefiend() : Status_Demonic_Restriction::Status_Demonic_Restriction()
	{
	}

	void Status_DR_Gorefiend::restrictionOn()
	{
		changeEffectedAD();
	}

	void Status_DR_Gorefiend::restrictionOff()
	{
		//change back

		AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);

		//enable Horror

		//Execute get original kill counter
	}
}