#include "NetworkJoinButton.h"

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

	}

	void NetworkJoinButton::start()
	{
		ClickableUI::start();

		// Network Menu buttons are their own GOs, but are attached as children to another GO
		// The parent GO is where the NetworkingConsoleMenu component is attached
		kitten::K_GameObject* parent = &m_attachedObject->getTransform().getParent()->getAttachedGameObject();
		m_menu = parent->getComponent<NetworkingConsoleMenu>();
		assert(m_menu != nullptr);

		m_inputMan = input::InputManager::getInstance();
		assert(m_inputMan != nullptr);
		m_inputMan->setPollMode(false);

		m_stringInputDisplay = getStringInputDisplay();
		assert(m_stringInputDisplay != nullptr);
	}

	void NetworkJoinButton::onClick()
	{				
		//printf("Input: %s\n", m_stringInputDisplay->getString().c_str());
		m_menu->connectToHost(m_stringInputDisplay->getString());
		if (m_menu->checkClientNetwork())
		{
			m_inputMan->setPollMode(true);
		}
	}

	StringInputDisplay*  NetworkJoinButton::getStringInputDisplay()
	{
		kitten::K_GameObject* parent = &m_attachedObject->getTransform().getParent()->getAttachedGameObject();
		kitten::K_GameObject* child;
		auto children = parent->getTransform().getChildren();

		for (auto it = children.begin(); it != children.end(); ++it)
		{
			child = &(*it)->getAttachedGameObject();
			StringInputDisplay* inputDisplay = child->getComponent<StringInputDisplay>();
			if (inputDisplay != nullptr)
			{
				return inputDisplay;
			}
		}
		return nullptr;
	}
}