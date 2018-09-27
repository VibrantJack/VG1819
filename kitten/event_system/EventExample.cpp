// EventExample
// 
// Simple class to showcase the functionality of the event system
// 
// author: Ken

#include "kitten\event_system\EventExample.h"
#include <iostream>

namespace kitten
{
	void EventExample::registerListener() {
		EventManager::getInstance()->addListener(
			Event::EventType::Test_Event,
			this,
			std::bind(&EventExample::printEventMessage, this, std::placeholders::_1, std::placeholders::_2));
	}

	void EventExample::deregisterListener() {
		EventManager::getInstance()->removeListener(Event::Test_Event, this);
	}

	void EventExample::printEventMessage(Event::EventType p_type, Event* p_data) {
		std::cout << p_data->getString("key") << std::endl;
	}
}