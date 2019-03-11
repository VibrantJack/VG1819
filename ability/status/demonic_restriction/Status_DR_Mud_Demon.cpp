#include "Status_Demonic_Restriction.h"
#include "board/component/tilePipeline/TilePipeline.h"

namespace ability
{
	Status_DR_Mud_Demon::Status_DR_Mud_Demon() : Status_Demonic_Restriction::Status_Demonic_Restriction()
	{
		refreshOnTP(TimePointEvent::Level_Up);
	}

	void Status_DR_Mud_Demon::restrictionOn()
	{
		AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);

		//move reduce to 1
		int mv = m_unit->m_attributes[UNIT_BASE_MV];
		m_deltaMV = -(mv - 1); //reduced to 1

		node->effect(m_unit, UNIT_MV, m_deltaMV);

		//in -1
		int deltaIN = m_intValue[UNIT_IN];
		node->effect(m_unit, UNIT_IN, deltaIN);
	}

	void Status_DR_Mud_Demon::restrictionOff()
	{
		//change back
		AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);

		//move
		node->effect(m_unit, UNIT_MV, -m_deltaMV);

		//in +1
		int deltaIN = -(m_intValue[UNIT_IN]);
		node->effect(m_unit, UNIT_IN, deltaIN);
	}
}