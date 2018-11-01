#include "ToggleSoundOnKeyPress.h"
#include "kitten\K_GameObject.h"


ToggleSoundOnKeyPress::ToggleSoundOnKeyPress(char p_key) : m_key(p_key)
{
	
}

ToggleSoundOnKeyPress::~ToggleSoundOnKeyPress()
{

}

void ToggleSoundOnKeyPress::start()
{
	m_audioSource = m_attachedObject->getComponent<kitten::AudioSource>();
	m_inputMan = input::InputManager::getInstance();

	assert(m_audioSource != nullptr && m_inputMan != nullptr);
}

void ToggleSoundOnKeyPress::update()
{
	if (m_inputMan->keyDown(m_key) && !m_inputMan->keyDownLast(m_key))
	{
		m_audioSource->setPaused(!m_audioSource->isPaused());
	}
}