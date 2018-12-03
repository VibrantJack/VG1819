#include "NetworkHostButton.h"
#include "kitten\event_system\EventManager.h"

namespace userinterface
{
	NetworkHostButton::NetworkHostButton()
	{
		
	}

	NetworkHostButton::~NetworkHostButton()
	{

	}

	void NetworkHostButton::onClick()
	{
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Host_Button_Clicked, nullptr);
	}
}