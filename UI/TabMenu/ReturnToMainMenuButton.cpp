#include "UI\TabMenu\ReturnToMainMenuButton.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\event_system\EventManager.h"


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

	void ReturnToMainMenuButton::onClick()
	{
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Return_to_Main_Menu, nullptr);
	}
}