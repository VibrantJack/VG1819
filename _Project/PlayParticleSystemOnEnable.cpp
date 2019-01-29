#include "PlayParticleSystemOnEnable.h"

PlayParticleSystemOnEnable::PlayParticleSystemOnEnable() : m_particleSystem(nullptr)
{

}

PlayParticleSystemOnEnable::~PlayParticleSystemOnEnable()
{

}

void PlayParticleSystemOnEnable::start()
{
	m_particleSystem = m_attachedObject->getComponent<kitten::K_ParticleSystem>();
	assert(m_particleSystem != nullptr);
}

void PlayParticleSystemOnEnable::onEnabled()
{
	m_particleSystem->play();
}