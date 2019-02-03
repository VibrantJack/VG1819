#include "HaltParticleSystemAfterTime.h"

HaltParticleSystemAfterTime::HaltParticleSystemAfterTime(float p_time, bool p_isStopping) : m_timeToHalt(p_time), m_isStopping(p_isStopping),
	m_timeElapsed(0), m_particleSystem(nullptr)
{

}

HaltParticleSystemAfterTime::~HaltParticleSystemAfterTime()
{

}

void HaltParticleSystemAfterTime::start()
{
	m_particleSystem = m_attachedObject->getComponent<kitten::K_ParticleSystem>();
	assert(m_particleSystem != nullptr);

	m_time = kitten::K_Time::getInstance();
	assert(m_time != nullptr);
}

void HaltParticleSystemAfterTime::onEnabled()
{
	m_timeElapsed = 0.0f;
}

void HaltParticleSystemAfterTime::onDisabled()
{

}

void HaltParticleSystemAfterTime::update()
{
	m_timeElapsed += m_time->getDeltaTime();
	if (m_timeElapsed >= m_timeToHalt)
	{
		if (m_isStopping)
		{
			m_particleSystem->stop();
		}
		else
		{
			m_particleSystem->pause();
		}

		setEnabled(false);
	}
}