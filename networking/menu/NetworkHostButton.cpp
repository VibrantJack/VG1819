#include "NetworkHostButton.h"
#include "kitten\event_system\EventManager.h"
#include "components\DeckInitializingComponent.h"

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
		if (DeckInitializingComponent::getActiveInstance() == nullptr) return;
		if (DeckInitializingComponent::getActiveInstance()->getDeckData() == nullptr) return;
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Host_Button_Clicked, nullptr);
	}
}