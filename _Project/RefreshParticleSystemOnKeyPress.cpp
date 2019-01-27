#include "RefreshParticleSystemOnKeyPress.h"

RefreshParticleSystemOnKeyPress::RefreshParticleSystemOnKeyPress(char p_key) : m_key(p_key), m_inputMan(nullptr), m_particleSystem(nullptr)
{

}

RefreshParticleSystemOnKeyPress::~RefreshParticleSystemOnKeyPress()
{

}

void RefreshParticleSystemOnKeyPress::start()
{
	m_particleSystem = m_attachedObject->getComponent<kitten::K_ParticleSystem>();
	assert(m_particleSystem != nullptr);

	m_inputMan = input::InputManager::getInstance();
	assert(m_inputMan != nullptr);
}

void RefreshParticleSystemOnKeyPress::update()
{
	if (m_inputMan->keyDown(m_key) && !m_inputMan->keyDownLast(m_key))
	{
		m_particleSystem->refreshXML();
	}
}
