#include "ability/status/Status.h"
#include "ability/AbilityMacro.h"

ability::Status_AD_Change::Status_AD_Change()
{
	m_name = STATUS_AD_CHANGE;
	addTimePoint(TimePointEvent::Turn_End);
}

int ability::Status_AD_Change::effect()
{
	AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);
	for (auto it : m_attributeChange)
	{
		node->effect(m_unit, m_effectedAD, it.first, it.second);
	}
	return 0;
}

int ability::Status_AD_Change::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent* p_event)
{
	if (p_type == ability::TimePointEvent::Turn_End)
	{
		//reduce duration
		changeCounter();
		return 0;
	}
	return 1;
}

void ability::Status_AD_Change::effectEnd()
{
	AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAbilityDescription);
	for (auto it : m_attributeChange)
	{
		int change = -it.second;//reverse change
		node->effect(m_unit, m_effectedAD, it.first, change);
	}
}