#include "Status_Demonic_Restriction.h"

#include "unit/UnitCommon.h"

namespace ability
{
	Status_DR_Wraith::Status_DR_Wraith() : Status_Demonic_Restriction::Status_Demonic_Restriction()
	{
	}

	void Status_DR_Wraith::restrictionOn()
	{
		AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);

		//in -8
		int delta = m_intValue[UNIT_IN];
		node->effect(m_unit, UNIT_IN, delta);
	}

	void Status_DR_Wraith::restrictionOff()
	{
		//change back
		AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);

		//in +8
		int delta = -(m_intValue[UNIT_IN]);
		node->effect(m_unit, UNIT_IN, delta);
	}
}