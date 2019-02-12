#include "FadePointLightOverTime.h"
#include "util\MathUtil.h"

FadePointLightOverTime::FadePointLightOverTime(float p_timeToFade, const glm::vec3& p_endingAttenuation) : m_pointLight(nullptr), 
m_time(nullptr), m_timeElapsed(0), m_timeToFade(p_timeToFade), m_endingAttenuation(p_endingAttenuation)
{

}

FadePointLightOverTime::~FadePointLightOverTime()
{

}

void FadePointLightOverTime::setTimeToFade(float p_timeToFade)
{
	m_timeToFade = p_timeToFade;
}

void FadePointLightOverTime::start()
{
	m_time = kitten::K_Time::getInstance();
	assert(m_time != nullptr);

	m_pointLight = m_attachedObject->getComponent<kitten::K_PointLight>();
	assert(m_pointLight != nullptr);

	m_startingAttenuation = m_pointLight->getAttenuation();
}

void FadePointLightOverTime::onEnabled()
{
	m_pointLight->setAttenuation(m_startingAttenuation);
}

void FadePointLightOverTime::onDisabled()
{
	m_timeElapsed = 0.0f;
}

void FadePointLightOverTime::update()
{
	m_timeElapsed += m_time->getDeltaTime();

	if (m_timeElapsed >= m_timeToFade)
	{
		m_attachedObject->setEnabled(false);
	}
	else
	{
		glm::vec3 newAttenuation = LERP((m_timeElapsed / m_timeToFade), m_startingAttenuation, m_endingAttenuation);
		m_pointLight->setAttenuation(newAttenuation);
	}
}