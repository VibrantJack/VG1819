#include "ToggleStringInputOnKeyPress.h"

ToggleStringInputOnKeyPress::ToggleStringInputOnKeyPress(char p_key) : m_key(p_key), m_inputMan(nullptr)
{

}

ToggleStringInputOnKeyPress::~ToggleStringInputOnKeyPress()
{

}

void ToggleStringInputOnKeyPress::start()
{
	m_inputMan = input::InputManager::getInstance();
	assert(m_inputMan != nullptr);
}

void ToggleStringInputOnKeyPress::update()
{
	if (m_inputMan->keyDown(m_key) && !m_inputMan->keyDownLast(m_key))
	{
		m_inputMan->setPollMode(false);
	}
}