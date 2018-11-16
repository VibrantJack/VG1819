#include "ui/NetworkHostButton.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"

namespace userinterface
{
	NetworkHostButton::NetworkHostButton()
	{
		//nothing new to add
		kitten::K_GameObject* networkingMenu = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		networkingMenu->addComponent(kitten::K_ComponentManager::getInstance()->createComponent("NetworkingConsoleMenu"));
		m_menu = networkingMenu->getComponent<NetworkingConsoleMenu>();
	}

	NetworkHostButton::~NetworkHostButton()
	{

	}

	void NetworkHostButton::onClick()
	{
		printf("Host Button clicked\n");
		m_menu->hostGame();
	}
}