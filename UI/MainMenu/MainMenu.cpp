// Testing Main Menu animations

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
	m_menuTop->getTransform().move(0.0f, 0.0f, -0.9f);
	m_menuTopController = m_menuTop->getComponent<LerpController>();
	m_menuTopController->addPositionLerpFinishedCallback(this);

	m_menuBottom = kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/menu_bottom.json");
	m_menuBottom->getTransform().move(0.0f, 0.0f, -0.9f);
	m_menuBottomController = m_menuBottom->getComponent<LerpController>();

	m_title = kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/victorum_title.json");
	m_title->getTransform().move(0.0f, 0.0f, -0.1f);
	m_titleController = m_title->getComponent<LerpController>();
	
}

void MainMenu::update()
{
	if (m_input->keyDown(GLFW_KEY_TAB) && !m_input->keyDownLast(GLFW_KEY_TAB))
	{
		m_titleController->positionLerp(glm::vec3(306.0f, 720.0f, -0.1f), MENU_LERP_TIME);
		m_menuTopController->positionLerp(MENU_TOP_LERP_VEC3_POS, MENU_LERP_TIME);
		m_menuBottomController->positionLerp(MENU_BOTTOM_LERP_VEC3_POS, MENU_LERP_TIME);

		m_menuTopController->addPositionLerpFinishedCallback(this);
	}
}

void MainMenu::onPositionLerpFinished()
{
	m_titleController->positionLerp(TITLE_ORIGINAL_VEC3_POS, MENU_LERP_TIME);
	m_menuTopController->positionLerp(MENU_TOP_ORIGINAL_VEC3_POS, MENU_LERP_TIME);
	m_menuBottomController->positionLerp(MENU_BOTTOM_ORIGINAL_VEC3_POS, MENU_LERP_TIME);
}
