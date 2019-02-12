#include "FadePointLightOverTime.h"
#include "util\MathUtil.h"

FadePointLightOverTime::FadePointLightOverTime(float p_timeToFade) : m_pointLight(nullptr), m_time(nullptr), m_timeElapsed(0), m_timeToFade(p_timeToFade)
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

	m_startingLightColour = m_pointLight->getPointColor();
}

void FadePointLightOverTime::onEnabled()
{
	m_pointLight->setPointColor((glm::vec3)m_startingLightColour);
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
		setEnabled(false);
		m_pointLight->setEnabled(false);
	}
	else
	{
		glm::vec4 newLightColour = LERP((m_timeElapsed / m_timeToFade), m_startingLightColour, glm::vec4(0, 0, 0, 1));
		m_pointLight->setPointColor((glm::vec3)newLightColour);
	}
}