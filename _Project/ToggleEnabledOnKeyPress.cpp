#include "ToggleEnabledOnKeyPress.h"
#include "kitten\K_GameObject.h"

ToggleEnabledOnKeyPress::ToggleEnabledOnKeyPress(char p_key) : m_key(p_key)
{
	
}

ToggleEnabledOnKeyPress::ToggleEnabledOnKeyPress(nlohmann::json & p_json) : kitten::K_Component(p_json)
{
	if(JSONHAS("key")) m_key = LOOKUPCHAR("key");
}

ToggleEnabledOnKeyPress::~ToggleEnabledOnKeyPress()
{

}

void ToggleEnabledOnKeyPress::start()
{
	m_inputMan = input::InputManager::getInstance();
	assert(m_inputMan != nullptr);
}

void ToggleEnabledOnKeyPress::update()
{
	//Only works if attached object is getting disabled
	//because this gets disabled as well (lol).
	if (m_inputMan->keyDown(m_key) && !m_inputMan->keyDownLast(m_key))
	{
		m_attachedObject->setEnabled(!m_attachedObject->isEnabled());
	}
}