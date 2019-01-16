#include "UI\TriggerEventButton.h"

namespace userinterface
{
	TriggerEventButton::TriggerEventButton(kitten::Event::EventType p_eventEnum) : m_eventEnum(p_eventEnum)
	{

	}

	TriggerEventButton::~TriggerEventButton()
	{

	}

	void TriggerEventButton::onClick()
	{
		if (m_active)
			kitten::EventManager::getInstance()->triggerEvent(m_eventEnum, nullptr);
	}
}