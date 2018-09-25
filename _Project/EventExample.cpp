//#include "kitten\event_system\EventExample.h"
#include "EventExample.h"
#include <iostream>

using namespace kitten;

void EventExample::registerListener() {

}

void EventExample::printEventMessage(const std::string& p_msg) {
	std::cout << p_msg << std::endl;
}