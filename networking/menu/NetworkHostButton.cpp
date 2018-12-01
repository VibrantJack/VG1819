#include "NetworkHostButton.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_Instance.h"

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
			m_textBox->setText("Connected");
			//kitten::K_GameObjectManager::getInstance()->flagGameObjectToSurvive(&m_menu->getGameObject());
			kitten::K_Instance::changeScene("mainscene.txt");
		}
		else
		{
			m_textBox->setText("Network Error");
		}
	}
}