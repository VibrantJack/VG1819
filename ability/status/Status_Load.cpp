#include "ability/status/Status.h"
#include "ability/AbilityMacro.h"
ability::Status_Load::Status_Load()
{
	m_Id = STATUS_LOAD;
	addTimePoint(TimePointEvent::Deal_Damage);
}

int ability::Status_Load::effect()
{
	AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);
	for (auto it : m_attributeChange)
	{
		node->effect(m_unit, m_effectedAD, it.first, it.second);
	}
	return 0;
}

int ability::Status_Load::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent* p_event)
{
	if (p_type == ability::TimePointEvent::Deal_Damage)
	{
		//reduce duration
		changeCounter();
		return 0;
	}
	return 1;
}

void ability::Status_Load::effectEnd()
{
	AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);
	for (auto it : m_attributeChange)
	{
		int change = -it.second;//reverse change
		node->effect(m_unit, m_effectedAD, it.first, change);
	}
}