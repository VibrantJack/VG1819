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
			return;
		}
		kitten::K_Instance::changeScene("network_menu.json");
		kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/loading_screen.json");
		//kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Join_Button_Clicked, nullptr);
	}
}