#include "ability/status/Status.h"
#include "ability/AbilityMacro.h"

ability::Status_Temp_Change::Status_Temp_Change()
{
	m_name = STATUS_TEMP_CHANGE;
	addTimePoint(TimePointEvent::Turn_End);
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

int ability::Status_Temp_Change::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent* p_event)
{
	if (p_type == ability::TimePointEvent::Turn_End)
	{
		//reduce duration
		changeCounter();
		return 0;
	}
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
