#pragma once

#include "kitten\event_system\EventManager.h"
#include <string>

namespace kitten {
	class EventExample {

	public:
		void registerListener();
		void deregisterListener();
		void printEventMessage(Event::EventType p_type, Event* p_data);

	};

}