#include "ability/status/Status.h"
#include "ability/AbilityMacro.h"
#include "unit/UnitCommon.h"

ability::Status_IN_Change::Status_IN_Change()
{
	m_Id = STATUS_IN_CHANGE;
}

ability::Status_IN_Change::~Status_IN_Change()
{
	//remove listenner
	kitten::EventManager::getInstance()->removeListener(kitten::Event::New_Game_Turn, this);
}

int ability::Status_IN_Change::effect()
{
	AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);
	for (auto it : m_attributeChange)
	{
		if(it.first == UNIT_IN || it.first == UNIT_BASE_IN)
			node->effect(m_unit, it.first, it.second);
	}

	registerEvent();

	return 0;
}

void ability::Status_IN_Change::effectEnd()
{
	AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);
	for (auto it : m_attributeChange)
	{
		int change = -it.second;//reverse change
		if (it.first == UNIT_IN || it.first == UNIT_BASE_IN)
			node->effect(m_unit, it.first, change);
	}

}

void ability::Status_IN_Change::registerEvent()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::New_Game_Turn,
		this,
		std::bind(&Status_IN_Change::listenEvent, this, std::placeholders::_1, std::placeholders::_2));

}

void ability::Status_IN_Change::listenEvent(kitten::Event::EventType p_type, kitten::Event * p_data)
{
	if (p_type == kitten::Event::New_Game_Turn)
	{
		checkDuration();
	}
}
