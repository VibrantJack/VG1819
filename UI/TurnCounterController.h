#pragma once

#include "kitten/K_Common.h"
#include "puppy/Text/TextBox.h"
#include "kitten/event_system/EventManager.h"

class TurnCounterController : public kitten::K_Component
{
public:
	TurnCounterController();
	~TurnCounterController();

	void start() override;

	void registerEvent();
	void deregisterEvent();
	void listenEvent(kitten::Event::EventType p_type, kitten::Event * p_data);
private:
	puppy::TextBox* m_text;
	int m_turnCounter;

	void changeText();
};