#include "components\TabMenu.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_ComponentManager.h"

#include "kitten/mouse picking/ClickableUI.h"
#include "kitten/mouse picking/ClickableFrame.h"
#include "UI\TabMenu\ReturnToMainMenuButton.h"
#include "UI/UIFrame.h"

TabMenu::TabMenu() : m_bOpened(false)
{

}

TabMenu::~TabMenu()
{

}

void TabMenu::start()
{
	m_input = input::InputManager::getInstance();
	assert(m_input != nullptr);

	kitten::Transform* parent = &m_attachedObject->getTransform();

	// Creating ReturnToMainMenuButton Button
	m_returnToMainButton = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
	m_returnToMainButton->getTransform().setParent(parent);
	m_returnToMainButton->getTransform().scale2D(170, 100);
	m_returnToMainButton->getTransform().place2D(0, 620);

	K_Component* buttonObj = kitten::K_ComponentManager::getInstance()->createComponent("Frame"); // UIFrame : UIElement
	userinterface::UIFrame* buttonFrame = static_cast<userinterface::UIFrame*>(buttonObj);
	buttonFrame->setTexture("textures/ui/return_to_mm.tga");
	m_returnToMainButton->addComponent(buttonObj);


	K_Component* buttonCF = kitten::K_ComponentManager::getInstance()->createComponent("ClickableFrame"); // ClickableFrame : K_Component
	K_Component* clickUI = kitten::K_ComponentManager::getInstance()->createComponent("ReturnToMainMenuButton"); // ClickableUI : K_Component
	m_returnToMainButton->addComponent(buttonCF);
	m_returnToMainButton->addComponent(clickUI);

	m_returnToMainButton->setEnabled(false);
	// End creating ReturnToMainMenuButton Button

}

void TabMenu::update()
{
	if ((m_input->keyDown(GLFW_KEY_TAB) && !m_input->keyDownLast(GLFW_KEY_TAB)))
	{
		m_bOpened = !m_bOpened;

		
		if (m_bOpened)
		{
			// Open menu
			m_returnToMainButton->setEnabled(true);
		} 
		else
		{
			// Close menu
			m_returnToMainButton->setEnabled(false);
		}
	}

	
}