#pragma once

#include "UI\ClickableButton.h"
#include "kitten\event_system\EventManager.h"

namespace userinterface
{
	class TriggerEventButton : public ClickableButton
	{
	private:
		kitten::Event::EventType m_eventEnum;
	public:
		TriggerEventButton(kitten::Event::EventType p_eventEnum);
		~TriggerEventButton();

		virtual void onClick();
	};
}