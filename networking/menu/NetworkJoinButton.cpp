#include "NetworkJoinButton.h"
#include "kitten\K_Instance.h"
#include "kitten\K_GameObjectManager.h"

namespace userinterface
{
	NetworkJoinButton::NetworkJoinButton()
		:
		m_menu(nullptr)
	{

	}

	NetworkJoinButton::~NetworkJoinButton()
	{
		m_inputMan->setPollMode(true);
	}

	void NetworkJoinButton::start()
	{
		ClickableUI::start();

		kitten::K_GameObject* parent = &m_attachedObject->getTransform().getParent()->getAttachedGameObject();

		m_menu = parent->getComponent<NetworkingConsoleMenu>();
		assert(m_menu != nullptr);

		m_inputMan = input::InputManager::getInstance();
		assert(m_inputMan != nullptr);
		m_inputMan->setPollMode(false);

		m_stringInputDisplay = parent->getComponent<StringInputDisplay>();
		assert(m_stringInputDisplay != nullptr);

		m_textBox = parent->getComponent<puppy::TextBox>();
	}

	void NetworkJoinButton::update()
	{
		if (m_inputMan->keyDown(GLFW_KEY_ENTER) && !m_inputMan->keyDownLast(GLFW_KEY_ENTER))
		{
			std::string address = m_stringInputDisplay->getString();
			printf("Entered address: %s\n", address.c_str());
			m_menu->connectToHost(address);
			if (m_menu->checkClientNetwork())
			{
				m_inputMan->setPollMode(true);
				m_textBox->setText("Joined host");
			} else
			{
				m_textBox->setText("Network Error");
			}
		}
	}

	void NetworkJoinButton::onClick()
	{				
		m_menu->connectToHost(m_stringInputDisplay->getString());
		if (m_menu->checkClientNetwork())
		{
			m_inputMan->setPollMode(true);
			m_textBox->setText("Joined host");
			//kitten::K_GameObjectManager::getInstance()->flagGameObjectToSurvive(&m_menu->getGameObject());
			kitten::K_Instance::changeScene("mainscene.txt");
		}
		else
		{
			m_textBox->setText("Network Error");
		}
	}
}