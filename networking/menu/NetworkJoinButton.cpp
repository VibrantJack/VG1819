#include "NetworkJoinButton.h"
#include "kitten\event_system\EventManager.h"
#include "kitten\K_GameObjectManager.h"

namespace userinterface
{
	NetworkJoinButton::NetworkJoinButton()
	{

	}

	NetworkJoinButton::~NetworkJoinButton()
	{
		m_inputMan->setPollMode(true);
	}

	void NetworkJoinButton::start()
	{
		ClickableButton::start();

		m_inputMan = input::InputManager::getInstance();
		assert(m_inputMan != nullptr);

		m_ipBox = kitten::K_GameObjectManager::getInstance()->createNewGameObject("netmenu_ip_box.txt");
		m_ipBox->getTransform().scale2D(250, 48);
		m_ipBox->getTransform().place(0, 0, -0.8);
		m_ipBox->getTransform().place2D(989, 37);
		m_ipBox->setEnabled(false);
	}

	void NetworkJoinButton::onClick()
	{		
		m_ipBox->setEnabled(true);
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Join_Button_Clicked, nullptr);
	}
}