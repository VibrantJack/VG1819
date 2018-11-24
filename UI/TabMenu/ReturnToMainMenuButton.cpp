#include "UI\TabMenu\ReturnToMainMenuButton.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"


namespace userinterface
{
	ReturnToMainMenuButton::ReturnToMainMenuButton()
	{

	}

	ReturnToMainMenuButton::~ReturnToMainMenuButton()
	{

	}

	void ReturnToMainMenuButton::onDisabled()
	{
		if (m_attachedFrame != nullptr)
		{
			m_attachedFrame->removeClickable(this);
		}
	}

	void ReturnToMainMenuButton::onEnabled()
	{
		if (m_attachedFrame != nullptr)
		{
			m_attachedFrame->addCLickable(this);
		}
	}

	void ReturnToMainMenuButton::start()
	{
		ClickableUI::start();
		// Menu buttons are their own GOs, but are attached as children to parent GO
		kitten::K_GameObject* parent = &m_attachedObject->getTransform().getParent()->getAttachedGameObject();
		//m_menu = parent->getComponent<NetworkingConsoleMenu>();
		//assert(m_menu != nullptr);
	}

	void ReturnToMainMenuButton::onClick()
	{
		//m_menu->stopHosting();
		printf("Return to Main Menu Button clicked!\n");
	}
}