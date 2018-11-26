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

		kitten::K_GameObject* parent = &m_attachedObject->getTransform().getParent()->getAttachedGameObject();
		m_menu = parent->getComponent<NetworkingConsoleMenu>();
		assert(m_menu != nullptr);

		m_textBox = parent->getComponent<puppy::TextBox>();
	}

	void NetworkHostButton::onClick()
	{
		m_menu->hostGame();
		if (m_menu->checkClientNetwork() && m_menu->checkServerNetwork())
		{
			// Successful network setup
			// TODO: Setup new gamestate (get deck data and spawn each player's Commander)
			m_textBox->setText("Connected");
		}
		else
		{
			m_textBox->setText("Network Error");
		}
	}
}