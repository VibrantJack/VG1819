#include "UI\MainMenu\MainMenu.h"
#include "kitten\K_GameObjectManager.h"

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{

}

void MainMenu::start()
{
	m_input = input::InputManager::getInstance();
	assert(m_input != nullptr);

	m_menuTop = kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/menu_top.json");
	m_menuTopController = m_menuTop->getComponent<LerpController>();
	m_menuTopController->addPositionLerpFinishedCallback(this);

	m_menuBottom = kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/menu_bottom.json");
	m_menuBottomController = m_menuBottom->getComponent<LerpController>();
	//m_menuBottomController->addPositionLerpFinishedCallback(this);
}

void MainMenu::update()
{
	if (m_input->keyDown(GLFW_KEY_TAB) && !m_input->keyDownLast(GLFW_KEY_TAB))
	{
		m_menuTopController->positionLerp(MENU_TOP_LERP_VEC3_POS, MENU_LERP_TIME);
		m_menuBottomController->positionLerp(MENU_BOTTOM_LERP_VEC3_POS, MENU_LERP_TIME);
		m_menuTopController->addPositionLerpFinishedCallback(this);
	}
}

void MainMenu::onPositionLerpFinished()
{
	m_menuTopController->positionLerp(MENU_TOP_ORIGINAL_VEC3_POS, MENU_LERP_TIME);
	m_menuBottomController->positionLerp(MENU_BOTTOM_ORIGINAL_VEC3_POS, MENU_LERP_TIME);

}
