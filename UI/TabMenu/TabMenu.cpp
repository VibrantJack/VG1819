// TabMenu
//
// Acts as something similar to a menu you would have when you hit 'Escape' in a game, 
// but instead you hit 'Tab', showing a button to return to..
// Hitting 'Tab' will either open the menu or close it depending on the state
// This also functions as a way to display the end game screen when a Commander is defeated, 
// alerted through events
//
// @Ken

#include "UI\TabMenu\TabMenu.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_ComponentManager.h"

#include "UI\UIObject.h"

TabMenu::TabMenu(const char* p_pathToTex)
	:
	UIFrame(p_pathToTex),
	m_bOpened(false),
	m_bGameEnded(false)
{

}

TabMenu::~TabMenu()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::End_Game_Screen, this);
}

void TabMenu::start()
{
	removeFromDynamicRender();

	m_input = input::InputManager::getInstance();
	assert(m_input != nullptr);

	// Add Listeners for enabling end game screen on Commander death
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::End_Game_Screen,
		this,
		std::bind(&TabMenu::enableEndGameScreen, this, std::placeholders::_1, std::placeholders::_2));

	// Create Return to Main Menu Button
	m_returnToMainButton = kitten::K_GameObjectManager::getInstance()->createNewGameObject("return_to_main_menu_button.txt"); 
	addToFrame(static_cast<userinterface::UIObject*>(m_returnToMainButton->getComponent<userinterface::UIObject>()));

	// Create End Game screen UI
	kitten::K_GameObject* endGameScreen = kitten::K_GameObjectManager::getInstance()->createNewGameObject("game_result_screen.txt");
	m_endGameScreenObj = static_cast<userinterface::UIObject*>(endGameScreen->getComponent<userinterface::UIObject>());
	addToFrame(m_endGameScreenObj);

	m_returnToMainButton->setEnabled(false);
	m_endGameScreenObj->setEnabled(false);
}

void TabMenu::update()
{
	if (m_input->keyDown(GLFW_KEY_TAB) && !m_input->keyDownLast(GLFW_KEY_TAB) && !m_bGameEnded)
	{
		m_bOpened = !m_bOpened;
		
		if (m_bOpened)
		{
			m_returnToMainButton->setEnabled(true);
		} 
		else
		{
			m_returnToMainButton->setEnabled(false);
		}
	}	
}

void TabMenu::enableEndGameScreen(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	m_bGameEnded = true;
	bool bVictory = p_data->getInt(PLAYER_COMMANDER_DEATH);
	if (!bVictory)
		m_endGameScreenObj->setTexture("textures/ui/defeat.tga");

	m_endGameScreenObj->setEnabled(true);	// Show UIObject indicating Victory or Defeat
	m_returnToMainButton->setEnabled(true); // Permanently show main menu button
}
