#include "ToggleChildEnabledOnKeyPress.h"
#include "kitten\K_GameObject.h"

ToggleChildEnabledOnKeyPress::ToggleChildEnabledOnKeyPress(char p_key) : m_key(p_key)
{
	
}

ToggleChildEnabledOnKeyPress::~ToggleChildEnabledOnKeyPress()
{

}

void ToggleChildEnabledOnKeyPress::start()
{
	m_inputMan = input::InputManager::getInstance();
	assert(m_inputMan != nullptr);
}

void ToggleChildEnabledOnKeyPress::update()
{
	if (m_inputMan->keyDown(m_key) && !m_inputMan->keyDownLast(m_key))
	{
		if (getTransform().hasChildren())
		{
			kitten::K_GameObject& firstChild = (*(getTransform().getChildren().begin()))->getAttachedGameObject();
			firstChild.setEnabled(!firstChild.isEnabled());
		}
	}
}
