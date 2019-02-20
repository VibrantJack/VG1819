#include "ability/status/Status.h"
#include "ability/AbilityMacro.h"
#include "unit/UnitCommon.h"

ability::Status_Attach::Status_Attach()
{
	m_Id = STATUS_ATTACH;
	addTimePoint(TimePointEvent::Unit_Destroy);
}

int ability::Status_Attach::effect()
{
	AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);
	
	//get power
	int pow = m_counter[UNIT_POWER];

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

int ability::Status_Attach::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event)
{
	if (p_type == TimePointEvent::Unit_Destroy)
	{
		//get lv
		int lv = m_counter[UNIT_LV];

		if (lv >= 3)
		{
			//TO DO: summon a new wraith
		}
	}
	return 0;
}
