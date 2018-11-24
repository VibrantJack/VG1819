#include "components\TabMenu.h"

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
}

void TabMenu::update()
{
	if (m_input->keyDown(GLFW_KEY_TAB) && !m_input->keyDownLast(GLFW_KEY_TAB && !m_bOpened))
	{
		m_bOpened = true;

		// Open menu
		// Create "Quit to Main Menu" button here and "Close Menu" button here
		// "Close Menu" would do the same thing as hitting Tab again
	}

	if (m_bOpened)
	{
		if (m_input->keyDown(GLFW_KEY_TAB) && !m_input->keyDownLast(GLFW_KEY_TAB && !m_bOpened))
		{
			m_bOpened = false;

			// Close menu
			// Destroy menu buttons here
		}
	}
}