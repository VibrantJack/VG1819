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
		if (DeckInitializingComponent::getActiveInstance() != nullptr)
		{
			DeckInitializingComponent::getActiveInstance()->toggleMessage(false);
		}
	}

	void NetworkHostButton::onClick()
	{
		if (DeckInitializingComponent::getActiveInstance() == nullptr) return;
		if (DeckInitializingComponent::getActiveInstance()->getDeckData() == nullptr)
		{
			DeckInitializingComponent::getActiveInstance()->toggleMessage(true);
			kitten::EventManager::getInstance()->queueEvent(kitten::Event::Remove_Loading_Screen, nullptr);
			return;
		}
		kitten::EventManager::getInstance()->queueEvent(kitten::Event::EventType::Host_Button_Clicked, nullptr);
	}
}