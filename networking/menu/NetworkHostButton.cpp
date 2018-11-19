#include "NetworkHostButton.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"
#include "networking\menu\NetworkingMenuUI.h"

namespace userinterface
{
	NetworkHostButton::NetworkHostButton()
		:
		m_menu(nullptr)
	{
		
	}

	NetworkHostButton::~NetworkHostButton()
	{

	}

	void NetworkHostButton::start()
	{
		ClickableUI::start();

		// Network Menu buttons are their own GOs, but are attached as children to another GO
		// The parent GO is where the NetworkingConsoleMenu component is attached
		kitten::K_GameObject* parent = &m_attachedObject->getTransform().getParent()->getAttachedGameObject();
		m_menu = parent->getComponent<NetworkingConsoleMenu>();
		assert(m_menu != nullptr);
	}

	void NetworkHostButton::onClick()
	{
		m_menu->hostGame();
	}
}