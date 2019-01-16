#include "NetworkConnectButton.h"
#include "kitten\event_system\EventManager.h"
#include "kitten\K_GameObjectManager.h"
#include "components\DeckInitializingComponent.h"
#include "kitten\K_Instance.h"

#include "networking\ClientGame.h"

namespace userinterface
{
	NetworkConnectButton::NetworkConnectButton()
	{

	}

	NetworkConnectButton::~NetworkConnectButton()
	{

	}

	void NetworkConnectButton::start()
	{
		ClickableButton::start();

		// Disabled due to a weird bug I can't figure out
		// If you Click this button instead of pressing Enter to confirm the IP address,
		// ServerGame accepts two new Clients, instead of just one, and the second player ID becomes 2 as a result

		// Keeping this so I can come back to solve this in the future
		m_attachedObject->setEnabled(false);
	}

	void NetworkConnectButton::onClick()
	{
		kitten::EventManager::getInstance()->queueEvent(kitten::Event::EventType::Join_Direct_Address, nullptr);

		/*networking::ClientGame::createInstance("localhost");
		if (networking::ClientGame::isNetworkValid())
		{
			kitten::K_Instance::changeScene("mainscene.json");
		}*/
	}
}