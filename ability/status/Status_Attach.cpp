#include "ability/status/Status.h"
#include "ability/AbilityMacro.h"
#include "unit/UnitCommon.h"
#include "unit/UnitSpawn.h"
#include "unit/unitComponent/UnitMove.h"
#include "networking/ClientGame.h"

ability::Status_Attach::Status_Attach()
{
	m_Id = STATUS_ATTACH;
	//addTimePoint(TimePointEvent::Unit_Destroy);
}

int ability::Status_Attach::effect()
{
	AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);
	
	//get power
	int pow = m_intValue[UNIT_POWER];

	if (pow > 0)//positive
	{//change max hp then hp
		node->effect(m_unit, UNIT_MAX_HP, pow);
		node->effect(m_unit, UNIT_HP, pow);
	}
	else//negative
	{
		//change hp then max hp
		node->effect(m_unit, UNIT_HP, pow);
		node->effect(m_unit, UNIT_MAX_HP, pow);
	}
	return 0;
}
