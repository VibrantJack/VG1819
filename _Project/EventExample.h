#pragma once

#include "kitten\event_system\EventManager.h"
#include <string>

namespace kitten {
	class EventExample {

		void registerListener();

		void printEventMessage(const std::string& p_msg);
	};
}