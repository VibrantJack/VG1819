#include "NetworkJoinButton.h"
#include "kitten\event_system\EventManager.h"
#include "components\DeckInitializingComponent.h"
#include "kitten\K_Instance.h"

#include "kitten\K_GameObjectManager.h"

namespace userinterface
{
	NetworkJoinButton::NetworkJoinButton()
	{

	}

	NetworkJoinButton::~NetworkJoinButton()
	{
		if (DeckInitializingComponent::getActiveInstance() != nullptr)
		{
			DeckInitializingComponent::getActiveInstance()->toggleMessage(false);
		}
	}

	void NetworkJoinButton::onClick()
	{		
		if (DeckInitializingComponent::getActiveInstance() == nullptr) return;
		if (DeckInitializingComponent::getActiveInstance()->getDeckData() == nullptr)
		{
			DeckInitializingComponent::getActiveInstance()->toggleMessage(true);
			kitten::EventManager::getInstance()->queueEvent(kitten::Event::Remove_Loading_Screen, nullptr);
			return;
		}
		kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/loading_screen.json");
		kitten::K_Instance::changeScene("network_menu.json");
	}
}