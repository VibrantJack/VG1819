#include "PlaySoundOnKeyPress.h"
#include "kitten\InputManager.h"
#include "kitten\K_GameObject.h"

PlaySoundOnKeyPress::PlaySoundOnKeyPress(char p_key) : m_audioSource(nullptr), m_key(p_key)
{

}

PlaySoundOnKeyPress::PlaySoundOnKeyPress(nlohmann::json & p_json) : kitten::K_Component(p_json),
	m_audioSource(nullptr)
{
	if (JSONHAS("key"))
	{
		m_key = LOOKUPCHAR("key");
	}
}

PlaySoundOnKeyPress::~PlaySoundOnKeyPress()
{

}

void PlaySoundOnKeyPress::start()
{
	m_inputMan = input::InputManager::getInstance();
	m_audioSource = m_attachedObject->getComponent<kitten::AudioSource>();
	assert(m_audioSource != nullptr && m_inputMan != nullptr);
}

void PlaySoundOnKeyPress::update()
{
	if(m_inputMan->keyDown(m_key) && !m_inputMan->keyDownLast(m_key))
	{
		m_audioSource->play();
	}
}