#include "ToggleParticleSystemOnKeyPress.h"
#include "kitten\K_GameObject.h"

ToggleParticleSystemOnKeyPress::ToggleParticleSystemOnKeyPress(char p_key) : m_key(p_key), m_inputMan(nullptr), m_particleSystem(nullptr)
{

}

ToggleParticleSystemOnKeyPress::~ToggleParticleSystemOnKeyPress()
{

}

void ToggleParticleSystemOnKeyPress::start()
{
	m_inputMan = input::InputManager::getInstance();
	assert(m_inputMan != nullptr);

	m_particleSystem = m_attachedObject->getComponent<kitten::K_ParticleSystem>();
	assert(m_particleSystem != nullptr);
}

void ToggleParticleSystemOnKeyPress::update()
{
	if (m_inputMan->keyDown(m_key) && !m_inputMan->keyDownLast(m_key))
	{
		if (m_particleSystem->isPlaying())
		{
			m_particleSystem->pause();
		}
		else
		{
			m_particleSystem->play();
		}
	}
}