#include "ability/status/Status.h"
#include "ability/AbilityMacro.h"

ability::Status_Temp_Change::Status_Temp_Change()
{
	m_Id = STATUS_TEMP_CHANGE;
	endEffectAt();
}

int ability::Status_Temp_Change::effect()
{
	AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);
	for (auto it : m_attributeChange)
	{
		node->effect(m_unit, it.first, it.second);
	}
	return 0;
}

int ability::Status_Temp_Change::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event)
{
	checkDuration(p_type);
	return 0;
}

void ability::Status_Temp_Change::effectEnd()
{
	AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);
	for (auto it : m_attributeChange)
	{
		int change = -it.second;//reverse change
		node->effect(m_unit, it.first, change);
	}
}
